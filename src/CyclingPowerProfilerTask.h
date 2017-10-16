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

#ifndef CYCLINGPOWERPROFILERTASK_H
#define CYCLINGPOWERPROFILERTASK_H

#include <sstream>

#include <QDebug>
#include <QSharedPointer>
#include <QtCore>

#include "CyclingPowerProfiler.h"

class CyclingPowerProfilerTask : public QObject {
  Q_OBJECT

public:
  CyclingPowerProfilerTask(QObject *parent = 0)
      : QObject(parent), m_gender("male"), m_weight("65.0"), m_ppo60("300.0"),
        m_ppo5("400"), m_ppo1("600"), m_ppo5s("1100"), m_hasCLI(false) {}

  virtual ~CyclingPowerProfilerTask() {}

  // athlete properties: gender, weight, best power for 60m, 5m, 1m and 5s
  Q_INVOKABLE void setAthleteGender(const QString &gender) {
    m_gender = gender;
  }
  Q_INVOKABLE void setAthleteWeight(const QString &weight) {
    m_weight = weight;
  }
  Q_INVOKABLE void setAthleteEffort(PowerType type, const QString &watts) {
    switch (type) {
    default:
      break;
    case PowerType::kFt:
      m_ppo60 = watts;
      break;
    case PowerType::k5Min:
      m_ppo5 = watts;
      break;
    case PowerType::k1Min:
      m_ppo1 = watts;
      break;
    case PowerType::k5Sec:
      m_ppo5s = watts;
      break;
    }
  }

  // get query result
  Q_INVOKABLE void getQueryResult(QString &result) {
    result = m_queryResult.readAll();
  }

  // set user interface type
  Q_INVOKABLE void setUI(bool hasCLI = false) { m_hasCLI = hasCLI; }

public slots:
  void calc() {
    // init athlete
    Athlete me(m_gender.at(0) == "m" ? Gender::kMale : Gender::kFemale);
    Weight w{Weight::dummy{}, m_weight.toDouble()};
    me.set_weight(w);

    // init profiler
    std::shared_ptr<CyclingPowerProfiler> profiler =
        std::make_shared<CyclingPowerProfiler>();
    profiler->Init();

    // build query for power profiling
    profiler->ResetQuery();
    profiler->InitQuery(PowerType::kFt, m_ppo60.toDouble());
    profiler->InitQuery(PowerType::k5Min, m_ppo5.toDouble());
    profiler->InitQuery(PowerType::k1Min, m_ppo1.toDouble());
    profiler->InitQuery(PowerType::k5Sec, m_ppo5s.toDouble());

    // run profiling on athlete 'me'
    me.set_profiler(profiler);
    me.DoProfiling();

    // retrieve and store(show) results
    std::ostringstream ss;
    profiler->SaveQuery(ss);
    if (m_hasCLI)
      std::cout << ss.str();
    else
      m_queryResult << ss.str().c_str();

    emit finished();
  }

signals:
  void finished();

private:
  // athlete properties
  QString m_gender;
  QString m_weight;
  QString m_ppo60;
  QString m_ppo5;
  QString m_ppo1;
  QString m_ppo5s;

  // power profiler query result (JSON format)
  QTextStream m_queryResult;

  // true if client has command-line user interface
  bool m_hasCLI;
};

#endif // CYCLINGPOWERPROFILERTASK_H
