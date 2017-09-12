import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property alias ftp: textField1
    property alias min5: textField2
    property alias min1: textField3
    property alias sec5: textField4
    property alias weight: textField5

    property alias calc: button1
    property alias clear: button2

    transformOrigin: Item.Center

    TextField {
        id: textField1
        x: 87
        y: 176
        width: 131
        height: 40
        text: "250"
        placeholderText: qsTr("Text Field")
    }

    Button {
        id: button1
        x: 131
        y: 377
        width: 87
        height: 40
        text: qsTr("Build")
    }

    Switch {
        id: switch1
        x: 123
        y: 28
        text: qsTr("Male")
        checked: true
    }

    Text {
        id: text1
        x: 50
        y: 28
        width: 72
        height: 40
        text: qsTr("Female")
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit
        font.pixelSize: 12
    }

    TextField {
        id: textField2
        x: 87
        y: 222
        width: 131
        height: 40
        text: "0"
        placeholderText: qsTr("Text Field")
    }

    TextField {
        id: textField3
        x: 87
        y: 268
        width: 131
        height: 40
        text: "0"
        placeholderText: qsTr("Text Field")
    }

    TextField {
        id: textField4
        x: 87
        y: 314
        width: 131
        height: 40
        text: "0"
        placeholderText: qsTr("Text Field")
    }

    TextField {
        id: textField5
        x: 87
        y: 83
        width: 131
        height: 40
        text: "65"
        placeholderText: qsTr("Text Field")
    }

    Text {
        id: text2
        x: 20
        y: 96
        text: qsTr("Weight [kg]:")
        font.bold: true
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text3
        x: 40
        y: 187
        width: 41
        height: 29
        text: qsTr("FTP:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text4
        x: 40
        y: 233
        width: 41
        height: 29
        text: qsTr("5min:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text5
        x: 40
        y: 279
        width: 41
        height: 29
        text: qsTr("1min:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Text {
        id: text6
        x: 40
        y: 325
        width: 41
        height: 29
        text: qsTr("5sec:")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 12
    }

    Button {
        id: button2
        x: 20
        y: 377
        width: 94
        height: 40
        text: qsTr("Clear")
    }

    Text {
        id: text7
        x: 20
        y: 28
        width: 41
        height: 40
        text: qsTr("Gender:")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

    Text {
        id: text8
        x: 20
        y: 141
        width: 203
        height: 29
        text: qsTr("Best Peak Power [W]:")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }
}
