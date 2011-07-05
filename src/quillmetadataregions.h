#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>


enum RegionType { Face, Pet, Focus, BarCode };

class RegionInfo
{
public:
    QRectF area;
    RegionType type;
    QString name;
};

class Regions
{
public:
    QList<RegionInfo> regionList;
    QSize imageDimensions;
};


#endif // QUILLMETADATAREGIONS_H
