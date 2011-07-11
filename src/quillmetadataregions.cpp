#include "quillmetadataregions.h"

#include <QDebug>

/*** QuillMeatadataRegion Definitions ***/

QuillMetadataRegion::QuillMetadataRegion()
{
}

QuillMetadataRegion::QuillMetadataRegion(const QuillMetadataRegion & other)
{
    m_area = other.m_area;
    m_type = other.m_type;
    m_name = other.m_name;
}


void QuillMetadataRegion::setRegionType(const QString & regionType)
{
    m_type = regionType;
}

QString QuillMetadataRegion::regionType() const
{
    return m_type;
}

void QuillMetadataRegion::setArea(const QRectF & areaValue)
{
    m_area = areaValue;
}

QRectF QuillMetadataRegion::area() const
{
    return m_area;
}

void QuillMetadataRegion::setName(const QString & nameValue)
{
    m_name = nameValue;
}

QString QuillMetadataRegion::name() const
{
    return m_name;
}

QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &other)
{
    if (this == &other)
	return *this;

    m_area = other.m_area;
    m_type = other.m_type;
    m_name = other.m_name;

    return *this;
}

/*** QuillMeatadataRegionBag Definitions ***/

void QuillMetadataRegionBag::setFullImageSize(const QSize & dimensionValue)
{
    m_fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionBag::fullImageSize() const
{
    return m_fullImageSize;
}

QuillMetadataRegionBag& QuillMetadataRegionBag::operator=(const QuillMetadataRegionBag &other)
{
    if (this == &other)
	return *this;

    this->m_fullImageSize = other.m_fullImageSize;
    this->clear();
    QList<QuillMetadataRegion>::operator =(other);

    return *this;
}
