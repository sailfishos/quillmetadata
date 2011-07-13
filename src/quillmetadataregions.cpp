#include "quillmetadataregions.h"

#include <QDebug>
#include <QtCore/qmath.h>

/*** QuillMeatadataRegion Definitions ***/

const QLatin1String QuillMetadataRegion::RegionType_Face("Face");
const QLatin1String QuillMetadataRegion::RegionType_Pet("Pet");
const QLatin1String QuillMetadataRegion::RegionType_Focus("Focus");
const QLatin1String QuillMetadataRegion::RegionType_BarCode("BarCode");

QuillMetadataRegion::QuillMetadataRegion()
{
    d = new QuillMetadataRegionPrivate;
}

QuillMetadataRegion::QuillMetadataRegion(const QuillMetadataRegion & other)
    :d(other.d)
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

void QuillMetadataRegion::setRegionType(const QString & regionType)
{
    d->type = regionType;
}

QString QuillMetadataRegion::regionType() const
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
    d->trackContact = extensionValue;
}

QString QuillMetadataRegion::extension() const
{
    return d->trackContact;
}
QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &other)
{
    if (this == &other)
	return *this;

    d->area  = other.d->area;
    d->type  = other.d->type;
    d->name  = other.d->name;

    return *this;
}

void QuillMetadataRegionFloatingPoints::setAreaF(const QRectF & areaValue)
{
    m_areaF = areaValue;
}

QRectF QuillMetadataRegionFloatingPoints::areaF() const
{
    return m_areaF;
}

/*** QuillMetadataRegionBag Definitions ***/

QuillMetadataRegionBag::QuillMetadataRegionBag()
{
    d = new QuillMetadataRegionBagPrivate;
}

void QuillMetadataRegionBag::setFullImageSize(const QSize & dimensionValue)
{
    d->fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionBag::fullImageSize() const
{
    return d->fullImageSize;
}

QuillMetadataRegionBag& QuillMetadataRegionBag::operator=(const QuillMetadataRegionBag &other)
							 {
    if (this == &other)
	return *this;

    d->fullImageSize = other.d->fullImageSize;
    this->clear();
    QList<QuillMetadataRegion>::operator =(other);

    return *this;
}

void QuillMetadataRegionBag::setFloatingPointRegion(
	QuillMetadataRegionFloatingPoints & region,
	int i)
{
    QRect area = QRect(
	    qFloor(region.areaF().left()  * fullImageSize().width()
	    + .5),
	    qFloor(region.areaF().top()   * fullImageSize().height()
	    + .5),
	    qFloor(region.areaF().width() * fullImageSize().width()
	    + .5),
	    qFloor(region.areaF().height()* fullImageSize().height()
	    + .5));

    (*this)[i].setArea(area);
    (*this)[i].setName(region.name());
    (*this)[i].setRegionType(region.regionType());
}

QuillMetadataRegionFloatingPoints &
	QuillMetadataRegionBag::getFloatingPointRegion(int i)
{
    QuillMetadataRegionFloatingPoints *regionF =
	    new QuillMetadataRegionFloatingPoints();

    QuillMetadataRegion region = this->at(i);

    QRectF areaF = QRectF(
	    (float)(region.area().left())   / fullImageSize().width(),
	    (float)(region.area().top())    / fullImageSize().height(),
	    (float)(region.area().width())  / fullImageSize().width(),
	    (float)(region.area().height()) / fullImageSize().height());

    regionF->setAreaF(areaF);
    regionF->setArea(region.area());
    regionF->setName(region.name());
    regionF->setRegionType(region.regionType());

    return *regionF;
}
