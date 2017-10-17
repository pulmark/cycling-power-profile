# Copyright (c) 2017 Markku Pulkkinen. All rights reserved.
# Contact: markku.j.pulkkinen@gmail.com
#
# This file is part of CyclingPowerProfiler software distribution.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.

QT += core
QT -= gui

CONFIG += c++11 c++14 c++17

TARGET = PowerProfiler
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../src
INCLUDEPATH += ../include

SOURCES += ./main.cpp \
    ../src/CyclingPowerProfiler.cc

HEADERS += \
    ../src/iProfiler.h \
    ../src/Athlete.h \
    ../src/CyclingPowerProfileChart.h \
    ../src/CyclingPowerProfiler.h \
    ../src/CyclingPowerProfilerQuery.h \
    ../src/CyclingPowerProfilerTask.h \
    ../include/json.hpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    ../README.md
