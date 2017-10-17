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

#ifndef ATHLETE_H
#define ATHLETE_H

#include <cassert>
#include <memory>

#include "iProfiler.h"

///////////////////////////////////////////////////////////////////////////////
template <class T> bool check_range(T value, T min, T max) {
  return (value >= min) && (value <= max);
};

///////////////////////////////////////////////////////////////////////////////
class Weight {
public:
  class dummy {}; // dummy class to prevent direct assignment of weights
  explicit constexpr Weight(dummy, double kg) : kg_(kg) {}
  double kg() const { return kg_; }

private:
  double kg_; // weight in kilograms
};

constexpr Weight operator"" _kg(long double weight) {
  return Weight{Weight::dummy{}, static_cast<double>(weight)};
}

constexpr Weight operator"" _lb(long double weight) {
  return Weight{Weight::dummy{}, static_cast<double>(weight * 0.45359237)};
}

constexpr double operator"" _W(long double watts) {
  return static_cast<double>(watts);
}

///////////////////////////////////////////////////////////////////////////////
enum class Gender { kUndef = 0, kMale, kFemale };

///////////////////////////////////////////////////////////////////////////////
class Athlete {
public:
  Athlete()
      : gender_{Gender::kUndef}, weight_{Weight::dummy{}, 0},
        profiler_{nullptr} {}
  explicit Athlete(const Gender &gender)
      : weight_{Weight::dummy{}, 0}, profiler_{nullptr} {
    set_gender(gender);
  }
  virtual ~Athlete() {}

  // does profiling for the athlete
  bool DoProfiling() {
    return (profiler_ != nullptr ? profiler_->Run(*this) : false);
  }

  // setters
  void set_gender(const Gender &gender) {
    assert((gender != Gender::kUndef) && "gender not defined");
    gender_ = gender;
  }

  void set_weight(const Weight &weight) {
    assert(check_range(weight.kg(), weight_min, weight_max) &&
           "weight out of range");
    weight_ = weight;
  }

  void set_profiler(std::shared_ptr<IProfiler> profiler) {
    profiler_.reset();
    profiler_ = profiler;
  }

  // getters
  Gender gender() const { return gender_; }
  Weight weight() const { return weight_; }

protected:
private:
  Gender gender_; // male, female
  Weight weight_; // weight in kgs

  // interface into profiler tool
  std::shared_ptr<IProfiler> profiler_;

  // athlete weight range in kgs
  static constexpr double weight_min = 20.0;
  static constexpr double weight_max = 150.0;
};

#endif // ATHLETE_H
