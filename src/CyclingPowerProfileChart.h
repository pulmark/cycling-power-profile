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

#ifndef CYCLINGPOWERPROFILECHART_H
#define CYCLINGPOWERPROFILECHART_H

#include <vector>
#include <utility>

struct CyclingPowerProfileChart {
  enum PowerType { kUndefined = 0, kFt, k5Min, k1Min, k5Sec };
  enum PowerUnit { kWatt = 1, kWattKg };
  enum EnergySystem { kMlss = 1, kMap, kAnaerobic, kNm };

  enum Class {
    kUntrained = 1,
    kFair,
    kModerate,
    kGood,
    kVeryGood,
    kExcellent,
    kWorldClass
  };

  PowerType type;
  std::string description;

  // power values
  std::vector<double> values;

  // power classifications as range (lower limit, upper limit)

  // world class (international pro)
  std::pair<double, double> world;

  // domestic pro
  std::pair<double, double> excellent;

  // very good (Cat1)
  std::pair<double, double> very_good;

  // good (Cat2)
  std::pair<double, double> good;

  // moderate (Cat3)
  std::pair<double, double> moderate;

  // fair
  std::pair<double, double> fair;

  // untrained
  std::pair<double, double> untrained;
};

#endif  // CYCLINGPOWERPROFILECHART_H
