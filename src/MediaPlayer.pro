#-------------------------------------------------
#
# Project created by QtCreator 2020-12-01T23:40:21
#
#-------------------------------------------------

QT       += widgets core dbus

CONFIG += c++11 link_pkgconfig plugin
PKGCONFIG = dde-dock dframeworkdbus dtkwidget

TARGET = mediaplayerplugin
TEMPLATE = lib

DEFINES += DDE_MEDIAPLAYER_LIBRARY QT_DEPRECATED_WARNINGS

SOURCES += \
    mpris/dbusinterface.cpp \
    mpris/dbusmpris.cpp \
    mpris/dmprismonitor.cpp \
    currentmedias.cpp \
    popupcontainer.cpp \
    mediaplayerplugin.cpp \
    mediaapplet.cpp \
    mediaplayerwidget.cpp

HEADERS += \
    mpris/dbusinterface.h \
    mpris/dbusmpris.h \
    mpris/dmprismonitor.h \
    currentmedias.h \
    defs.h \
    popupcontainer.h \
    mediaplayerplugin.h \
    mediaapplet.h \
    mediaplayerwidget.h

TRANSLATIONS += \

unix {
    target.path = /usr/lib/dde-dock/plugins/system-trays
    INSTALLS += target
}

RESOURCES += \
    res.qrc

DISTFILES += \
    mediaplayer.json
