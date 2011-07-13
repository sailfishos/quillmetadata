#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>
#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>



/*** QuillMetadataRegionBag ***/
class QuillMetadataRegion;
class QuillMetadataRegionFloatingPoints;

class QuillMetadataRegionBagPrivate: public QSharedData
{
public:
    QuillMetadataRegionBagPrivate(){};
    ~QuillMetadataRegionBagPrivate(){};
    QSize fullImageSize;
};


class QuillMetadataRegionBag : public QList<QuillMetadataRegion>
{
    friend class Xmp; // Permission to use relative coordinates
public:
    QuillMetadataRegionBag();
    void setFullImageSize(const QSize & dimension);
    QSize fullImageSize() const;

    QuillMetadataRegionBag & operator=(const QuillMetadataRegionBag &other);

private:
    QSharedDataPointer<QuillMetadataRegionBagPrivate> d;

    void updatePixelCoordinates();
    void updateRelativeCoordinates();

};


/*** QuillMetadataRegion ***/

class QuillMetadataRegionPrivate: public QSharedData

{
public:
    QuillMetadataRegionPrivate(){};
    QuillMetadataRegionPrivate(const QuillMetadataRegionPrivate& other)
	:QSharedData(other),area(other.area),areaF(other.areaF),
	 type(other.type),name(other.name)
	{};
    ~QuillMetadataRegionPrivate(){};
    QRect   area;
    QRectF  areaF;
    QString type;
    QString name;
};

class QuillMetadataRegion
{
    // Permissions to relative coordinate usage
    friend class QuillMetadataRegionBag;
    friend class Xmp;
public:

    QuillMetadataRegion();
    QuillMetadataRegion(const QuillMetadataRegion & other);

    void setRegionType(const QString & type);
    QString regionType() const;

    void setName(const QString & name);
    QString name() const;

    void setArea(const QRect & area);
    QRect area() const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &other);

    static const QLatin1String RegionType_Face;
    static const QLatin1String RegionType_Pet;
    static const QLatin1String RegionType_Focus;
    static const QLatin1String RegionType_BarCode;

private:
    QSharedDataPointer<QuillMetadataRegionPrivate> d;

    void   setAreaF(const QRectF & area);
    QRectF areaF() const;
};


Q_DECLARE_METATYPE(QuillMetadataRegion);
Q_DECLARE_METATYPE(QuillMetadataRegionBag);

#endif // QUILLMETADATAREGIONS_H
