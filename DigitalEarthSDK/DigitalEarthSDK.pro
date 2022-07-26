QT += core gui opengl widgets

TEMPLATE = lib
DEFINES += DIGITALEARTHSDK_LIBRARY

CONFIG += c++11

# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../../DigitalEarth_x64
} else {
    DESTDIR = $$PWD/../../DigitalEarth_x64
}

INCLUDEPATH += $$PWD/../../Dependence/include

LIBS += -L$$PWD/../../Dependence/lib/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DigitalEarthSDK.cpp \
    EarthEventHandler.cpp \
    GraphicsWindowQt.cpp \
    Helpers/ConfigHelper.cpp \
    Math/Coordinate.cpp \
    QGraphicsViewAdapter.cpp \
    QWidgetImage.cpp \
    Tools/JsonTool.cpp

HEADERS += \
    DigitalEarthSDK_global.h \
    DigitalEarthSDK.h \
    EarthEventHandler.h \
    Enums/EarthEnums.h \
    GraphicsWindowQt.h \
    Helpers/ConfigHelper.h \
    Math/Coordinate.h \
    Objects/EarthObjects.h \
    PluginRegister.h \
    QGraphicsViewAdapter.h \
    QWidgetImage.h \
    Tools/JsonTool.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# 添加调试信息
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
