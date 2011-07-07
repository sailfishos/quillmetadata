/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Alexander Bokovoy <alexander.bokovoy@nokia.com>
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

#ifndef XMP_H
#define XMP_H

#include <exempi-2.0/exempi/xmp.h>
#include <QHash>

#include "metadatarepresentation.h"


class XmpTag {
public:
    enum TagType {
        TagTypeString,
        TagTypeStringList,
	TagTypeAltLang,
	TagTypeRegions
    };

    XmpTag(const QString &schema, const QString &tag, TagType tagType);

    QString schema;
    QString tag;
    TagType tagType;
};

class Xmp : public MetadataRepresentation
{
 public:

    Xmp();
    Xmp(const QString &fileName);
    ~Xmp();

    bool isValid() const;

    bool supportsEntry(QuillMetadata::Tag tag) const;
    bool hasEntry(QuillMetadata::Tag tag) const;
    QVariant entry(QuillMetadata::Tag tag) const;
    void setEntry(QuillMetadata::Tag tag, const QVariant &entry);
    void removeEntry(QuillMetadata::Tag tag);

    bool write(const QString &fileName) const;

 private:
    void initTags();

    static QString processXmpString(XmpStringPtr xmpString);

    void setXmpEntry(QuillMetadata::Tag tag, const QVariant &entry);

    void readRegionListItem(const QString & qPropValue,
			    const QString & qPropName,
			    QuillMetadataRegionBag & regions) const;

 private:
    static QHash<QuillMetadata::Tag,XmpTag> m_xmpTags;

    XmpPtr m_xmpPtr;

    static bool m_initialized;
};

#endif
