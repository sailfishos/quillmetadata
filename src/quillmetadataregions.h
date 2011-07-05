#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>


enum RegionType { Face, Pet, Focus, BarCode };

class RegionInfo
{
public:
    RegionInfo()
    {
	area = new QRectF();
    }

    QRectF *area;
    RegionType type;
    QString name;
    QString extension;
};

class Regions
{
public:
    QList<RegionInfo*> regionList;
    QSize imageDimensions;

    RegionInfo* operator[] (int i)
    {
	return regionList.at(i);
    }
};


#endif // QUILLMETADATAREGIONS_H
