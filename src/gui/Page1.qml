/*
** Copyright (c) 2017 Markku Pulkkinen. All rights reserved.
** Contact: markku.j.pulkkinen@gmail.com
**
** This file is part of CyclingPowerProfiler software distribution.
**
** This software is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This software is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this software.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.7

Page1Form {
    calc.onClicked: {
        console.log("Calculate Button Pressed");
        tabBar.incrementCurrentIndex();
    }
    clear.onClicked: {
        console.log("ClearButton Pressed");
        weight.clear();
        ftp.clear();
        min5.clear();
        min1.clear();
        sec5.clear();
    }
}
