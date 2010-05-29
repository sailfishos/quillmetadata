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

#ifndef QUILL_METADATA_H
#define QUILL_METADATA_H

#include <exempi-2.0/exempi/xmp.h>
#include <QString>
#include <QVariant>

class QuillMetadataPrivate;

class QuillMetadata
{
 public:

    enum Tag {
        Tag_Make,
        Tag_Model,
        Tag_ImageWidth,
        Tag_ImageHeight,
        Tag_FocalLength,
        Tag_ExposureTime,
        Tag_TimestampOriginal,
        Tag_Title,
        Tag_Copyright,
        Tag_Creator,
        Tag_Keywords,
        Tag_Subject,
        Tag_City,
        Tag_Country,
        Tag_Location,
        Tag_Rating,
        Tag_Timestamp,
        Tag_Orientation
    };

 public:
    /*!
      Constructs an empty metadata object.
     */
    QuillMetadata();

    /*!
      Reads metadata from a given file.
     */
    QuillMetadata(const QString &fileName);
    ~QuillMetadata();

    /*!
      Returns true if the metadata in the file was valid.
     */
    bool isValid() const;

    /*!
      Returns the value of the metadata entry for a given tag.
      Currently, only some tags are supported.
     */
    QVariant entry(Tag tag) const;

    /*!
      Sets the value of the metadata entry for a given tag. Use
      invalid QVariant to clear the entry. Currently, only some tags are
      supported.
     */
    void setEntry(Tag tag, const QVariant &entry);

    /*!
      This function has been deprecated, please do not use.

      Writes the metadata into an existing file. Writes XMP and
      IPTC-IIM using libexempi, does not write EXIF data which should
      be written at the start of the save by the save filter.
    */
    bool write(const QString &fileName) const;

    /*!
      As libexif does not have a writeback feature, the EXIF block
      is dumped into a byte array instead to be processed by the save filter.
     */
    QByteArray dumpExif() const;

    /*!
      Writes the metadata into an existing file, writes both XMP, IPTC-IIM
      (transparently by exempi) and EXIF blocks.
     */
    bool writeAll(const QString &fileName) const;

 private:
    QuillMetadataPrivate *priv;
};

#endif
