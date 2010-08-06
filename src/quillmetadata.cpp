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

#include "exif.h"
#include "xmp.h"
#include "quillmetadata.h"

class QuillMetadataPrivate
{
public:
    Xmp *xmp;
    Exif *exif;
    bool isXmpNeeded; // If in the writeback we need also write XMP metadata

    static bool m_initialized;
    static QMap<QuillMetadata::TagGroup, QList<QuillMetadata::Tag> >
      m_tagGroups;
};

bool QuillMetadataPrivate::m_initialized = false;
QMap<QuillMetadata::TagGroup, QList<QuillMetadata::Tag> >
  QuillMetadataPrivate::m_tagGroups;

QuillMetadata::QuillMetadata()
{
    init();
    priv = new QuillMetadataPrivate;
    priv->xmp = new Xmp();
    priv->exif = new Exif();
    priv->isXmpNeeded = false;
}

QuillMetadata::QuillMetadata(const QString &fileName)
{
    init();
    priv = new QuillMetadataPrivate;
    priv->xmp = new Xmp(fileName);
    priv->exif = new Exif(fileName);
    priv->isXmpNeeded = true;
}

QuillMetadata::~QuillMetadata()
{
    delete priv->xmp;
    delete priv->exif;
}

bool QuillMetadata::isValid() const
{
    return (priv->exif->isValid() || priv->xmp->isValid());
}

QVariant QuillMetadata::entry(Tag tag) const
{
    // Prioritize EXIF over XMP as required by metadata working group
    QVariant result = priv->exif->entry(tag);
    if (result.isNull())
        result = priv->xmp->entry(tag);

    return result;
}

void QuillMetadata::setEntry(Tag tag, const QVariant &entry)
{
    priv->exif->setEntry(tag, entry);
    priv->xmp->setEntry(tag, entry);
    if (priv->xmp->supportsEntry(tag) && (tag != Tag_Orientation))
        priv->isXmpNeeded = true;
}

void QuillMetadata::removeEntry(Tag tag)
{
    priv->exif->removeEntry(tag);
    priv->xmp->removeEntry(tag);
}

void QuillMetadata::removeEntries(const QList<Tag> &tags)
{
    foreach(Tag tag, tags)
        removeEntry(tag);
}

void QuillMetadata::removeEntries(TagGroup tagGroup)
{
    removeEntries(QuillMetadataPrivate::m_tagGroups.value(tagGroup));
    priv->exif->removeEntries(tagGroup);
}

bool QuillMetadata::write(const QString &fileName,
                          MetadataFormatFlags formats) const
{
    bool result = true;
    if ((formats == ExifFormat) || (formats == AllFormats))
        result = result && priv->exif->write(fileName);
    if (((formats == XmpFormat) || (formats == AllFormats)) &&
        priv->isXmpNeeded)
        result = result && priv->xmp->write(fileName);
    return result;
}

QByteArray QuillMetadata::dumpExif() const
{
    return dump(ExifFormat);
}

QByteArray QuillMetadata::dump(MetadataFormatFlags formats) const
{
    if (formats == ExifFormat)
        return priv->exif->dump();
    else
        return QByteArray();
}

void QuillMetadata::init()
{
    if (QuillMetadataPrivate::m_initialized)
        return;

    QuillMetadataPrivate::m_initialized = true;

    QuillMetadataPrivate::m_tagGroups.insert(TagGroup_GPS,
                                             QList<QuillMetadata::Tag>() <<
                                             QuillMetadata::Tag_GPSLatitude <<
                                             QuillMetadata::Tag_GPSLongitude <<
                                             QuillMetadata::Tag_GPSAltitude);
}
