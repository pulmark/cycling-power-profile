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

/* code */

#ifndef CYCLINGPOWERPROFILER_H
#define CYCLINGPOWERPROFILER_H

#include <iostream>

#include "CyclingPowerProfilerQuery.h"

class CyclingPowerProfiler : public IProfiler {
public:
  enum ProfileFormat { kInternal, kJson, kBson };

  explicit CyclingPowerProfiler() : male_{}, female_{}, query_{} {}
  ~CyclingPowerProfiler() {}

  // profiler initialization
  void Init();

  // clears query
  void ResetQuery();

  // initializes a new query
  bool InitQuery(PowerType type, double watts,
                 PowerUnit unit = PowerUnit::kWatt);

  // saves last query (request & result)
  bool SaveQuery(std::ostream &s, ProfileFormat format = kJson);

  // does profiling for given athlete
  bool Run(const Athlete &athlete);

protected:
private:
  // power profile charts for male cyclists
  std::vector<CyclingPowerProfileChart> male_;

  // power profile charts for female cyclist
  std::vector<CyclingPowerProfileChart> female_;

  // query for profiling
  CyclingPowerProfilerQuery query_;

  // loads power profile charts
  bool LoadPowerProfileChart(ProfileFormat format = kInternal);

  Category CalcPowerProfile(double power, CyclingPowerProfileChart &chart,
                            QueryResponse &result);

  Category CalcPowerProfileGoal(Category cat, CyclingPowerProfileChart &chart,
                                QueryResponse &result);

  bool SaveQueryJson(std::ostream &s);

  // file names to store/load power profile chart
  static constexpr const char *kFileNameJson_ = "CyclingPowerProfileChart.json";
  static constexpr const char *kFileNameBson_ = "CyclingPowerProfileChart.bson";

  // file name for query has the form: <date>_RCPQ.json or <date>_RCPQ.bson
  static constexpr const char *kFileNameSuffixQuery_ = "_RCPQ";
};

#endif // CYCLINGPOWERPROFILER_H
