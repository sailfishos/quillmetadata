#ifndef QUILLMETADATAREGION_H
#define QUILLMETADATAREGION_H

#include <QRect>
#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>


/*** QuillMetadataRegion ***/
class QuillMetadataRegionPrivate;

class QuillMetadataRegion
{
    // Permissions to relative coordinate usage
    friend class QuillMetadataRegionList;
    friend class Xmp;
public:

    QuillMetadataRegion();
    ~QuillMetadataRegion();
    QuillMetadataRegion(const QuillMetadataRegion & other);

    void setType(const QString & type);
    QString type() const;

    void setName(const QString & name);
    QString name() const;

    void setArea(const QRect & area);
    QRect area() const;

    void setExtension(const QString &value);
    QString extension() const;

    void setExtension(const QString &xmpTag, const QVariant &value);
    QVariant extension(const QString &xmpTag) const;

    QuillMetadataRegion & operator=(const QuillMetadataRegion &other);

    static const QLatin1String RegionType_Face;
    static const QLatin1String RegionType_Pet;
    static const QLatin1String RegionType_Focus;
    static const QLatin1String RegionType_BarCode;

private:
    QSharedDataPointer<QuillMetadataRegionPrivate> d;

    void   setAreaF(const QRectF & area);
    QRectF areaF() const;

    QList<QString> listExtensionTags() const;
};



Q_DECLARE_METATYPE(QuillMetadataRegion);

#endif // QUILLMETADATAREGION_H
