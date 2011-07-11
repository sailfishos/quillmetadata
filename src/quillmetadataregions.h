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
    QString regionType() const;

    void setArea( const QRectF & area);
    QRectF area() const;

    void setName(const QString & name);
    QString name() const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &rhs);

private:
    QRectF m_area;
    QString m_type;
    QString m_name;
};


class QuillMetadataRegionBag : public QList<QuillMetadataRegion>
{
public:
    void setFullImageSize(const QSize & dimension);
    QSize fullImageSize() const;

private:
    QSize m_fullImageSize;
};

Q_DECLARE_METATYPE(QuillMetadataRegion);
Q_DECLARE_METATYPE(QuillMetadataRegionBag);

#endif // QUILLMETADATAREGIONS_H
