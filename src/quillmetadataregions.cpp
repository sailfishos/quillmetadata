#include "quillmetadataregions.h"

#include <QDebug>


QuillMetadataRegion::QuillMetadataRegion()
{
}

QuillMetadataRegion::QuillMetadataRegion(const QuillMetadataRegion & other)
{
    area = other.area;
    type = other.type;
    name = other.name;
}


void QuillMetadataRegion::setRegionType(const QString & regionType)
{
    type = regionType;
}

QString QuillMetadataRegion::RegionType() const
{
    return type;
}

void QuillMetadataRegion::setArea(const QRectF & areaValue)
{
    area = areaValue;
}

QRectF QuillMetadataRegion::Area() const
{
    return area;
}

void QuillMetadataRegion::setName(const QString & nameValue)
{
    name = nameValue;
}

QString QuillMetadataRegion::Name() const
{
    return name;
}

QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &rhs)
{
    if (this == &rhs)
	return *this;

    area = rhs.area;
    type = rhs.type;
    name = rhs.name;

    return *this;
}



void QuillMetadataRegionBag::setFullImageSize(const QSize & dimensionValue)
{
    fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionBag::FullImageSize() const
{
    return fullImageSize;
}

