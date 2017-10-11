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

#include <QCoreApplication>

// #include "Athlete.h"
#include "CyclingPowerProfileChart.h"
#include "CyclingPowerProfiler.h"
#include "CyclingPowerProfilerQuery.h"
#include "iProfiler.h"

#include "json.hpp"


int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  // init athlete
  Athlete me(Gender::kMale);
  Weight w = 65.6_kg;
  me.set_weight(w);

  // init profiler
  shared_ptr<CyclingPowerProfiler> profiler = std::make_shared<CyclingPowerProfiler>();
  profiler->Init();

  // build query
  profiler->ResetQuery();
  profiler->InitQuery(PowerType::kFt, 257.0);
  profiler->InitQuery(PowerType::k5Min, 416.0);
  profiler->InitQuery(PowerType::k1Min, 630.0);
  profiler->InitQuery(PowerType::k5Sec, 870.0);

  // run profiling on athlete 'me'
  me.set_profiler(profiler);
  me.DoProfiling();

  // save query and its results
  profiler->SaveQuery();

  return a.exec();
}
