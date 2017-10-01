################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
#
# AKL_RS232
# Copyright (C) 2015-2017   Ilnur Gimazov
#
################################################################

QT += widgets
win32:LIBS += libws2_32

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

include( $${PWD}/../examples.pri )

TARGET       = AKL_RS232

HEADERS = \
    mainwindow.h \
    scrollzoomer.h \
    scrollbar.h \
    incrementalplot.h \
    appa.h \
    dialog_k.h \
    class_port_appa.h \
    class_port_lock_in.h \
    class_write_to_file.h \
    class_open_file.h \
    class_port_keithley.h \
    class_temp.h

SOURCES = \
    main.cpp \
    mainwindow.cpp \
    scrollzoomer.cpp \
    scrollbar.cpp \
    incrementalplot.cpp \
    appa.cpp \
    dialog_k.cpp \
    class_port_appa.cpp \
    class_port_lock_in.cpp \
    class_write_to_file.cpp \
    class_open_file.cpp \
    class_port_keithley.cpp \
    class_temp.cpp

RC_FILE = AKL.rc

FORMS +=

