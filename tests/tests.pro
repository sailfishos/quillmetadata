equals(QT_MAJOR_VERSION, 4): PACKAGENAME = libquillmetadata
equals(QT_MAJOR_VERSION, 5): PACKAGENAME = libquillmetadata-qt5

TEMPLATE = subdirs

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += ordered

SUBDIRS += ut_metadata \
	    ut_regions

# --- generate tests.xml
tests_xml.target = tests.xml
tests_xml.depends = $$PWD/tests.xml.in
tests_xml.commands = sed -e "s:@PACKAGENAME@:$${PACKAGENAME}:g" $< > $@

QMAKE_EXTRA_TARGETS = tests_xml
QMAKE_CLEAN += $$tests_xml.target
PRE_TARGETDEPS += $$tests_xml.target

# --- install
tatam.depends = tests_xml
tatam.files = $$tests_xml.target
tatam.path  = $$(DESTDIR)/usr/share/$${PACKAGENAME}-tests/
tatam.CONFIG += no_check_exist

tatamimages.files += images/exif.jpg
tatamimages.files += images/xmp.jpg
tatamimages.files += images/iptc.jpg
tatamimages.files += images/gps.jpg
tatamimages.files += images/mnaa.jpg

tatamimages.path  = $${tatam.path}/images/

INSTALLS = tatam tatamimages
