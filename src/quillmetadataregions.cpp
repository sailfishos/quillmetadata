#include "quillmetadataregions.h"

#include <QDebug>


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

QuillMetadataRegion& QuillMetadataRegion::operator=(const QuillMetadataRegion &rhs)
{
    if (this == &rhs)
	return *this;

    m_area = rhs.m_area;
    m_type = rhs.m_type;
    m_name = rhs.m_name;

    return *this;
}



void QuillMetadataRegionBag::setFullImageSize(const QSize & dimensionValue)
{
    m_fullImageSize = dimensionValue;
}

QSize QuillMetadataRegionBag::fullImageSize() const
{
    return m_fullImageSize;
}

