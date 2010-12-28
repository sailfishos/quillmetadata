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

#include <stdlib.h>
#include <libexif/exif-loader.h>
#include "exifwriteback.h"
#include "exif.h"

ExifTypedTag::ExifTypedTag():tag(),ifd(),format(),count()
{
}

ExifTypedTag::ExifTypedTag(ExifTag tag, ExifIfd ifd, ExifFormat format) :
    tag(tag), ifd(ifd), format(format), count(1)
{
}

ExifTypedTag::ExifTypedTag(ExifTag tag, ExifIfd ifd, ExifFormat format,
                           int count) :
    tag(tag), ifd(ifd), format(format), count(count)
{
}

QHash<QuillMetadata::Tag,ExifTypedTag> Exif::m_exifTags;
bool Exif::m_initialized = false;

Exif::Exif()
{
    m_exifData = exif_data_new();
    m_exifByteOrder = exif_data_get_byte_order(m_exifData);
    initTags();
}

Exif::Exif(const QString &fileName)
{
    // not using exif_data_new_from_file() since exif_data_fix() is too slow

    ExifLoader *loader = exif_loader_new();
    exif_loader_write_file(loader, fileName.toAscii().constData());

    const unsigned char *buf = 0;
    unsigned int bufSize = 0;
    exif_loader_get_buf(loader, &buf, &bufSize);

    m_exifData = exif_data_new();
    exif_data_unset_option(m_exifData, EXIF_DATA_OPTION_FOLLOW_SPECIFICATION);
    exif_data_load_data(m_exifData, buf, bufSize);
    exif_loader_unref(loader);

    m_exifByteOrder = exif_data_get_byte_order(m_exifData);

    initTags();
}

Exif::~Exif()
{
    //the entry, content will be freed recursively, we do not unref content and entry explicitly.
    //otherwise, there is a crashing
    exif_data_unref(m_exifData);
}

bool Exif::isValid() const
{
    return (m_exifData != 0);
}

bool Exif::supportsEntry(QuillMetadata::Tag tag) const
{
    return m_exifTags.contains(tag);
}

bool Exif::hasEntry(QuillMetadata::Tag tag) const
{
    return (supportsEntry(tag) &&
            exif_data_get_entry(m_exifData, m_exifTags[tag].tag));
}

QVariant Exif::entry(QuillMetadata::Tag tag) const
{
    if (!supportsEntry(tag))
        return QVariant();

    if (!m_exifData)
        return QVariant();

    ExifTag exifTag = m_exifTags[tag].tag;

    ExifEntry *entry = exif_data_get_entry(m_exifData, exifTag);
    if (!entry)
        return QVariant();

    QVariant result;

    switch(entry->format) {
    case EXIF_FORMAT_ASCII:
        result = QVariant(QByteArray((const char*)entry->data,entry->size));
        break;

    case EXIF_FORMAT_SHORT:
        result = QVariant(exif_get_short(entry->data, m_exifByteOrder));
        break;

    case EXIF_FORMAT_LONG:
        result = QVariant(exif_get_long(entry->data, m_exifByteOrder));
        break;

    case EXIF_FORMAT_RATIONAL: {
        ExifRational rational = exif_get_rational(entry->data, m_exifByteOrder);
        if (rational.denominator == 0)
            result = QVariant();
        else
            result = QVariant((float)rational.numerator /
                              (float)rational.denominator);
        break;
    }

    case EXIF_FORMAT_SRATIONAL: {
        ExifSRational srational = exif_get_srational(entry->data, m_exifByteOrder);
        if (srational.denominator == 0)
            result = QVariant();
        else
            result = QVariant((float)srational.numerator /
                              (float)srational.denominator);
        break;
    }

    case EXIF_FORMAT_FLOAT:
        result = QVariant(*((float*)entry->data));
        break;

    case EXIF_FORMAT_DOUBLE:
        result = QVariant(*((float*)entry->data));
        break;

    default:
        result = QVariant();
        break;
    }

    return result;
}

void Exif::setExifEntry(ExifData *data, ExifTypedTag tag, const QVariant &value)
{
    ExifContent *content = data->ifd[tag.ifd];

    ExifEntry *entry = exif_content_get_entry(content, tag.tag);
    if (!entry) {
        entry = exif_entry_new();
        exif_entry_initialize(entry, tag.tag);
    }

    entry->tag = tag.tag;
    entry->format = tag.format;

    switch(entry->format) {
    case EXIF_FORMAT_ASCII:
        entry->data = new unsigned char[value.toByteArray().size()];
        memcpy((char*)entry->data, value.toByteArray().constData(),value.toByteArray().size());
        entry->size = value.toByteArray().size();
        entry->components = entry->size;
        break;

    case EXIF_FORMAT_SHORT:
        entry->data = new unsigned char[exif_format_get_size(EXIF_FORMAT_SHORT)];
        exif_set_short(entry->data, m_exifByteOrder, value.toInt());
        entry->size = exif_format_get_size(EXIF_FORMAT_SHORT);
        entry->components = 1;
        break;

    default:
        break;
    }

    exif_content_add_entry(content, entry);
}

void Exif::setEntry(QuillMetadata::Tag tag, const QVariant &value)
{
    if (!supportsEntry(tag))
        return;

    if (!m_exifData) {
        m_exifData = exif_data_new();
        m_exifByteOrder = exif_data_get_byte_order(m_exifData);
    }

    setExifEntry(m_exifData, m_exifTags[tag], value);
}

void Exif::removeEntry(QuillMetadata::Tag tag)
{
    if (!supportsEntry(tag) || !m_exifData)
        return;

    ExifTypedTag typedTag = m_exifTags[tag];

    ExifContent *content = m_exifData->ifd[typedTag.ifd];

    ExifEntry *entry = exif_content_get_entry(content, typedTag.tag);
    if (entry)
        exif_content_remove_entry(content, entry);
}

void Exif::removeEntries(QuillMetadata::TagGroup tagGroup)
{
    if (!m_exifData)
        return;

    /* Remove all tags in the tag group */
    if (tagGroup == QuillMetadata::TagGroup_GPS) {
        ExifContent *content = m_exifData->ifd[EXIF_IFD_GPS];
        for (int t=(int)EXIF_TAG_GPS_VERSION_ID; // first GPS tag
             t<=(int)EXIF_TAG_GPS_DIFFERENTIAL; t++) // last GPS tag
            {
                ExifEntry *entry = exif_content_get_entry(content, (ExifTag)t);
                if (entry)
                    exif_content_remove_entry(content, entry);
            }
    }
}

bool Exif::write(const QString &fileName) const
{
    return ExifWriteback::writeback(fileName, dump());
}

QByteArray Exif::dump() const
{
    if (!m_exifData)
        return QByteArray();

    unsigned char *d;
    unsigned int ds;

    // Since the data is not fixed on load, fix it on save instead.
    exif_data_fix(m_exifData);
    exif_data_save_data(m_exifData, &d, &ds);
    QByteArray result = QByteArray((char*)d, ds);
    free(d);

    return result;
}

void Exif::initTags()
{
    if (m_initialized)
        return;

    m_initialized = true;

    m_exifTags.insert(QuillMetadata::Tag_Make,
                      ExifTypedTag(EXIF_TAG_MAKE,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_ASCII));
    m_exifTags.insert(QuillMetadata::Tag_Model,
                      ExifTypedTag(EXIF_TAG_MODEL,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_ASCII));
    m_exifTags.insert(QuillMetadata::Tag_ImageWidth,
                      ExifTypedTag(EXIF_TAG_IMAGE_WIDTH,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_SHORT));
    m_exifTags.insert(QuillMetadata::Tag_ImageHeight,
                      ExifTypedTag(EXIF_TAG_IMAGE_LENGTH,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_SHORT));
    m_exifTags.insert(QuillMetadata::Tag_FocalLength,
                      ExifTypedTag(EXIF_TAG_FOCAL_LENGTH,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_RATIONAL));
    m_exifTags.insert(QuillMetadata::Tag_ExposureTime,
                      ExifTypedTag(EXIF_TAG_EXPOSURE_TIME,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_RATIONAL));
    m_exifTags.insert(QuillMetadata::Tag_TimestampOriginal,
                      ExifTypedTag(EXIF_TAG_DATE_TIME_ORIGINAL,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_ASCII));
    m_exifTags.insert(QuillMetadata::Tag_Orientation,
                      ExifTypedTag(EXIF_TAG_ORIENTATION,
                                   EXIF_IFD_0,
                                   EXIF_FORMAT_SHORT));
    m_exifTags.insert(QuillMetadata::Tag_GPSLatitude,
                      ExifTypedTag((ExifTag)EXIF_TAG_GPS_LATITUDE,
                                   EXIF_IFD_GPS,
                                   EXIF_FORMAT_RATIONAL));
    m_exifTags.insert(QuillMetadata::Tag_GPSLongitude,
                      ExifTypedTag((ExifTag)EXIF_TAG_GPS_LONGITUDE,
                                   EXIF_IFD_GPS,
                                   EXIF_FORMAT_RATIONAL));
    m_exifTags.insert(QuillMetadata::Tag_GPSAltitude,
                      ExifTypedTag((ExifTag)EXIF_TAG_GPS_ALTITUDE,
                                   EXIF_IFD_GPS,
                                   EXIF_FORMAT_RATIONAL));
}
