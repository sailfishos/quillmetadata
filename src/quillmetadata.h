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
        //! Camera make, string (EXIF)
        Tag_Make,
        //! Camera model, string (EXIF)
        Tag_Model,
        //! Image width, int (EXIF, deprecated)
        Tag_ImageWidth,
        //! Image height, int (EXIF, deprecated)
        Tag_ImageHeight,
        //! Camera focal length, float (EXIF)
        Tag_FocalLength,
        //! Exposure time used, float (EXIF)
        Tag_ExposureTime,
        //! Time when picture was taken, string (EXIF)
        Tag_TimestampOriginal,
        //! Image title, string (XMP/DC)
        Tag_Title,
        //! Not supported
        Tag_Copyright,
        //! Creator of original image, string (XMP/DC)
        Tag_Creator,
        //! Not supported, see Subject
        Tag_Keywords,
        //! Subject, keywords or tags, string (XMP/DC)
        Tag_Subject,
        //! City represented, string (XMP/IPTC or Photoshop)
        Tag_City,
        //! Country represented, string (XMP/IPTC or Photoshop)
        Tag_Country,
        //! Precise location represented, string (XMP/IPTC)
        Tag_Location,
        //! Rating in stars (0-5), float (XMP/XAP)
        Tag_Rating,
        //! Time of last modification, string (XMP/XAP)
        Tag_Timestamp,
        //! Image orientation, short (EXIF)
        Tag_Orientation
    };

    /*!
      These flags can be used to limit working to a given metadata format.
     */

    enum MetadataFormatFlags {
        //! Operate on EXIF only
        ExifFormat = 0x1,
        //! Operate on XMP only
        XmpFormat = 0x2,
        //! Operate on all formats
        AllFormats = ~1
    };

 public:
    /*!
      Constructs an empty metadata object.
     */
    QuillMetadata();

    /*!
      Constructs a metadata object containing all metadata from a given file.

      @param filePath Local filesystem path to file to be read.
     */
    QuillMetadata(const QString &filePath);

    /*!
      Removes a metadata object.
     */
    ~QuillMetadata();

    /*!
      Returns true if the metadata object is valid.
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
      Removes an entry for a given tag. Currently, instead of removing,
      overwrites the entry with an empty content.
     */
    void removeEntry(Tag tag);

    /*!
      Writes the metadata object into an existing file, writes both
      XMP, IPTC-IIM (transparently by exempi) and EXIF blocks. Any
      existing metadata in the file will be lost by this overwrite.

      @param filePath Local filesystem path to file to be written into.

      @param formats Which metadata formats to write. Currently,
      only supports XmpFormat and AllFormats, ExifFormat will default to
      AllFormats. XmpFormat and AllFormats include IPTC-IIM reconciliation.
     */
    bool write(const QString &filePath,
               MetadataFormatFlags formats = AllFormats) const;

    /*!
      Dumps the EXIF block into a byte array so that it can be
      inserted to a file by a file compression library.

      Warning: this is deprecated and will be removed, please use dump()
      instead.
     */
    QByteArray dumpExif() const;

    /*!
      Dumps an EXIF or XMP block into a byte array.

      @param formats Which metadata block to dump. Currently only
      supports ExifFormat, other format flags will return an empty
      byte array.
     */
    QByteArray dump(MetadataFormatFlags formats) const;

 private:
    QuillMetadataPrivate *priv;
};

#endif
