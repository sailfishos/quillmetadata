#include "quillmetadataregions.h"

#include <QDebug>
#include <QtCore/qmath.h>

/*** QuillMeatadataRegion ***/

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
    d->areaF = other.d->areaF;
    d->type  = other.d->type;
    d->name  = other.d->name;

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


/*** QuillMetadataRegionBag ***/

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

void QuillMetadataRegionBag::updatePixelCoordinates()
{
    QList<QuillMetadataRegion>::iterator region;
    for (region = begin(); region != end(); ++region) {
	region->setArea(relativeToPixelCoordinates(region->areaF()));
    }
}

void QuillMetadataRegionBag::updateRelativeCoordinates()
{
    QList<QuillMetadataRegion>::iterator region;
    for (region = begin(); region != end(); ++region) {
	QRectF relative = pixelToRelativeCoordinates(region->area());
	if (region->area() != relativeToPixelCoordinates(region->areaF())) {
	    // If new relative coords produce same pixel coords
	    // as the old ones, don't update.
	    region->setAreaF(relative);
	}
    }
}

QRectF QuillMetadataRegionBag::pixelToRelativeCoordinates(const QRect &relative) const
{
    return QRectF(
	    (float)(relative.left())   / fullImageSize().width(),
	    (float)(relative.top())    / fullImageSize().height(),
	    (float)(relative.width())  / fullImageSize().width(),
	    (float)(relative.height()) / fullImageSize().height());
}

QRect QuillMetadataRegionBag::relativeToPixelCoordinates(const QRectF &pixel) const
{
    return QRect(
	    qFloor(pixel.left()	    * fullImageSize().width()   + .5),
	    qFloor(pixel.top()	    * fullImageSize().height()  + .5),
	    qFloor(pixel.width()    * fullImageSize().width()   + .5),
	    qFloor(pixel.height()   * fullImageSize().height()  + .5));
}
