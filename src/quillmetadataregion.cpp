#include "quillmetadataregion.h"
#include <QDebug>
#include <QtCore/qmath.h>


/*** QuillMeatadataRegion ***/


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

void QuillMetadataRegion::setExtension(const QString& extensionValue)
{
    d->trackerContact = extensionValue;
}

QString QuillMetadataRegion::extension() const
{
    return d->trackerContact;
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

