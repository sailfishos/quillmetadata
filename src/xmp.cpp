/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Alexander Bokovoy <alexander.bokovoy@nokia.com>
**
** This file is part of the Quill Metadata package.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include <QStringList>
#include <exempi-2.0/exempi/xmpconsts.h>

#include "xmp.h"

const QString Schema_DC = NS_DC;
const QString Schema_Exif = NS_EXIF;
const QString Schema_Photoshop = NS_PHOTOSHOP;
const QString Schema_IPTC = NS_IPTC4XMP;
const QString Schema_XAP = NS_XAP;

QHash<QuillMetadata::Tag,XmpTag> Xmp::m_xmpTags;
bool Xmp::m_initialized = false;

XmpTag::XmpTag() : schema(""), tag("")
{
}

XmpTag::XmpTag(const QString &schema, const QString &tag, TagType tagType) :
    schema(schema), tag(tag), tagType(tagType)
{
}

Xmp::Xmp()
{
    m_xmpPtr = xmp_new_empty();
}

Xmp::Xmp(const QString &fileName)
{
    xmp_init();
    XmpFilePtr xmpFilePtr = xmp_files_open_new(fileName.toAscii().constData(),
                                               XMP_OPEN_READ);
    m_xmpPtr = xmp_files_get_new_xmp(xmpFilePtr);
    xmp_files_close(xmpFilePtr, XMP_CLOSE_NOOPTION);
    xmp_files_free(xmpFilePtr);

    initTags();
}

Xmp::~Xmp()
{
    xmp_free(m_xmpPtr);
}

bool Xmp::isValid() const
{
    return (m_xmpPtr != 0);
}

bool Xmp::supportsEntry(QuillMetadata::Tag tag) const
{
    return m_xmpTags.contains(tag);
}

bool Xmp::hasEntry(QuillMetadata::Tag tag) const
{
    return (supportsEntry(tag) &&
            !m_xmpTags.values(tag).isEmpty());
}

QVariant Xmp::entry(QuillMetadata::Tag tag) const
{
    if (!supportsEntry(tag))
        return QVariant();

    QList<XmpTag> xmpTags = m_xmpTags.values(tag);

    XmpStringPtr xmpStringPtr = xmp_string_new();

    foreach (XmpTag xmpTag, xmpTags) {
        uint32_t propBits;

        if (xmp_get_property(m_xmpPtr,
                             xmpTag.schema.toAscii().constData(),
                             xmpTag.tag.toAscii().constData(),
                             xmpStringPtr,
                             &propBits)) {
            if (XMP_IS_PROP_ARRAY(propBits)) {
                xmp_get_array_item(m_xmpPtr,
                                   xmpTag.schema.toAscii().constData(),
                                   xmpTag.tag.toAscii().constData(),
                                   1,
                                   xmpStringPtr,
                                   &propBits);
            }
            QString string = QString(xmp_string_cstr(xmpStringPtr)).trimmed();

            if (!string.isEmpty()) {
                xmp_string_free(xmpStringPtr);
                // Unique nonstandard behavior for the Subject tag
                if (tag == QuillMetadata::Tag_Subject)
                    return QVariant(commaSeparatedToStringList(string));
                else
                    return QVariant(string);
            }
        }
    }

    xmp_string_free(xmpStringPtr);
    return QVariant();
}

void Xmp::setEntry(QuillMetadata::Tag tag, const QVariant &entry)
{
    if (!supportsEntry(tag))
        return;

    if (!m_xmpPtr) {
        m_xmpPtr = xmp_new_empty();
    }

    QList<XmpTag> xmpTags = m_xmpTags.values(tag);

    foreach (XmpTag xmpTag, xmpTags) {
        xmp_delete_property(m_xmpPtr,
                            xmpTag.schema.toAscii().constData(),
                            xmpTag.tag.toAscii().constData());

        if (xmpTag.tagType == XmpTag::TagTypeString)
            xmp_set_property(m_xmpPtr,
                             xmpTag.schema.toAscii().constData(),
                             xmpTag.tag.toAscii().constData(),
                             variantToXmpString(entry).constData(), 0);
        else if (xmpTag.tagType == XmpTag::TagTypeStringList) {
            xmp_append_array_item(m_xmpPtr,
                                  xmpTag.schema.toAscii().constData(),
                                  xmpTag.tag.toAscii().constData(),
                                  XMP_PROP_ARRAY_IS_UNORDERED,
                                  variantToXmpString(entry).constData(), 0);
        }
        else if (xmpTag.tagType == XmpTag::TagTypeAltLang) {
            xmp_set_localized_text(m_xmpPtr,
                                   xmpTag.schema.toAscii().constData(),
                                   xmpTag.tag.toAscii().constData(),
                                   "", "x-default",
                                   variantToXmpString(entry).constData(), 0);
        }
    }
}

#include <QDebug>

bool Xmp::write(const QString &fileName) const
{
    XmpPtr ptr = m_xmpPtr;

    if (!ptr)
        ptr = xmp_new_empty();

    XmpFilePtr xmpFilePtr = xmp_files_open_new(fileName.toAscii().constData(),
                                               XMP_OPEN_FORUPDATE);
    bool result;

    if (xmp_files_can_put_xmp(xmpFilePtr, ptr))
        result = xmp_files_put_xmp(xmpFilePtr, ptr);
    else
        result = false;

    // Crash safety can be ignored here by selecting Nooption since
    // QuillFile already has crash safety measures.
    if (result)
        result = xmp_files_close(xmpFilePtr, XMP_CLOSE_NOOPTION);
    xmp_files_free(xmpFilePtr);

    return result;
}

QStringList Xmp::commaSeparatedToStringList(const QString &inString)
{
    QStringList list = inString.split(",", QString::SkipEmptyParts);
    QStringList result;

    foreach (QString string, list)
        result.append(string.trimmed());

    return result;
}

QByteArray Xmp::variantToXmpString(const QVariant &variant)
{
    if (variant.type() != QVariant::StringList)
        return variant.toByteArray();

    QStringList list = variant.toStringList();
    QString result;
    foreach (QString string, list)
        result.append(string + QLatin1String(", "));
    result.truncate(result.length()-2);

    return result.toAscii();
}

void Xmp::initTags()
{
    if (m_initialized)
        return;

    m_initialized = true;

    m_xmpTags.insertMulti(QuillMetadata::Tag_Creator,
                          XmpTag(Schema_DC, "creator", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Subject,
                          XmpTag(Schema_DC, "subject", XmpTag::TagTypeStringList));
    m_xmpTags.insertMulti(QuillMetadata::Tag_City,
                          XmpTag(Schema_Photoshop, "City", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Country,
                          XmpTag(Schema_Photoshop, "Country", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_City,
                          XmpTag(Schema_IPTC, "LocationShownCity", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Country,
                          XmpTag(Schema_IPTC, "LocationShownCountry", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Location,
                          XmpTag(Schema_IPTC, "LocationShownSublocation", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Rating,
                          XmpTag(Schema_XAP, "Rating", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Timestamp,
                          XmpTag(Schema_XAP, "MetadataDate", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Description,
                          XmpTag(Schema_DC, "description", XmpTag::TagTypeAltLang));
    m_xmpTags.insertMulti(QuillMetadata::Tag_Orientation,
                          XmpTag(Schema_Exif, "Orientation", XmpTag::TagTypeString));

    m_xmpTags.insertMulti(QuillMetadata::Tag_GPSLatitude,
                          XmpTag(Schema_Exif, "GPSLatitude", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_GPSLongitude,
                          XmpTag(Schema_Exif, "GPSLongitude", XmpTag::TagTypeString));
    m_xmpTags.insertMulti(QuillMetadata::Tag_GPSAltitude,
                          XmpTag(Schema_Exif, "GPSAltitude", XmpTag::TagTypeString));
}
