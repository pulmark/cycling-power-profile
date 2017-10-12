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

#ifndef CYCLINGPOWERPROFILER_H
#define CYCLINGPOWERPROFILER_H

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
  bool SaveQuery(ProfileFormat format = kJson);

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

  // file names to store/load power profile chart
  static constexpr const char *kFileNameJson_ = "CyclingPowerProfileChart.json";
  static constexpr const char *kFileNameBson_ = "CyclingPowerProfileChart.bson";

  // file name for query has the form: <date>_RCPQ.json or <date>_RCPQ.bson
  static constexpr const char *kFileNameSuffixQuery_ = "_RCPQ";
};

#endif // CYCLINGPOWERPROFILER_H
