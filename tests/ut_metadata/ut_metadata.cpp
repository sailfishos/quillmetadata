/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Alexander Bokovoy <alexander.bokovoy@nokia.com>
**
** This file is part of the Quill package.
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

#include <QVariant>
#include <QtTest/QtTest>

#include "quillmetadata.h"
#include "quillmetadataregions.h"
#include "ut_metadata.h"

#define PRECISION 10000

ut_metadata::ut_metadata()
{
}

void ut_metadata::initTestCase()
{
    sourceImage = QImage(QSize(8, 2), QImage::Format_RGB32);
    sourceImage.fill(qRgb(255, 255, 255));
}

void ut_metadata::cleanupTestCase()
{
}

void ut_metadata::init()
{
    metadata	= new QuillMetadata("/usr/share/libquillmetadata-tests/images/exif.jpg");
    xmp		= new QuillMetadata("/usr/share/libquillmetadata-tests/images/xmp.jpg");
    iptc	= new QuillMetadata("/usr/share/libquillmetadata-tests/images/iptc.jpg");
    gps		= new QuillMetadata("/usr/share/libquillmetadata-tests/images/gps.jpg");

    region	= new QuillMetadata("/usr/share/libquillmetadata-tests/images/mnaa.jpg");
}

void ut_metadata::cleanup()
{
    delete metadata;
    delete xmp;
    delete iptc;
    delete gps;

    delete region;
}

void ut_metadata::testCameraMake()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_Make).toString(), QString("Quill"));
}

void ut_metadata::testCameraModel()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_Model).toString(), QString("Q100125"));
}

void ut_metadata::testImageWidth()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_ImageWidth).toInt(), 2);
}

void ut_metadata::testImageHeight()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_ImageHeight).toInt(), 2);
}

void ut_metadata::testFocalLength()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(QString::number(metadata->entry(QuillMetadata::Tag_FocalLength).toDouble()), QString("9.9"));
}

void ut_metadata::testExposureTime()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(QString::number(metadata->entry(QuillMetadata::Tag_ExposureTime).toDouble()), QString("0.005"));
}

void ut_metadata::testTimestampOriginal()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_TimestampOriginal).toString(),
             QString("2010:01:25 15:00:00"));
}

void ut_metadata::testOrientation()
{
    QVERIFY(metadata->isValid());
    QCOMPARE(metadata->entry(QuillMetadata::Tag_Orientation).toString(),
             QString("3"));
}

void ut_metadata::testSubject()
{
    QVERIFY(xmp->isValid());
    QStringList reference;
    reference << "test" << "quill";
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Subject).toStringList(),
             reference);
}

void ut_metadata::testCity()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_City).toString(),
             QString("Tapiola"));
}

void ut_metadata::testCountry()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Country).toString(),
             QString("Finland"));
}

void ut_metadata::testRating()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Rating).toInt(),
             5);
}

void ut_metadata::testCreator()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Creator).toString(),
             QString("John Q"));
}

void ut_metadata::testDescription()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Description).toString(),
             QString("Snowman warming up"));
}

void ut_metadata::testTitle()
{
    QVERIFY(xmp->isValid());
    QCOMPARE(xmp->entry(QuillMetadata::Tag_Title).toString(),
             QString("Funny snowman"));
}

void ut_metadata::testCityIptc()
{
    QVERIFY(iptc->isValid());
    QCOMPARE(iptc->entry(QuillMetadata::Tag_City).toString(),
             QString("Tapiola"));
}

void ut_metadata::testCountryIptc()
{
    QVERIFY(iptc->isValid());
    QCOMPARE(iptc->entry(QuillMetadata::Tag_Country).toString(),
             QString("Finland"));
}

void ut_metadata::testWriteSubject()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    xmp->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QStringList reference;
    reference << "test" << "quill";
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Subject).toStringList(),
             reference);
}

void ut_metadata::testWriteCity()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    xmp->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_City).toString(),
             QString("Tapiola"));
}

void ut_metadata::testWriteCameraMake()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    metadata->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Make).toString(),
             QString("Quill"));
}

void ut_metadata::testWriteDescription()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    xmp->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Description).toString(),
             QString("Snowman warming up"));
}

void ut_metadata::testEditCameraMake()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_Make, QString("Quill"));
    empty.write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Make).toString(),
             QString("Quill"));
}

void ut_metadata::testEditOrientation()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_Orientation, QVariant(7));
    QVERIFY(empty.write(file.fileName()));

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Orientation).toString(),
             QString("7"));
}

void ut_metadata::testEditCity()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_City, QString("Tapiola"));
    empty.write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_City).toString(),
             QString("Tapiola"));
}

void ut_metadata::testEditKeywords()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    QStringList list;
    list << "aquarium" << "Neon Tetra" << "Paracheirodon innesi";

    empty.setEntry(QuillMetadata::Tag_Subject, list);
    empty.write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QStringList resultList =
        writtenMetadata.entry(QuillMetadata::Tag_Subject).toStringList();
    QCOMPARE(resultList, list);
}

void ut_metadata::testDoubleEditKeywords()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    QStringList list, list2;
    list << "aquarium" << "Neon Tetra" << "Paracheirodon innesi";
    list2 << "aquarium" << "Colombian Tetra" << "Hyphessobrycon columbianus";

    empty.setEntry(QuillMetadata::Tag_Subject, list);
    empty.setEntry(QuillMetadata::Tag_Subject, list2);
    empty.write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QStringList resultList =
        writtenMetadata.entry(QuillMetadata::Tag_Subject).toStringList();
    QCOMPARE(resultList, list2);
}

void ut_metadata::testEditDescription()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_Description,
                   QString("Fish"));
    QVERIFY(empty.write(file.fileName()));

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Description).toString(),
             QString("Fish"));
}

void ut_metadata::testEditTitle()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_Title,
                   QString("The Big Fish"));
    QVERIFY(empty.write(file.fileName()));

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Title).toString(),
             QString("The Big Fish"));
}

void ut_metadata::testCrossEdit()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    metadata->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    writtenMetadata.setEntry(QuillMetadata::Tag_Creator, QString("John Quill"));
    QVERIFY(writtenMetadata.write(file.fileName()));

    QuillMetadata writtenMetadata2(file.fileName());
    QVERIFY(writtenMetadata2.isValid());

    QCOMPARE(writtenMetadata2.entry(QuillMetadata::Tag_Creator).toString(),
             QString("John Quill"));
}

void ut_metadata::testCrossEdit2()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    xmp->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    writtenMetadata.setEntry(QuillMetadata::Tag_Make, QString("Quill"));
    QVERIFY(writtenMetadata.write(file.fileName()));

    QuillMetadata writtenMetadata2(file.fileName());
    QVERIFY(writtenMetadata2.isValid());

    QCOMPARE(writtenMetadata2.entry(QuillMetadata::Tag_Make).toString(),
             QString("Quill"));
}

void ut_metadata::testGps()
{
    QVERIFY(gps->isValid());
    QCOMPARE(gps->entry(QuillMetadata::Tag_GPSLatitude).toString(), QString("65"));
    QCOMPARE(gps->entry(QuillMetadata::Tag_GPSLongitude).toString(), QString("30"));
    QCOMPARE(gps->entry(QuillMetadata::Tag_GPSAltitude).toString(), QString("85"));
}

void ut_metadata::testWriteGps()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    gps->write(file.fileName());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSLatitude).toString(), QString("65"));
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSLongitude).toString(), QString("30"));
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSAltitude).toString(), QString("85"));
}

void ut_metadata::testGps_XmpExif()
{
    // TODO: Stop skipping the test once that it becomes possible to only read XMP data
    QSKIP("Reading only XMP data is still unsupported", SkipSingle);

    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    gps->write(file.fileName());

    QuillMetadata editMetadataEXIF(file.fileName(), QuillMetadata::ExifFormat);
    QuillMetadata editMetadataXMP(file.fileName(), QuillMetadata::XmpFormat);

    QVERIFY(editMetadataEXIF.isValid());
    QVERIFY(editMetadataXMP.isValid());

    // Latitude
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSLatitude).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSLatitude).toString());

    // Latitude REF
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSLatitudeRef).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSLatitudeRef).toString());

    // Longitude
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSLongitude).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSLongitude).toString());

    // Longitude REF
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSLongitudeRef).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSLongitudeRef).toString());

    // Altitude
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSAltitude).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSAltitude).toString());

    // Altitude REF
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSAltitudeRef).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSAltitudeRef).toString());

    // Direction
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSImgDirection).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSImgDirection).toString());

    // Direction REF
    QCOMPARE(editMetadataEXIF.entry(QuillMetadata::Tag_GPSImgDirectionRef).toString(),
             editMetadataXMP.entry(QuillMetadata::Tag_GPSImgDirectionRef).toString());
}

void ut_metadata::testEditGps_latitude()
{
    QuillMetadata editMetadata;
    double expected = 60.1639;
    double actual;

    QVERIFY(editMetadata.isValid());

    // Setting a latitude
    editMetadata.setEntry(QuillMetadata::Tag_GPSLatitude, QVariant(expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSLatitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLatitudeRef).toString(), QString("N"));

    // Setting a negative latitude (that is: the latitude reference should be now "S"outh)
    editMetadata.setEntry(QuillMetadata::Tag_GPSLatitude, QVariant(-expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSLatitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLatitudeRef).toString(), QString("S"));

    // 0 degrees latitude is "N"orth
    editMetadata.setEntry(QuillMetadata::Tag_GPSLatitude, QVariant(double(0)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLatitude).toString(), QString("0"));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLatitudeRef).toString(), QString("N"));

    // Manually setting the latitude reference
    editMetadata.setEntry(QuillMetadata::Tag_GPSLatitudeRef, QVariant(QString("S")));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLatitudeRef).toString(), QString("S"));
}

void ut_metadata::testEditGps_longitude()
{
    QuillMetadata editMetadata;
    double expected = 60.1639;
    double actual;

    QVERIFY(editMetadata.isValid());

    // Setting a setEntry
    editMetadata.setEntry(QuillMetadata::Tag_GPSLongitude, QVariant(expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSLongitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLongitudeRef).toString(), QString("E"));

    // Setting a negative longitude (that is: the longitude reference should be now "W"est)
    editMetadata.setEntry(QuillMetadata::Tag_GPSLongitude, QVariant(-expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSLongitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLongitudeRef).toString(), QString("W"));

    // 0 degrees longitude is "E"ast
    editMetadata.setEntry(QuillMetadata::Tag_GPSLongitude, QVariant(double(0)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLongitude).toString(), QString("0"));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLongitudeRef).toString(), QString("E"));

    // Manually setting the longitude reference
    editMetadata.setEntry(QuillMetadata::Tag_GPSLongitudeRef, QVariant(QString("W")));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSLongitudeRef).toString(), QString("W"));
}

void ut_metadata::testEditGps_altitude()
{
    QuillMetadata editMetadata;
    double expected = 60.1639;
    double actual;

    QVERIFY(editMetadata.isValid());

    // Setting a latitude
    editMetadata.setEntry(QuillMetadata::Tag_GPSAltitude, QVariant(expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSAltitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSAltitudeRef).toString(), QString("0"));

    // Setting a negative altitude (that is: the altitude reference should be now "1" (below sea level)
    editMetadata.setEntry(QuillMetadata::Tag_GPSAltitude, QVariant(-expected));
    actual = editMetadata.entry(QuillMetadata::Tag_GPSAltitude).toDouble();
    QCOMPARE(round(actual * PRECISION), round(expected * PRECISION));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSAltitudeRef).toString(), QString("1"));

    // 0 meters altitude is over sea level
    editMetadata.setEntry(QuillMetadata::Tag_GPSAltitude, QVariant(double(0)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSAltitude).toString(), QString("0"));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSAltitudeRef).toString(), QString("0"));

    // Manually setting the altitude reference
    editMetadata.setEntry(QuillMetadata::Tag_GPSAltitudeRef, QVariant(int(1)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSAltitudeRef).toString(), QString("1"));
}

void ut_metadata::testEditGps_direction()
{
    QuillMetadata editMetadata;

    QVERIFY(editMetadata.isValid());

    // Setting image direction between 0.00 and 359.99
    editMetadata.setEntry(QuillMetadata::Tag_GPSImgDirection, QVariant(double(25.25)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSImgDirection).toString(), QString("25.25"));

    // Setting image under 0.00
    editMetadata.setEntry(QuillMetadata::Tag_GPSImgDirection, QVariant(double(-15)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSImgDirection).toString(), QString("345"));

    // Setting image over 359.99
    editMetadata.setEntry(QuillMetadata::Tag_GPSImgDirection, QVariant(double(400)));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSImgDirection).toString(), QString("40"));

    // Manually setting the direction reference
    editMetadata.setEntry(QuillMetadata::Tag_GPSImgDirectionRef, QVariant(QString("T")));
    QCOMPARE(editMetadata.entry(QuillMetadata::Tag_GPSImgDirectionRef).toString(), QString("T"));
}

void ut_metadata::testClearGps()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");

    QuillMetadata gps("/usr/share/libquillmetadata-tests/images/gps.jpg");
    gps.removeEntries(QuillMetadata::TagGroup_GPS);
    QVERIFY(gps.write(file.fileName()));

    QCOMPARE(gps.entry(QuillMetadata::Tag_GPSLatitude).toString(), QString());
    QCOMPARE(gps.entry(QuillMetadata::Tag_GPSLongitude).toString(), QString());
    QCOMPARE(gps.entry(QuillMetadata::Tag_GPSAltitude).toString(), QString());

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());

    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSLatitude).toString(), QString(""));
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSLongitude).toString(), QString(""));
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_GPSAltitude).toString(), QString(""));
}

void ut_metadata::testCopyOrientation()
{
    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");

    QuillMetadata empty;
    empty.setEntry(QuillMetadata::Tag_Orientation,
                   metadata->entry(QuillMetadata::Tag_Orientation));
    QVERIFY(empty.write(file.fileName()));

    QuillMetadata writtenMetadata(file.fileName());
    QVERIFY(writtenMetadata.isValid());
    QCOMPARE(writtenMetadata.entry(QuillMetadata::Tag_Orientation).toString(),
             QString("3"));
}

void ut_metadata::testCanRead()
{
    QVERIFY(QuillMetadata::canRead("/usr/share/libquillmetadata-tests/images/exif.jpg"));
    QVERIFY(QuillMetadata::canRead("/usr/share/libquillmetadata-tests/images/iptc.jpg"));
    QVERIFY(QuillMetadata::canRead("/usr/share/libquillmetadata-tests/images/xmp.jpg"));
    QVERIFY(QuillMetadata::canRead("/usr/share/libquillmetadata-tests/images/gps.jpg"));

    QTemporaryFile file;
    file.open();
    QVERIFY(!QuillMetadata::canRead(file.fileName()));
}

//we add the case to test dump function by creating medatedata object with file name from other team.
void ut_metadata::testSetOrientationTag()
{
    QVERIFY(QuillMetadata::canRead("/usr/share/libquillmetadata-tests/images/exif.jpg"));
    metadata->setEntry(QuillMetadata::Tag_Orientation, QVariant(short(7)));
    QByteArray result = metadata->dump(QuillMetadata::ExifFormat);
    QVERIFY(!result.isNull());
}

void ut_metadata::testOrientationTagSpeedup()
{
    QString str("/usr/share/quillimagefilter-tests/images/16_color_palette.png");

    for (int i = 0; i<=8; i++){
        QTemporaryFile file;
        file.open();
        sourceImage.save(file.fileName(), "jpg");

        QuillMetadata empty;
        empty.setEntry(QuillMetadata::Tag_Orientation, QVariant(i));
        QVERIFY(empty.write(file.fileName()));

        int orientation1, orientation2;
        {
            QuillMetadata *metadata = new QuillMetadata(file.fileName(),
                                                        QuillMetadata::ExifFormat);
            QVERIFY(metadata->isValid());
            QCOMPARE(metadata->entry(QuillMetadata::Tag_Orientation).toInt(), i);

            orientation1 = metadata->entry(QuillMetadata::Tag_Orientation).toInt();

            delete metadata;
        }
        {
            QuillMetadata *metadata = new QuillMetadata(file.fileName(),
                                                        QuillMetadata::ExifFormat,
                                                        QuillMetadata::Tag_Orientation);
            QVERIFY(metadata->isValid());
            QCOMPARE(metadata->entry(QuillMetadata::Tag_Orientation).toInt(), i);
            orientation2 = metadata->entry(QuillMetadata::Tag_Orientation).toInt();

            delete metadata;
        }
        QCOMPARE(orientation1, orientation2);
    }
}



// Rounds to FUZZYACC precision, then asserts that difference is <= FUZZYACC
#define FUZZYACC 1.0
#define MYQCOMPARE(x, y) do {\
QVERIFY2(abs(((int)(x/FUZZYACC+.5)) -\
	     ((int)(y/FUZZYACC+.5))) <= 1,\
	 (QString("%1 vs. %2").arg(x).arg(y)).toAscii());} while (0)

void ut_metadata::testReadRegions()
{

    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag regs = data.value<QuillMetadataRegionBag>();
    QCOMPARE(regs.count(), 2);
    QCOMPARE(regs.fullImageSize().width(),  4288);
    QCOMPARE(regs.fullImageSize().height(), 2848);
    // Name:
    QCOMPARE(regs[0].name(), QString("Albert Einstein"));
    QCOMPARE(regs[1].name(), QString("Dilbert"));
    // Type:
    QCOMPARE(regs[0].regionType(), QString("Face"));
    QCOMPARE(regs[1].regionType(), QString("Face"));
    // Area:
    {
	QRectF area = regs[0].area();
	MYQCOMPARE(area.width(),	0.15*4288);
	MYQCOMPARE(area.height(),	0.17*2848);
	MYQCOMPARE(area.center().x(),	0.3*4288);
	MYQCOMPARE(area.center().y(),	0.4*2848);
    }
    {
	QRectF area = regs[1].area();
	MYQCOMPARE(area.width(),	0.17*4288);
	MYQCOMPARE(area.height(),	0.15*2848);
	MYQCOMPARE(area.center().x(),	0.4*4288);
	MYQCOMPARE(area.center().y(),	0.3*2848);
    }
}

void ut_metadata::testEditRegions()
{

    QVERIFY(region->isValid());
    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag bag = data.value<QuillMetadataRegionBag>();

    bag[0].setName(QString("This is foo name"));
    bag[0].setRegionType(QString("Pet"));
    QRect area;
    area.setWidth(1);
    area.setHeight(2);
    QPoint centerPoint(3, 4);
    area.moveCenter(centerPoint);
    bag[0].setArea(area);
    QVariant entry;
    entry.setValue(bag);
    region->setEntry(QuillMetadata::Tag_Regions,entry);


    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");

    region->write(file.fileName());


    QuillMetadata *region1 = new QuillMetadata(file.fileName());
    QVariant data1 = region1->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data1.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag bag1 = data1.value<QuillMetadataRegionBag>();
    QCOMPARE(bag1.count(), 2);
    QCOMPARE(bag1[0].name(), QString("This is foo name"));
    QCOMPARE(bag1[0].regionType(), QString("Pet"));
    {
	QRect area = bag1[0].area();
	QCOMPARE(area.width(),	    1);
	QCOMPARE(area.height(),	    2);
	QCOMPARE(area.center().x(), 3);
	QCOMPARE(area.center().y(), 4);
    }

    delete region1;

}

void ut_metadata::testRegion()
{
    QuillMetadataRegion region;
    region.setName("this is testing");
    QString name = region.name();
    QCOMPARE(name, QString("this is testing"));

    QString type("face");
    region.setRegionType(type);
    QString type1 = region.regionType();
    QCOMPARE(type, type1);

    QRect rect(0,0,2,3);
    region.setArea(rect);
    QRect rect1 = region.area();
    QCOMPARE(rect,rect1);
}

void ut_metadata::testRegionBag()
{
    QuillMetadataRegionBag regionBag;

    QSize dimension;
    int width = 5;
    int height = 6;
    dimension = QSize(width, height);
    regionBag.setFullImageSize(dimension);
    QSize dimension1 = regionBag.fullImageSize();
    QCOMPARE(dimension.width(),dimension1.width());
    QCOMPARE(dimension.height(),dimension1.height());
}

void ut_metadata::testRegionAssignment()
{
    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag regionBag = data.value<QuillMetadataRegionBag>();
    QuillMetadataRegion region = regionBag[0];

    QuillMetadataRegion region1;

    region1 = region;

    QCOMPARE(region1.regionType(),  region.regionType());
    QCOMPARE(region1.area(),	    region.area());
    QCOMPARE(region1.name(),	    region.name());
}


void ut_metadata::testRegionBagAssignment()
{
    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag regionBag = data.value<QuillMetadataRegionBag>();

    QuillMetadataRegionBag regionBag1;

    regionBag1 = regionBag;

    QCOMPARE(regionBag1.count(), regionBag.count());
    QCOMPARE(regionBag1.fullImageSize(), regionBag.fullImageSize());

    for (int i = 0; i < regionBag.count(); i++)
    {
	QCOMPARE(regionBag1[i].regionType(),regionBag[i].regionType());
	QCOMPARE(regionBag1[i].area(),	    regionBag[i].area());
	QCOMPARE(regionBag1[i].name(),	    regionBag[i].name());
    }
}

void ut_metadata::testRegionBagAppend()
{
    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag regs = data.value<QuillMetadataRegionBag>();

    regs.append(regs[0]);
    regs[2].setName("appended region");


    QVariant entry;
    entry.setValue(regs);
    region->setEntry(QuillMetadata::Tag_Regions,entry);

    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    region->write(file.fileName());
    QuillMetadata *region1 = new QuillMetadata(file.fileName());
    QVariant data1 = region1->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data1.canConvert<QuillMetadataRegionBag>());

    QuillMetadataRegionBag regs1 = data1.value<QuillMetadataRegionBag>();


    QCOMPARE(regs1.count(), 3);
    QCOMPARE(regs.fullImageSize().width(),  4288);
    QCOMPARE(regs1.fullImageSize().width(),  4288);
    //QCOMPARE(regs1.fullImageSize().height(), 2848);
    // Name:
    QCOMPARE(regs1[0].name(), QString("Albert Einstein"));
    QCOMPARE(regs1[1].name(), QString("Dilbert"));
    QCOMPARE(regs1[2].name(), QString("appended region"));
    // Type:
    QCOMPARE(regs1[0].regionType(), QString("Face"));
    QCOMPARE(regs1[1].regionType(), QString("Face"));
    QCOMPARE(regs1[2].regionType(), QString("Face"));
    // Area:
    for (int i=0; i<3; i+=2){
	QRect area = regs[i].area();
	MYQCOMPARE(area.width(),	0.15*4288);
	MYQCOMPARE(area.height(),	0.17*2848);
	MYQCOMPARE(area.center().x(),	0.3*4288);
	MYQCOMPARE(area.center().y(),	0.4*2848);
    }
    {
	QRectF area = regs[1].area();
	MYQCOMPARE(area.width(),	0.17*4288);
	MYQCOMPARE(area.height(),	0.15*2848);
	MYQCOMPARE(area.center().x(),	0.4*4288);
	MYQCOMPARE(area.center().y(),	0.3*2848);
    }

}

void ut_metadata::testRegionBagRemoveRegion()
{
    QVariant data = region->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.canConvert<QuillMetadataRegionBag>());
    QuillMetadataRegionBag regs = data.value<QuillMetadataRegionBag>();

    while (regs.count()>0) // Remove, until no regions left.
    {
	regs.removeFirst();

	QVariant entry;
	entry.setValue(regs);
	region->setEntry(QuillMetadata::Tag_Regions,entry);

	QTemporaryFile file;
	file.open();
	sourceImage.save(file.fileName(), "jpg");
	region->write(file.fileName());

	QuillMetadata *region1 = new QuillMetadata(file.fileName());
	QVariant data1 = region1->entry(QuillMetadata::Tag_Regions);
	if (!data1.isNull())
	{
	    QVERIFY(data1.canConvert<QuillMetadataRegionBag>());
	    QuillMetadataRegionBag regs1 = data1.value<QuillMetadataRegionBag>();
	    QCOMPARE(regs1.count(), regs.count());

	    QCOMPARE(regs1.fullImageSize().width(),  4288);
	    QCOMPARE(regs1.fullImageSize().height(), 2848);
	    // Name:
	    QCOMPARE(regs1.last().name(), QString("Dilbert"));
	    // Type:
	    QCOMPARE(regs1.last().regionType(), QString("Face"));
	    // Area:
	    {
		QRect area = regs1.last().area();
		MYQCOMPARE(area.width(),	0.17*4288);
		MYQCOMPARE(area.height(),	0.15*2848);
		MYQCOMPARE(area.center().x(),	0.4*4288);
		MYQCOMPARE(area.center().y(),	0.3*2848);
	    }
	}
    }
}

void ut_metadata::testCreateRegionBag()
{
    QuillMetadataRegionBag regionBag;

    QuillMetadataRegion region;
    region.setName("this is testing");

    QString type("face");
    region.setRegionType(type);

    QRect rect(10,20,30,40);
    region.setArea(rect);

    int width = 50;
    int height = 60;
    QSize dimension = QSize(width, height);
    regionBag.setFullImageSize(dimension);

    regionBag.reserve(1);
    regionBag.append(region);

    QVariant data = metadata->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data.isNull());

    QVariant entry;
    entry.setValue(regionBag);
    metadata->setEntry(QuillMetadata::Tag_Regions,entry);
    QVariant data1 = metadata->entry(QuillMetadata::Tag_Regions);

    QTemporaryFile file;
    file.open();
    sourceImage.save(file.fileName(), "jpg");
    metadata->write(file.fileName());

    QuillMetadata *region1 = new QuillMetadata(file.fileName());
    QVariant data2 = region1->entry(QuillMetadata::Tag_Regions);
    QVERIFY(data2.canConvert<QuillMetadataRegionBag>());

    QuillMetadataRegionBag regs1 = data1.value<QuillMetadataRegionBag>();

    QCOMPARE(regs1[0].name(), QString("this is testing"));
    QCOMPARE(regs1[0].regionType(), QString("face"));
    {
	QRect area = regs1[0].area();
	MYQCOMPARE(area.x(),	    10);
	MYQCOMPARE(area.y(),	    20);
	MYQCOMPARE(area.width(),    30);
	MYQCOMPARE(area.height(),   40);
    }
}

int main ( int argc, char *argv[] ){
    QCoreApplication app( argc, argv );
    ut_metadata test;
    return QTest::qExec( &test, argc, argv );
}
