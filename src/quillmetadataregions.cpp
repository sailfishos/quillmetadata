#include "quillmetadataregions.h"


void RegionInfo::setRegionType(RegionType regionType)
{
    type = regionType;
}

RegionInfo::RegionType RegionInfo::getRegionType()
{
    return type;
}

void RegionInfo::setArea(QRectF areaValue)
{
    area = areaValue;
}

QRectF RegionInfo::getArea()
{
    return area;
}

void RegionInfo::setName(QString nameValue)
{
    name = nameValue;
}

QString RegionInfo::getName()
{
    return name;
}

void RegionInfo::setDimensions(QSize dimensionValue)
{
    imageDimensions = dimensionValue;
}

QSize RegionInfo::getDimensions()
{
    return imageDimensions;
}

