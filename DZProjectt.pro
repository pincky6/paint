QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    model/abstractfigure.cpp \
    model/line.cpp \
    model/path.cpp \
    model/rectangle.cpp \
    model/ellipse.cpp \
    model/triangle.cpp \
    model/figurefactory.cpp \
    paintwidget.cpp \
    view/drawablefigure.cpp \
    view/painttoolbar.cpp \
    view/paintview.cpp \
    viewmodel/paintviewlogic.cpp

HEADERS += \
    model/abstractfigure.h \
    model/figuresenum.h \
    model/line.h \
    model/paintstate.h \
    model/path.h \
    model/rectangle.h \
    model/ellipse.h \
    model/triangle.h \
    model/figurefactory.h \
    paintwidget.h \
    view/drawablefigure.h \
    view/idrawable.h \
    view/painttoolbar.h \
    view/paintview.h \
    viewmodel/paintviewlogic.h

FORMS += \
    paintwidget.ui \
    view/painttoolbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
