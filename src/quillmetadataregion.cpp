
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

#include "quillmetadataregion.h"
#include <QVariant>
#include <QDebug>
#include <QtCore/qmath.h>

class QuillMetadataRegionPrivate: public QSharedData

{
public:
    QuillMetadataRegionPrivate(){};
    QuillMetadataRegionPrivate(const QuillMetadataRegionPrivate& other)
	:QSharedData(other),area(other.area),areaF(other.areaF),
	type(other.type),name(other.name),extensions(other.extensions)
    {};

    ~QuillMetadataRegionPrivate(){};
    QRect  area;
    QRectF  areaF; // Used when reading and writing relative coordinates
    QString type;
    QString name;
    QMap<QString, QVariant> extensions;
};

const QLatin1String QuillMetadataRegion::RegionType_Face    ("Face");
const QLatin1String QuillMetadataRegion::RegionType_Pet	    ("Pet");
const QLatin1String QuillMetadataRegion::RegionType_Focus   ("Focus");
const QLatin1String QuillMetadataRegion::RegionType_BarCode ("BarCode");

QuillMetadataRegion::QuillMetadataRegion()
{
    d = new QuillMetadataRegionPrivate;
}

QuillMetadataRegion::QuillMetadataRegion(const QuillMetadataRegion & other)
    :d(other.d)
{
}

QuillMetadataRegion::~QuillMetadataRegion()
{
}

void QuillMetadataRegion::setArea(const QRect & areaValue)
{
    d->area = areaValue;
}
QRect QuillMetadataRegion::area() const
{
    return d->area;
}

void QuillMetadataRegion::setType(const QString & regionType)
{
    d->type = regionType;
}

QString QuillMetadataRegion::type() const
{
    return d->type;
}

void QuillMetadataRegion::setName(const QString & nameValue)
{
    d->name = nameValue;
}

QString QuillMetadataRegion::name() const
{
    return d->name;
}

void QuillMetadataRegion::setExtension(const QString& value)
{
    Q_UNUSED(value);
}

QString QuillMetadataRegion::extension() const
{
    return QString();
}

void QuillMetadataRegion::setExtension(const QString& tag,
                                       const QVariant &value)
{
    d->extensions.insert(tag, value);
}

QVariant QuillMetadataRegion::extension(const QString& tag) const
{
    return d->extensions.value(tag);
}

QList<QString> QuillMetadataRegion::listExtensionTags() const
{
    return d->extensions.keys();
}

QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &other)
{
    if (this == &other)
	return *this;

    d = other.d;

    return *this;
}

void QuillMetadataRegion::setAreaF(const QRectF & areaValue)
{
    d->areaF = areaValue;
}

QRectF QuillMetadataRegion::areaF() const
{
    return d->areaF;
}

