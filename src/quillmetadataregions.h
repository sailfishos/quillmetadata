#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>
#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>



/*** QuillMetadataRegionBag ***/
class QuillMetadataRegion;

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

    void    updatePixelCoordinates();   // Call after reading relative coordinates (QRectF)
    void    updateRelativeCoordinates();// Call before writing relative coordinates
    QRectF  pixelToRelativeCoordinates(const QRect &relative) const;
    QRect   relativeToPixelCoordinates(const QRectF &pixel) const;

};

/*** QuillMetadataRegion ***/

class QuillMetadataRegionPrivate: public QSharedData

{
public:
    QuillMetadataRegionPrivate(){};
    QuillMetadataRegionPrivate(const QuillMetadataRegionPrivate& other)
	:QSharedData(other),area(other.area),areaF(other.areaF),
         type(other.type),name(other.name),trackerContact(other.trackerContact)
        {};

    ~QuillMetadataRegionPrivate(){};
    QRect  area;
    QRectF  areaF; // Used when reading and writing relative coordinates
    QString type;
    QString name;
    QString trackerContact;
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

    void setExtension(const QString& trackContact);
    QString extension() const;

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
