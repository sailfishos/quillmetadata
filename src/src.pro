##########
# the project file in src, it is not created automatically/
##########

TEMPLATE = lib
TARGET = quillmetadata-qt5

MOC_DIR = .moc

LIBS += -lexif -lexempi -ljpeg
# Generate pkg-config support by default
# Note that we HAVE TO also create prl config as QMake implementation
# mixes both of them together.
CONFIG += create_pc create_prl no_install_prl
QMAKE_PKGCONFIG_REQUIRES = Qt5Gui
QMAKE_PKGCONFIG_INCDIR = $$[QT_INSTALL_HEADERS]/$$TARGET
QMAKE_PKGCONFIG_LIBDIR = $$[QT_INSTALL_LIBS]
QMAKE_PKGCONFIG_VERSION = $$VERSION

QMAKE_CXXFLAGS += -Werror
QMAKE_LFLAGS += -Wl,--as-needed

# this is for adding coverage information while doing qmake as "qmake COV_OPTION=on"
# message is shown when 'make' is executed
for(OPTION,$$list($$lower($$COV_OPTION))){
    isEqual(OPTION, on){
        message("TEST COVERAGE IS ENABLED")
        QMAKE_CXXFLAGS += -ftest-coverage -fprofile-arcs -fno-elide-constructors
        LIBS += -lgcov
    }
}

# --- input

HEADERS += quillmetadata.h \
           metadatarepresentation.h \
           xmp.h \
           exif.h \
           exifwriteback.h \
	   quillmetadataregion.h \
	   quillmetadataregionlist.h

SOURCES += quillmetadata.cpp \
           xmp.cpp \
           exif.cpp \
           exifwriteback.cpp \
	   quillmetadataregion.cpp \
	   quillmetadataregionlist.cpp

INSTALL_HEADERS = QuillMetadata \
                  quillmetadata.h \
                  QuillMetadataRegion \
		  quillmetadataregion.h \
                  QuillMetadataRegionList \
		  quillmetadataregionlist.h

# --- install
headers.files = $$INSTALL_HEADERS
headers.path = $$[QT_INSTALL_HEADERS]/$$TARGET
target.path = $$[QT_INSTALL_LIBS]
pkgconfig.files = quillmetadata-qt5.pc
pkgconfig.path = $$[QT_INSTALL_LIBS]/pkgconfig
INSTALLS += target headers pkgconfig


QMAKE_CLEAN += *.gcov *.gcno *.log *.moc_* *.gcda
