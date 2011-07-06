#ifndef QUILLMETADATAREGIONS_H
#define QUILLMETADATAREGIONS_H

#include <QRect>
#include <QList>
#include <QString>
#include <QMetaType>

class QuillMetadataRegion
{
public:
    QuillMetadataRegion();
    QuillMetadataRegion(const QuillMetadataRegion & other);

    void setRegionType(const QString & type);
    QString RegionType() const;

    void setArea( const QRectF & area);
    QRectF Area() const;

    void setName(const QString & name);
    QString Name() const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &rhs);

private:
    QRectF area;
    QString type;
    QString name;
};


class QuillMetadataRegionBag : public QList<QuillMetadataRegion>
{
public:
    void setFullImageSize(const QSize & dimension);
    QSize FullImageSize() const;

private:
    QSize fullImageSize;

    QList<QuillMetadataRegion> regionList;
};

Q_DECLARE_METATYPE(QuillMetadataRegion);
Q_DECLARE_METATYPE(QuillMetadataRegionBag);

#endif // QUILLMETADATAREGIONS_H
