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
        //! Subject, keywords or tags, string list (XMP/DC)
        Tag_Subject,
        //! City represented, string (XMP/IPTC or Photoshop)
        Tag_City,
        //! Country represented, string (XMP/IPTC or Photoshop)
        Tag_Country,
        //! Precise location (landmark or address), string (XMP/IPTC)
        Tag_Location,
        //! Rating in stars (0-5), float (XMP/XAP)
        Tag_Rating,
        //! Time of last modification, string (XMP/XAP)
        Tag_Timestamp,
        //! Image orientation, short (EXIF)
        Tag_Orientation,
        //! Description, string (XMP/DC)
        Tag_Description,
        //! GPS latitude, string (XMP/EXIF)
        Tag_GPSLatitude,
        //! GPS latitude is north or south (EXIF)
        Tag_GPSLatitudeRef,
        //! GPS longitude, string (XMP/EXIF)
        Tag_GPSLongitude,
        //! GPS longitude is east or west (EXIF)
        Tag_GPSLongitudeRef,
        //! GPS altitude, string (XMP/EXIF)
        Tag_GPSAltitude,
        //! GPS altitude above or below sea level, string (XMP/EXIF)
        Tag_GPSAltitudeRef,
        //! GPS version ID, string (XMP/EXIF)
        Tag_GPSVersionID,
        //! GPS image direction of the image when captured (EXIF)
        Tag_GPSImgDirection,
        //! GPS image direction reference (EXIF)
        Tag_GPSImgDirectionRef,
        //! Undefined tag
        Tag_Undefined,
    };

    enum TagGroup {
        //! All defined tags
        TagGroup_All = 0,
        //! GPS tags
        TagGroup_GPS
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

      @param formats Which formats to read (currently only supports ExifFormat
      and AllFormats)
     */

    QuillMetadata(const QString &fileName,
                  MetadataFormatFlags formats = AllFormats);

    /*!
      Constructs a metadata object containing all metadata from a given file.

      @param filePath Local filesystem path to file to be read.

      @param formats Which formats to read (currently only supports ExifFormat
      and AllFormats)

      @param tagToRead Which tags to read; if undefined, reads all tags
     */

    explicit QuillMetadata(const QString &fileName,
                  MetadataFormatFlags formats,
                  Tag tagToRead);

    /*!
      Removes a metadata object.
     */
    ~QuillMetadata();

    /*!
      Returns true if the image format of a given file is supported by
      the metadata reader. It will only make a lightweight check of
      the file headers, and it will not guarantee that any metadata can
      be actually be read from the file.
     */

    static bool canRead(const QString &filePath);

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
      Removes a list of entries.
      Currently, instead of removing, overwrites the entry with an empty
      content.
     */
    void removeEntries(const QList<Tag> &tags);

    /*!
      Removes a preset group of entries.
      Currently, instead of removing, overwrites the entry with an empty
      content.
     */
    void removeEntries(TagGroup tagGroup);

    /*!
      Writes the metadata object into an existing file, writes both
      XMP, IPTC-IIM (transparently by exempi) and EXIF blocks. Any
      existing metadata in the file will be lost by this overwrite.

      @param filePath Local filesystem path to file to be written into.

      @param formats Which metadata formats to write. If AllFormats is
      selected, both Exif and XMP metadata will be written. If
      ExifFormat is selected, it will destroy any existing XMP block
      in the file. If XmpFormat is selected, it should not affect
      existing Exif blocks in the file except those affected by
      automated reconciliation. XmpFormat and AllFormats also include
      IPTC-IIM reconciliation.
     */
    bool write(const QString &filePath,
               MetadataFormatFlags formats = AllFormats) const;

    /*!
      Dumps an EXIF or XMP block into a byte array.

      @param formats Which metadata block to dump. Currently only
      supports ExifFormat, other format flags will return an empty
      byte array.
     */
    QByteArray dump(MetadataFormatFlags formats) const;

 private:
    void init();

 private:
    QuillMetadataPrivate *priv;
};

#endif
