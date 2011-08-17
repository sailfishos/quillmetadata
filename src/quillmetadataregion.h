
/****************************************************************************
**
** Copyright (C) 2009-11 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Pekka Marjola <pekka.marjola@nokia.com>
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

#ifndef QUILLMETADATAREGION_H
#define QUILLMETADATAREGION_H

#include <QRect>
#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>


/*** QuillMetadataRegion ***/
class QuillMetadataRegionPrivate;

class QuillMetadataRegion
{
    // Permissions to relative coordinate usage
    friend class QuillMetadataRegionList;
    friend class Xmp;
public:

    QuillMetadataRegion();
    ~QuillMetadataRegion();
    QuillMetadataRegion(const QuillMetadataRegion & other);

    void setType(const QString & type);
    QString type() const;

    void setName(const QString & name);
    QString name() const;

    void setArea(const QRect & area);
    QRect area() const;

    void setExtension(const QString &value);
    QString extension() const;

    void setExtension(const QString &xmpTag, const QVariant &value);
    QVariant extension(const QString &xmpTag) const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &other);

    static const QLatin1String RegionType_Face;
    static const QLatin1String RegionType_Pet;
    static const QLatin1String RegionType_Focus;
    static const QLatin1String RegionType_BarCode;

private:
    QSharedDataPointer<QuillMetadataRegionPrivate> d;

    void   setAreaF(const QRectF & area);
    QRectF areaF() const;

    QList<QString> listExtensionTags() const;
};



Q_DECLARE_METATYPE(QuillMetadataRegion);

#endif // QUILLMETADATAREGION_H
