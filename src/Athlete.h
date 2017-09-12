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

#include <memory>

#include "iProfiler.h"

class Athlete {
 public:
  enum Gender { kUndef = 0, kMale, kFemale };

  Athlete() : gender_(kUndef), profiler_(0) {}
  explicit Athlete(const Gender& gender) { set_gender(gender); }
  virtual ~Athlete(){};

  bool DoProfiling() {
    return (profiler_ != 0 ? profiler_->Run(*this) : false);
  }

  void set_gender(const Gender& gender) { gender_ = gender; }
  Gender gender() const { return gender_; }

  void set_weight(double weight) { weight_ = weight; }
  double weight() const { return weight_; }

  void set_profiler(std::shared_ptr<IProfiler> profiler) {
    this->profiler_ = profiler;
  }

 protected:
 private:
  Gender gender_;
  double weight_;

  // Interface for profiler tool
  std::shared_ptr<IProfiler> profiler_;
};

#endif  // ATHLETE_H
