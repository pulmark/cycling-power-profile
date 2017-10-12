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

#include <array>
#include <map>
#include <utility>
#include <vector>

// enumerations for different categories
enum class Category {
  kUndefined = 0,
  kUntrained,
  kFair,
  kModerate,
  kGood,
  kVeryGood,
  kExcellent,
  kExceptional,
  kWorldClass
};

enum class PowerType { kUndefined = 0, kFt, k5Min, k1Min, k5Sec };

enum class PowerUnit { kWatt = 1, kWattKg };

enum class EnergySystem { kMlss = 1, kMap, kAnaerobic, kNm };

//////////////////////////////////////////////////////////////////////////////
struct CyclingPowerProfileCategory {
  CyclingPowerProfileCategory() : id(), low(), high() {}
  CyclingPowerProfileCategory(Category c, double l, double h)
      : id(c), low(l), high(h) {}

  Category id{};
  double low = 0.0;  // lowest power(W/kg)
  double high = 0.0; // highest power(W/kg)
};

//////////////////////////////////////////////////////////////////////////////
struct CyclingPowerProfileChart {
  PowerType type;
  std::string description;

  // power (watt/kg) categorirized as range (lower limit, upper limit)
  std::array<CyclingPowerProfileCategory, 8> categories;
};

//////////////////////////////////////////////////////////////////////////////
struct CyclingPowerProfile {
  std::array<CyclingPowerProfileChart, 4> male;
  std::array<CyclingPowerProfileChart, 4> female;
};

#endif // CYCLINGPOWERPROFILECHART_H
