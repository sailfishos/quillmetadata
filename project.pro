##########
# main libquillmetadata project file
##########

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = src \
          tests

contains( doc, no ) {
    message( "Not building the documentation ..." )
}
else {
    include(doc/doc.pri)
    }

