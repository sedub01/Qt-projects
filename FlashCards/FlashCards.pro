QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/answerform.cpp \
    sources/choosecountform.cpp \
    main.cpp \
    sources/mainwindow.cpp \
    sources/selftestform.cpp

HEADERS += \
    headers/answerform.h \
    headers/choosecountform.h \
    headers/mainwindow.h \
    headers/selftestform.h

FORMS += \
    forms/answerform.ui \
    forms/choosecountform.ui \
    forms/mainwindow.ui \
    forms/selftestform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
