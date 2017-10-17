
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
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1

Item {
    property alias ftp: textField1
    property alias min5: textField2
    property alias min1: textField3
    property alias sec5: textField4
    property alias weight: textField5

    property alias calc: button1
    property alias clear: button2

    width: 480
    height: 620
    transformOrigin: Item.Center

    Button {
        id: button1
        x: 131
        y: 377
        width: 87
        height: 40
        text: qsTr("Calc")
    }

    Button {
        id: button2
        x: 20
        y: 377
        width: 94
        height: 40
        text: qsTr("Clear")
    }

    Switch {
        id: switch1
        x: 123
        y: 28
        text: qsTr("Male")
        spacing: 8
        font.pointSize: 11
        checked: true
    }

    TextField {
        id: textField1
        x: 107
        y: 176
        width: 111
        height: 40
        text: "250"
        placeholderText: qsTr("")
    }

    TextField {
        id: textField2
        x: 107
        y: 222
        width: 111
        height: 40
        text: "0"
        placeholderText: qsTr("")
    }

    TextField {
        id: textField3
        x: 107
        y: 268
        width: 111
        height: 40
        text: "0"
        placeholderText: qsTr("")
    }

    TextField {
        id: textField4
        x: 107
        y: 314
        width: 111
        height: 40
        text: "0"
        placeholderText: qsTr("")
    }

    TextField {
        id: textField5
        x: 107
        y: 83
        width: 111
        height: 40
        text: "65"
        placeholderText: qsTr("")
    }

    Text {
        id: text1
        x: 50
        y: 31
        width: 72
        height: 40
        color: Material.foreground
        text: qsTr("Female")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
    }

    Text {
        id: text2
        x: 10
        y: 90
        color: Material.foreground
        text: qsTr("Weight [kg]:")
        font.bold: true
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 14
    }

    Text {
        id: text3
        x: 29
        y: 183
        width: 41
        height: 29
        color: Material.foreground
        text: qsTr("FTP:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text4
        x: 29
        y: 228
        width: 41
        height: 29
        color: Material.foreground
        text: qsTr("5min:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text5
        x: 29
        y: 274
        width: 41
        height: 29
        color: Material.foreground
        text: qsTr("1min:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text6
        x: 29
        y: 320
        width: 41
        height: 29
        color: Material.foreground
        text: qsTr("5sec:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text7
        x: 10
        y: 31
        width: 41
        height: 40
        color: Material.foreground
        text: qsTr("Gender:")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14
    }

    Text {
        id: text8
        x: 10
        y: 141
        width: 203
        height: 29
        color: Material.foreground
        text: qsTr("Best Peak Power [W]:")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 14
    }
}
