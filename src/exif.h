/****************************************************************************
**
** Copyright (C) 2010-11 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Pekka Marjola <pekka.marjola@nokia.com>
**
** This file is part of the Quill package.
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

#ifndef EXIF_H
#define EXIF_H

#include <libexif/exif-data.h>
#include <QString>
#include <QHash>

#include "metadatarepresentation.h"

class ExifTypedTag {
public:
    ExifTypedTag();
    ExifTypedTag(ExifTag tag, ExifIfd ifd, ExifFormat format);
    ExifTypedTag(ExifTag tag, ExifIfd ifd, ExifFormat format, int count);

    ExifTag tag;
    ExifIfd ifd;
    ExifFormat format;
    int count;
};

class Exif : public MetadataRepresentation
{
 public:
    Exif();
    Exif(const QString &fileName,
         QuillMetadata::Tag tagToRead = QuillMetadata::Tag_Undefined);
    ~Exif();

    bool isValid() const;
    bool hasData() const;

    bool supportsEntry(QuillMetadata::Tag tag) const;
    bool hasEntry(QuillMetadata::Tag tag) const;
    QVariant entry(QuillMetadata::Tag tag) const;
    void setEntry(QuillMetadata::Tag tag, const QVariant &entry);
    void removeEntry(QuillMetadata::Tag tag);
    void removeEntries(QuillMetadata::TagGroup tagGroup);

    bool write(const QString &fileName) const;
    QByteArray dump() const;

 private:
    void initTags();

    void setExifEntry(ExifData *data, ExifTypedTag tag, const QVariant &value);

    void updateReferenceTag(ExifTag tag, bool positive);

    bool readShortTagAndByteOrder(const QuillMetadata::Tag tagToRead,
                                  const unsigned char *buf, const unsigned int bufSize,
                                  short &_tagValue, ExifByteOrder &_byteOrder);

 private:
    static QHash<QuillMetadata::Tag,ExifTypedTag> m_exifTags;

    ExifData *m_exifData;
    ExifByteOrder m_exifByteOrder;
    bool m_containsData;
    static bool m_initialized;
};

#endif
