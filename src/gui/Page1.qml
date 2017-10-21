/*
** CyclingPowerProfiler distribution, Copyright (c) 2017 Markku Pulkkinen.
** Contact: markku.j.pulkkinen@gmail.com

** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.

** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.7
import com.me.qmlcomponents 1.0

Page1Form {
    calc.onClicked: {
        console.log("Calculate Button Pressed");

        // sanity checks for power and weigth values
        var valFtp = ftp.text.length == 0 ? 0 : parseInt(ftp.text.valueOf(), 10);
        var valVo2 = min5.text.length == 0 ? 0 : parseInt(min5.text.valueOf(), 10);
        var valAna = min1.text.length == 0 ? 0 : parseInt(min1.text.valueOf(), 10);
        var valNmu = sec5.text.length == 0 ? 0 : parseInt(sec5.text.valueOf(), 10);
        var valKg = weight.text.length == 0 ? 0 : parseInt(weight.text.valueOf(), 10);
        if (valFtp < 1 || valFtp > 2000) return;
        if (valVo2 < 1 || valVo2 > 2000) return;
        if (valAna < 1 || valAna > 2000) return;
        if (valNmu < 1 || valNmu > 2000) return;
        if (valKg < 20 || valKg > 200) return;

        // set rider properties
        task.setAthleteWeight(weight.text);
        task.setAthleteGender(gender.checked ? "male" : "female");
        task.setAthleteEffort(Task.Ftp, ftp.text);
        task.setAthleteEffort(Task.Vo2Max, min5.text);
        task.setAthleteEffort(Task.Anaerobic, min1.text);
        task.setAthleteEffort(Task.NeuroMuscular, sec5.text);

        // call our task to do calculation
        task.calc();

        // switch to Power Profile view
        tabBar.incrementCurrentIndex();
    }
    clear.onClicked: {
        console.log("ClearButton Pressed");

        // call our task to clear user input values
        task.clear();

        // clear user input fields
        weight.clear();
        ftp.clear();
        min5.clear();
        min1.clear();
        sec5.clear();
    }
}
