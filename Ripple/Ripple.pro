######################################################################
# Automatically generated by qmake (2.01a) Tue May 24 09:43:52 2011
######################################################################

TEMPLATE = app
TARGET = ripple 
DEPENDPATH += .
INCLUDEPATH += .

# Specify that we're looking for the IPC.  Realistically, this should be put
# in some configuration file
INCLUDEPATH += ../build ../IPC

LIBS += -L../build -lipc -lripplelibrary

# Required QT modules
QT += webkit network xml

# Input
HEADERS += application.h ripple.h ../RippleLibrary/*.h
SOURCES += application.cpp main.cpp ripple.cpp
RESOURCES += ripple.qrc