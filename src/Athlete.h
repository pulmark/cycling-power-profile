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

#ifndef ATHLETE_H
#define ATHLETE_H

using namespace std;

#include <cassert>
#include <memory>

#include "iProfiler.h"

///////////////////////////////////////////////////////////////////////////////
template <class T>
bool check_range(T value, T min, T max) {
    return (value >= min) && (value <= max);
};

///////////////////////////////////////////////////////////////////////////////
class Weight {
public:
    class dummy {};  // dummy class to prevent direct assignment of weights
    explicit constexpr Weight(dummy, double kg) : kg_{kg} {}
    double kg() const { return kg_; }

private:
    double kg_ = 70.0;  // weight in kilograms
};

constexpr Weight operator"" _kg(long double weight) {
    return Weight{Weight::dummy{}, static_cast<double>(weight)};
}

constexpr Weight operator"" _lb(long double weight) {
    return Weight{Weight::dummy{}, static_cast<double>(weight * 0.45359237)};
}

///////////////////////////////////////////////////////////////////////////////
constexpr double operator"" _W(long double watts) {
    return static_cast<double>(watts);
}

///////////////////////////////////////////////////////////////////////////////
enum class Gender { kUndef = 0, kMale, kFemale };

///////////////////////////////////////////////////////////////////////////////
class Athlete {
public:
    Athlete() : gender_(Gender::kUndef), weight_{Weight::dummy{}, 0.0}, profiler_(nullptr) {}
    explicit Athlete(const Gender& gender) : weight_{Weight::dummy{}, 0.0}, profiler_(nullptr) { set_gender(gender); }
    virtual ~Athlete(){}

    // does profiling for the athlete
    bool DoProfiling() {
        return (profiler_ != nullptr ? profiler_->Run(*this) : false);
    }

    // setters
    void set_gender(const Gender& gender)
    {
        assert((gender != Gender::kUndef) && "gender not defined");
        gender_ = gender;
    }

    void set_weight(const Weight& weight)
    {
        assert(check_range(weight.kg(), weight_min, weight_max) && "weight out of range");
        weight_ = weight;
    }

    void set_profiler(shared_ptr<IProfiler> profiler) {
        profiler_.reset();
        profiler_ = profiler;
    }

    // getters
    Gender gender() const { return gender_; }
    Weight weight() const { return weight_; }


protected:
private:
    Gender gender_ {Gender::kUndef};    // male, female
    Weight weight_;                     // weight in kgs

    // interface into profiler tool
    shared_ptr<IProfiler> profiler_;

    // constants for athlete weight range in kgs
    static constexpr double weight_min = 20.0;
    static constexpr double weight_max = 150.0;
};

#endif  // ATHLETE_H
