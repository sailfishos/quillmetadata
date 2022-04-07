TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += ordered

SUBDIRS += ut_metadata \
	    ut_regions

tests_xml.files = tests.xml
tests_xml.path  = $$(DESTDIR)/opt/tests/libquillmetadata-qt5/

images.files += images/exif.jpg
images.files += images/xmp.jpg
images.files += images/iptc.jpg
images.files += images/gps.jpg
images.files += images/mnaa.jpg

images.path  = $${tests_xml.path}/images/

INSTALLS = tests_xml images
