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
