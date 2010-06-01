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
};

QuillMetadata::QuillMetadata()
{
    priv = new QuillMetadataPrivate;
    priv->xmp = new Xmp();
    priv->exif = new Exif();
}

QuillMetadata::QuillMetadata(const QString &fileName)
{
    priv = new QuillMetadataPrivate;
    priv->xmp = new Xmp(fileName);
    priv->exif = new Exif(fileName);
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
}

void QuillMetadata::removeEntry(Tag tag)
{
    setEntry(tag, QVariant());
}

bool QuillMetadata::write(const QString &fileName,
                          MetadataFormatFlags formats) const
{
    if (formats == XmpFormat)
        return priv->xmp->write(fileName);
    else
        return priv->xmp->write(fileName) && priv->exif->write(fileName);
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
