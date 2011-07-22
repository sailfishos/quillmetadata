
/****************************************************************************
**
** Copyright (C) 2009-11 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Pekka Marjola <pekka.marjola@nokia.com>
**
** This file is part of the Quill Metadata package.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "quillmetadataregionlist.h"
#include <QDebug>
#include <QtCore/qmath.h>

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

