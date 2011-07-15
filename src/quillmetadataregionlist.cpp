#include "quillmetadataregionlist.h"
#include <QDebug>
#include <QtCore/qmath.h>

/*** QuillMetadataRegionList ***/

class QuillMetadataRegionListPrivate: public QSharedData
{
public:
    QuillMetadataRegionListPrivate(){};
    ~QuillMetadataRegionListPrivate(){};
    QSize fullImageSize;
};



QuillMetadataRegionList::QuillMetadataRegionList()
{
    d = new QuillMetadataRegionListPrivate;
}

QuillMetadataRegionList::QuillMetadataRegionList(const QuillMetadataRegionList & other)
    :QList<QuillMetadataRegion>( other ),  d(other.d)
{
}

QuillMetadataRegionList::~QuillMetadataRegionList()
{
}

void QuillMetadataRegionList::setFullImageSize(const QSize & dimensionValue)
{
    d->fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionList::fullImageSize() const
{
    return d->fullImageSize;
}

QuillMetadataRegionList& QuillMetadataRegionList::operator=(const QuillMetadataRegionList &other)
							 {
    if (this == &other)
	return *this;

    d = other.d;
    QList<QuillMetadataRegion>::operator =(other);

    return *this;
}

void QuillMetadataRegionList::updatePixelCoordinates()
{
    QList<QuillMetadataRegion>::iterator region;
    for (region = begin(); region != end(); ++region) {
	region->setArea(relativeToPixelCoordinates(region->areaF()));
    }
}

void QuillMetadataRegionList::updateRelativeCoordinates()
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

QRectF QuillMetadataRegionList::pixelToRelativeCoordinates(const QRect &relative) const
{
    return QRectF(
	    (float)(relative.left())   / fullImageSize().width(),
	    (float)(relative.top())    / fullImageSize().height(),
	    (float)(relative.width())  / fullImageSize().width(),
	    (float)(relative.height()) / fullImageSize().height());
}

QRect QuillMetadataRegionList::relativeToPixelCoordinates(const QRectF &pixel) const
{
    return QRect(
	    qFloor(pixel.left()	    * fullImageSize().width()   + .5),
	    qFloor(pixel.top()	    * fullImageSize().height()  + .5),
	    qFloor(pixel.width()    * fullImageSize().width()   + .5),
	    qFloor(pixel.height()   * fullImageSize().height()  + .5));
}

