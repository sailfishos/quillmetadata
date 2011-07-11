#include <QSharedData>
#include "quillmetadataregions.h"

#include <QDebug>

/*** QuillMeatadataRegion Definitions ***/

const QLatin1String QuillMetadataRegion::RegionType_Face("Face");
const QLatin1String QuillMetadataRegion::RegionType_Pet("Pet");
const QLatin1String QuillMetadataRegion::RegionType_Focus("Focus");
const QLatin1String QuillMetadataRegion::RegionType_BarCode("BarCode");

QuillMetadataRegion::QuillMetadataRegion()
{
    d = new QuillMetadataRegionPrivate;
}

QuillMetadataRegion::QuillMetadataRegion(const QuillMetadataRegion & other)
    :d(other.d)
{
}

void QuillMetadataRegion::setRegionType(const QString & regionType)
{
    d->type = regionType;
}

QString QuillMetadataRegion::regionType() const
{
    return d->type;
}

void QuillMetadataRegion::setArea(const QRectF & areaValue)
{
    d->area = areaValue;
}

QRectF QuillMetadataRegion::area() const
{
    return d->area;
}

void QuillMetadataRegion::setName(const QString & nameValue)
{
    d->name = nameValue;
}

QString QuillMetadataRegion::name() const
{
    return d->name;
}

QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &other)
{
    if (this == &other)
	return *this;

    d->area = other.d->area;
    d->type = other.d->type;
    d->name = other.d->name;

    return *this;
}

/*** QuillMeatadataRegionBag Definitions ***/

QuillMetadataRegionBag::QuillMetadataRegionBag()
{
    d = new QuillMetadataRegionBagPrivate;
}

void QuillMetadataRegionBag::setFullImageSize(const QSize & dimensionValue)
{
    d->fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionBag::fullImageSize() const
{
    return d->fullImageSize;
}

QuillMetadataRegionBag& QuillMetadataRegionBag::operator=(const QuillMetadataRegionBag &other)
{
    if (this == &other)
	return *this;

    d->fullImageSize = other.d->fullImageSize;
    this->clear();
    QList<QuillMetadataRegion>::operator =(other);

    return *this;
}
