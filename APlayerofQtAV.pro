QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

unix{
	DESTDIR = $$PWD/bin
	OBJECTS_DIR = $$PWD/tmp
	MOC_DIR = $$PWD/tmp
	RCC_DIR = $$PWD/tmp
	UI_DIR = $$PWD/tmp
}

SOURCES += \
	src/main.cpp \
	src/MainW.cpp \
    src/RPainterRendererPrivate.cpp \
    src/RPainterRenderer.cpp \
    src/RGraphicsItemRendererPrivate.cpp \
    src/RGraphicsItemRenderer.cpp

HEADERS += \
	src/MainW.h \
    src/RPainterRendererPrivate.h \
    src/RPainterRenderer.h \
    src/RGraphicsItemRendererPrivate.h \
    src/RGraphicsItemRenderer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lQtAV1 -lQtAVWidgets1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lQtAVd1 -lQtAVWidgetsd1

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

#LIBS += -L$$PWD/lib/ -lQtAV1 -lQtAVWidgets1
