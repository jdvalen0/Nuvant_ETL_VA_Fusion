#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T10:20:42
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG += c++11
TARGET = StViewer
TEMPLATE = app

unix:macx:{
ICON=res/StViewer.icns
FRAMEWORKPATH = /Library/Frameworks/SentechSDK.framework
INCLUDEPATH += $${FRAMEWORKPATH}/Headers \
    $${FRAMEWORKPATH}/Headers/GenICam \
    $${FRAMEWORKPATH}/Headers/StApi
LIBS += -L$${FRAMEWORKPATH}/Libraries/GenICam -lGCBase -lGenApi \
      -L$${FRAMEWORKPATH}/Libraries -lStApi_TL -lStApi_IP -lStApi_GUI_qt
}

unix:!macx:{
INCLUDEPATH += $(STAPI_ROOT_PATH)/include/GenICam \
    $(STAPI_ROOT_PATH)/include/StApi
LIBS += -L$(STAPI_ROOT_PATH)/lib/GenICam \
    -lGCBase \
    -lGenApi \
    -llog4cpp \
    -L$(STAPI_ROOT_PATH)/lib \
    -lStApi_TL -lStApi_IP -lStApi_GUI_qt
}

QMAKE_CXXFLAGS += -O2 -Wno-unknown-pragmas -Wno-switch -Wno-pointer-arith

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QT_NO_VERSION_TAGGING

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    dialogabout.cpp \
    mdichild.cpp \
    mdichild_device.cpp \
    mdichild_stillimage.cpp \
    dialogvideoconfiguration.cpp \
    cavifilerecorder.cpp \
    widgetgraphview.cpp \
    widgetnodemap.cpp \
    ccamerasideffc.cpp \
    dialogconfigurationfilesetting.cpp \
    cconfigurationfile.cpp \
    widgetdefectivepixeldetection.cpp \
    cdefectivepixelmanager.cpp \
    tablemodeldefectivepixel.cpp

HEADERS  += mainwindow.h \
    common.h \
    dialogabout.h \
    mdichild.h \
    mdichild_device.h \
    mdichild_stillimage.h \
    dialogvideoconfiguration.h \
    cavifilerecorder.h \
    widgetgraphview.h \
    widgetnodemap.h \
    ccamerasideffc.h \
    dialogconfigurationfilesetting.h \
    cconfigurationfile.h \
    widgetdefectivepixeldetection.h \
    istimagecallback.h \
    istreamingctrl.h \
    cdefectivepixelmanager.h \
    tablemodeldefectivepixel.h

FORMS    += mainwindow.ui \
    dialogabout.ui \
    mdichild_device.ui \
    mdichild_stillimage.ui \
    dialogvideoconfiguration.ui \
    widgetgraphview.ui \
    widgetnodemap.ui \
    dialogconfigurationfilesetting.ui \
    widgetdefectivepixeldetection.ui

RESOURCES += \
    resource.qrc
