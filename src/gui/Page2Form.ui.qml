import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    width: 480
    height: 620
    transformOrigin: Item.Center

/*
    RangeSlider {
        id: rangeSlider1
        x: 40
        y: 258
        width: 420
        height: 20
        stepSize: 0.1
        to: 4.02
        from: 4.02
        live: false
        rotation: 270
        second.value: 4.18
        first.value: 3.47
    }

    RangeSlider {
        id: rangeSlider2
        x: 80
        y: 258
        width: 420
        height: 20
        stepSize: 0.1
        to: 4.75
        from: 4.75
        live: false
        rotation: 270
        second.value: 5.01
        first.value: 4.19
    }

    RangeSlider {
        id: rangeSlider3
        x: 120
        y: 258
        width: 420
        height: 20
        stepSize: 0.1
        to: 6.4
        from: 1.86
        live: false
        rotation: 270
        second.value: 4.18
        first.value: 3.47
    }

    RangeSlider {
        id: rangeSlider4
        x: 160
        y: 258
        width: 420
        height: 20
        stepSize: 0.1
        to: 6.4
        from: 1.86
        live: false
        rotation: 270
        second.value: 4.18
        first.value: 3.47
    }
*/

    ProgressBar {
        id: progressBar0
        x: 70
        y: 227
        width: 410
        height: 20
        to: 6.40
        from: 1.86
        transformOrigin: Item.Center
        rotation: 270
        value: 4.02
    }

    ProgressBar {
        id: progressBar1
        x: 110
        y: 227
        width: 410
        height: 20
        to: 7.60
        from: 2.33
        value: 4.75
        rotation: 270
        transformOrigin: Item.Center
    }

    ProgressBar {
        id: progressBar2
        x: 150
        y: 227
        width: 410
        height: 20
        to: 11.50
        from: 5.64
        value: 8.42
        rotation: 270
        transformOrigin: Item.Center
    }

    ProgressBar {
        id: progressBar3
        x: 190
        y: 227
        width: 410
        height: 20
        from: 10.17
        to: 24.04
        value: 14.64
        rotation: 270
        transformOrigin: Item.Center
    }

    Label {
        id: label
        x: 263
        y: 464
        text: qsTr("FTP")
    }

    Label {
        id: label1
        x: 300
        y: 464
        text: qsTr("5min")
    }

    Label {
        id: label2
        x: 340
        y: 464
        text: qsTr("1min")
    }

    Label {
        id: label3
        x: 380
        y: 464
        width: 31
        height: 17
        text: qsTr("5sec")
    }

    Pane {
        id: pane
        x: 33
        y: 206
        width: 172
        height: 275
        padding: 5
        rightPadding: 5
        leftPadding: 5
        bottomPadding: 5
        topPadding: 5
        ColumnLayout {
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent
            Text {
                color: "grey"
                text: qsTr("FTP: Good\n  4.02 W/kg\n  Rank: 23[3.47, 4.18]")
            }
            Text {
                color: "grey"
                text: qsTr("5min: Good\n  4.75 W/kg\n  Rank: 31[4.19, 5.01]")
            }
            Text {
                color: "grey"
                text: qsTr("1min: Good\n  8.42 W/kg\n  Rank: 22[7.71, 8.63]")
            }
            Text {
                color: "grey"
                text: qsTr("5sec: Moderate\n  14.64 W/kg\n  Rank: 44[13.44, 15.61]")
            }
        }
    }

    GroupBox {
        id: groupBox
        x: 33
        y: 32
        width: 172
        height: 143
        padding: 5
        enabled: true
        title: qsTr("Power Scope View:")

        Column {
            spacing: 5

            RadioButton {
                id: radioButton1
                text: qsTr("Category")
            }

            RadioButton {
                id: radioButton2
                text: qsTr("Global")
            }
        }
    }
}
