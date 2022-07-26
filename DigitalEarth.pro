QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../DigitalEarth_x64
} else {
    DESTDIR = $$PWD/../DigitalEarth_x64
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FramelessHelper.cpp \
    main.cpp \
    DigitalEarth.cpp

HEADERS += \
    DigitalEarth.h \
    FramelessHelper.h

FORMS += \
    DigitalEarth.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DigitalEarth_x64/ -lDigitalEarthSDK
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DigitalEarth_x64/ -lDigitalEarthSDKd

INCLUDEPATH += $$PWD/../DigitalEarth_x64 \
               $$PWD/../Dependence/include \
               $$PWD/DigitalEarthSDK
DEPENDPATH += $$PWD/../DigitalEarth_x64 \
              $$PWD/../Dependence/include \
              $$PWD/DigitalEarthSDK

LIBS += -L$$PWD/../Dependence/lib/ \
        -L$$PWD/../DigitalEarth_x64/ -lDigitalEarthSDK

RC_FILE += DigitalEarth.rc

# 添加调试信息
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
