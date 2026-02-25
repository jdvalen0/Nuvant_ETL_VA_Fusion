#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T15:29:08
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG += c++11

TARGET = GigECameraIPConfig
TEMPLATE = app


unix:macx:{
ICON=res/GigECameraIPConfig.icns
FRAMEWORKPATH = /Library/Frameworks/SentechSDK.framework
INCLUDEPATH += $${FRAMEWORKPATH}/Headers \
    $${FRAMEWORKPATH}/Headers/GenICam \
    $${FRAMEWORKPATH}/Headers/StApi
LIBS += -L$${FRAMEWORKPATH}/Libraries/GenICam -lGCBase -lGenApi \
      -L$${FRAMEWORKPATH}/Libraries -lStApi_TL -lStApi_GUI_qt
}

unix:!macx:{
INCLUDEPATH += $(STAPI_ROOT_PATH)/include/GenICam \
    $(STAPI_ROOT_PATH)/include/StApi
LIBS += -L$(STAPI_ROOT_PATH)/lib/GenICam \
    -lGCBase \
    -lGenApi \
    -llog4cpp \
    -L$(STAPI_ROOT_PATH)/lib \
    -lStApi_TL -lStApi_GUI_qt
}

QMAKE_CXXFLAGS += -O2 -Wno-unknown-pragmas -Wno-switch

SOURCES += main.cpp\
        gigecameraipconfigdlg.cpp

HEADERS  += gigecameraipconfigdlg.h

FORMS    += gigecameraipconfigdlg.ui

RESOURCES += \
    resource.qrc
