#ifndef QUILLMETADATAREGIONLIST_H
#define QUILLMETADATAREGIONLIST_H

#include <QString>
#include <QMetaType>
#include <QSharedDataPointer>

#include "quillmetadataregion.h"

/*** QuillMetadataRegionList ***/
class QuillMetadataRegionListPrivate;


class QuillMetadataRegionList : public QList<QuillMetadataRegion>
{
    friend class Xmp; // Permission to use relative coordinates
public:
    QuillMetadataRegionList();
    ~QuillMetadataRegionList();
    QuillMetadataRegionList(const QuillMetadataRegionList & other);

    void setFullImageSize(const QSize & dimension);
    QSize fullImageSize() const;

    QuillMetadataRegionList & operator=(const QuillMetadataRegionList &other);

private:
    QSharedDataPointer<QuillMetadataRegionListPrivate> d;

    void    updatePixelCoordinates();   // Call after reading relative coordinates (QRectF)
    void    updateRelativeCoordinates();// Call before writing relative coordinates
    QRectF  pixelToRelativeCoordinates(const QRect &relative) const;
    QRect   relativeToPixelCoordinates(const QRectF &pixel) const;

};

Q_DECLARE_METATYPE(QuillMetadataRegionList);

#endif // QUILLMETADATAREGIONLIST_H
