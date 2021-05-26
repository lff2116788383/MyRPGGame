QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlescene.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    role.cpp \
    testmap001.cpp

HEADERS += \
    battlescene.h \
    mainwindow.h \
    map.h \
    role.h \
    testmap001.h

FORMS += \
    battlescene.ui \
    mainwindow.ui \
    map.ui \
    testmap001.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




#DEFINES += QT_NO_WARNING_OUTPUT\
#                       QT_NO_DEBUG_OUTPUT

RESOURCES += \
    res.qrc
