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

/* code */

#include <QCommandLineParser>
#include <QCoreApplication>

#include "CyclingPowerProfiler.h"
#include "CyclingPowerProfilerTask.h"

// #include "main.moc"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QCoreApplication::setApplicationName("PowerProfiler");
  QCoreApplication::setApplicationVersion("1.0.0");

  // do command-line parsing
  QCommandLineParser parser;
  parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
  parser.setApplicationDescription("Power profiling tool for road cycling");
  parser.addHelpOption();
  parser.addVersionOption();

  parser.addOptions(
      {{{"g", "gender"}, "Athlete's gender.", "m(ale) or f(emale)", "male"},
       {{"w", "weight"}, "Athlete's weight in kilograms.", "kg", "64.0"},
       {{"ftp", "ftp"},
        "60 min functional threshold power (W).",
        "ppo60",
        "257"},
       {{"vo2", "vo2"}, "5 min best power (W).", "ppo5", "304"},
       {{"ana", "ana"}, "1 min best power (W).", "ppo1", "539"},
       {{"nmu", "nmu"}, "5 sec best power (W).", "ppo5s", "937"}});

  parser.process(a);

  // Task parented to the application so that it will be deleted by the
  // application.
  QSharedPointer<CyclingPowerProfilerTask> task(
      new CyclingPowerProfilerTask(&a));

  task->setUI(UiType::kTerminal);

  // init task properties with user input values
  task->setAthleteGender(parser.value("gender").toLower());
  task->setAthleteWeight(parser.value("weight"));
  task->setAthleteEffort(PowerType::kFt, parser.value("ftp"));
  task->setAthleteEffort(PowerType::k5Min, parser.value("vo2"));
  task->setAthleteEffort(PowerType::k1Min, parser.value("ana"));
  task->setAthleteEffort(PowerType::k5Sec, parser.value("nmu"));

  // This will cause the application to exit when the task signals finished.
  QObject::connect(task.data(), SIGNAL(calcCompleted()), &a, SLOT(quit()));

  // This will run the task from the application event loop.
  QTimer::singleShot(0, task.data(), SLOT(calc()));

  return a.exec();
}
