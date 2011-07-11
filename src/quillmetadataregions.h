#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>
#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>

class QuillMetadataRegionPrivate: public QSharedData

{
public:
    QuillMetadataRegionPrivate(){};
    QuillMetadataRegionPrivate(const QuillMetadataRegionPrivate& other)
        :QSharedData(other),area(other.area),
         type(other.type),name(other.name)
        {};
    ~QuillMetadataRegionPrivate(){};
    QRectF area;
    QString type;
    QString name;
};

class QuillMetadataRegion
{
public:

    QuillMetadataRegion();
    QuillMetadataRegion(const QuillMetadataRegion & other);

    void setRegionType(const QString & type);
    QString regionType() const;

    void setArea( const QRectF & area);
    QRectF area() const;

    void setName(const QString & name);
    QString name() const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &other);

    static const QLatin1String RegionType_Face;
    static const QLatin1String RegionType_Pet;
    static const QLatin1String RegionType_Focus;
    static const QLatin1String RegionType_BarCode;

private:
    QSharedDataPointer<QuillMetadataRegionPrivate> d;
};

class QuillMetadataRegionBagPrivate: public QSharedData
{
public:
    QuillMetadataRegionBagPrivate(){};
    ~QuillMetadataRegionBagPrivate(){};
    QSize fullImageSize;
};

class QuillMetadataRegionBag : public QList<QuillMetadataRegion>
{
public:
    QuillMetadataRegionBag();
    void setFullImageSize(const QSize & dimension);
    QSize fullImageSize() const;

    QuillMetadataRegionBag & operator=(const QuillMetadataRegionBag &other);

private:
    QSharedDataPointer<QuillMetadataRegionBagPrivate> d;
};

Q_DECLARE_METATYPE(QuillMetadataRegion);
Q_DECLARE_METATYPE(QuillMetadataRegionBag);

#endif // QUILLMETADATAREGIONS_H
