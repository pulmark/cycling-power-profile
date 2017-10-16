// The MIT License (MIT)

// Copyright (c) 2017 Markku Pulkkinen <markku.j.pulkkinen@gmail.com>

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

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

  // Task parented to the application so that it
  // will be deleted by the application.
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

  // This will cause the application to exit when
  // the task signals finished.
  QObject::connect(task.data(), SIGNAL(calcCompleted()), &a, SLOT(quit()));

  // This will run the task from the application event loop.
  QTimer::singleShot(0, task.data(), SLOT(calc()));

  return a.exec();
}
