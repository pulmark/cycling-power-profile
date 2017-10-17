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

#ifndef CYCLINGPOWERPROFILERTASK_H
#define CYCLINGPOWERPROFILERTASK_H

#include <sstream>

#include <QDebug>
#include <QSharedPointer>
#include <QtCore>

#include "CyclingPowerProfiler.h"

enum class UiType { kUndefined = 0, kTerminal, kGraphical, kTouchScreen };

class CyclingPowerProfilerTask : public QObject {
  Q_OBJECT

public:
  CyclingPowerProfilerTask(QObject *parent = 0)
      : QObject{parent}, m_gender{"male"}, m_weight{"64.0"}, m_ppo60{"257.0"},
        m_ppo5{"304"}, m_ppo1{"539"}, m_ppo5s{"937"}, m_queryResult{},
        m_ui{UiType::kTerminal} {}

  virtual ~CyclingPowerProfilerTask() {}

  // enums for power types and user interface
  Q_ENUM(PowerType)
  Q_ENUM(UiType)

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

  // set user interface type
  Q_INVOKABLE void setUI(UiType type) { m_ui = type; }

  // get query result
  Q_INVOKABLE void getQueryResult(QString &result) const {
    result = m_queryResult;
  }

public slots:

  void clear() {
    m_gender.clear();
    m_weight.clear();
    m_ppo60.clear();
    m_ppo5.clear();
    m_ppo1.clear();
    m_ppo5s.clear();
    m_queryResult.clear();
    emit clearCompleted();
  }

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
    m_queryResult = ss.str().c_str();
    if (m_ui == UiType::kTerminal) {
      QTextStream cout(stdout);
      cout << m_queryResult;
      cout.flush();
    }
    emit calcCompleted();
  }

signals:
  void calcCompleted();
  void clearCompleted();

private:
  // athlete properties
  QString m_gender;
  QString m_weight;
  QString m_ppo60;
  QString m_ppo5;
  QString m_ppo1;
  QString m_ppo5s;

  // power profiler query result (JSON format)
  QString m_queryResult;

  // user interface type
  UiType m_ui;
};

#endif // CYCLINGPOWERPROFILERTASK_H
