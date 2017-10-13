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

/*
#include <QDebug>
#include <QSharedPointer>
#include <QtCore>

class Task : public QObject
{
    Q_OBJECT

public:
    Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run()
    {
        qDebug() << "Hello World from the Event Loop" << endl;
        emit finished();
    }

signals:
    void finished();
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Task parented to the application so that it
    // will be deleted by the application.
    QSharedPointer<Task> task(new Task(&a));

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task.data(), SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task.data(), SLOT(run()));

    return a.exec();
}
*/

#include <QCommandLineParser>
#include <QCoreApplication>

#include "CyclingPowerProfiler.h"
#include "json.hpp"

int main(int argc, char *argv[]) {
  // init app
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
      {{{"g", "gender"}, "Athlete's gender.", "gender", "male"},
       {{"w", "weight"}, "Athlete's weight.", "weight", "65.0"},
       {{"ftp", "ftp"}, "Functional threshold power-60min (W).", "ftp", "257"},
       {{"vo2", "vo2"}, "Peak aerobic power-5min (W).", "ppo5m", "0"},
       {{"ana", "ana"}, "Peak anaerobic power-1min (W).", "ppo1m", "0"},
       {{"nmu", "nmu"}, "Peak neuromuscular power-5sec (W).", "ppo5s", "0"}});

  parser.process(a);

  QString gender = parser.value("gender").toLower();
  QString kg = parser.value("weight");
  QString ppo60 = parser.value("ftp");
  QString ppo5 = parser.value("vo2");
  QString ppo1 = parser.value("ana");
  QString ppo5s = parser.value("nmu");

  // init athlete

  Athlete me(gender.at(0) == "m" ? Gender::kMale : Gender::kFemale);
  Weight w{Weight::dummy{}, kg.toDouble()};
  // Weight w = 65.6_kg;
  me.set_weight(w);

  // init profiler
  std::shared_ptr<CyclingPowerProfiler> profiler =
      std::make_shared<CyclingPowerProfiler>();
  profiler->Init();

  // build query for power profiling
  profiler->ResetQuery();
  profiler->InitQuery(PowerType::kFt, ppo60.toDouble());
  profiler->InitQuery(PowerType::k5Min, ppo5.toDouble());
  profiler->InitQuery(PowerType::k1Min, ppo1.toDouble());
  profiler->InitQuery(PowerType::k5Sec, ppo5s.toDouble());

  // run profiling on athlete 'me'
  me.set_profiler(profiler);
  me.DoProfiling();

  // print query and its results into console output
  profiler->SaveQuery(std::cout);

  return a.exec();
}
