#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>
#include <QString>

class RegionInfo
{
public:
    RegionInfo()
    {
    }

    enum RegionType { Face, Pet, Focus, BarCode };
    void setRegionType(RegionType type);
    RegionType getRegionType();
    void setArea(QRectF area);
    QRectF getArea();
    void setName(QString name);
    QString getName();
    void setDimensions(QSize dimension);
    QSize getDimensions();

private:
    QRectF area;
    RegionType type;
    QString name;
    QSize imageDimensions;

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
