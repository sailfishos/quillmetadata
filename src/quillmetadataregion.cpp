#include "quillmetadataregion.h"
#include <QVariant>
#include <QDebug>
#include <QtCore/qmath.h>

class QuillMetadataRegionPrivate: public QSharedData

{
public:
    QuillMetadataRegionPrivate(){};
    QuillMetadataRegionPrivate(const QuillMetadataRegionPrivate& other)
	:QSharedData(other),area(other.area),areaF(other.areaF),
	type(other.type),name(other.name),extensions(other.extensions)
    {};

    ~QuillMetadataRegionPrivate(){};
    QRect  area;
    QRectF  areaF; // Used when reading and writing relative coordinates
    QString type;
    QString name;
    QMap<QString, QVariant> extensions;
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

void QuillMetadataRegion::setExtension(const QString& value)
{
    Q_UNUSED(value);
}

QString QuillMetadataRegion::extension() const
{
    return QString();
}

void QuillMetadataRegion::setExtension(const QString& tag,
                                       const QVariant &value)
{
    d->extensions.insert(tag, value);
}

QVariant QuillMetadataRegion::extension(const QString& tag) const
{
    return d->extensions.value(tag);
}

QList<QString> QuillMetadataRegion::listExtensionTags() const
{
    return d->extensions.keys();
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

