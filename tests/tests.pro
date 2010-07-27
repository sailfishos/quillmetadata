
TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += ordered

SUBDIRS += ut_metadata \


# --- install
tatam.files = tests.xml
tatam.path  = $$(DESTDIR)/usr/share/libquillmetadata-tests/

tatamimages.files += images/exif.jpg
tatamimages.files += images/xmp.jpg
tatamimages.files += images/iptc.jpg
tatamimages.files += images/gps.jpg

tatamimages.path  = $$(DESTDIR)/usr/share/libquillmetadata-tests/images/

INSTALLS += tatam tatamimages
