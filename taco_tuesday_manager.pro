QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network gui

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/apireply.cpp \
    src/configurationdialog.cpp \
    src/cooldownbar.cpp \
    src/domainobject.cpp \
    src/employee.cpp \
    src/employeerow.cpp \
    src/employeetable.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/taco.cpp \
    src/tacotuesdayapiclient.cpp \
    src/tacotuesdayapihandler.cpp \
    src/tacotuesdayconfig.cpp \
    src/jsonparser.cpp \
    src/order.cpp \
    src/fullorder.cpp \
    src/individualorder.cpp \
    src/ttlogger.cpp \
    src/ttordertree.cpp

HEADERS += \
    src/apireply.h \
    src/cooldownbar.h \
    src/domainobject.h \
    src/employee.h \
    src/employeerow.h \
    src/employeetable.h \
    src/jsonparser.h \
    src/order.h \
    src/fullorder.h \
    src/individualorder.h \
    src/taco.h \
    src/tacotuesdayapiclient.h \
    src/tacotuesdayapihandler.h \
    src/mainwindow.h \
    src/configurationdialog.h \
    src/tacotuesdayconfig.h \
    src/ttlogger.h \
    src/ttordertree.h

FORMS += \
    src/ui/configurationdialog.ui \
    src/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
