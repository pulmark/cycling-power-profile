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

/* query contents:

{
  "name": "road-cycling-profiler-query",
  "date": "2012-04-23T18:25:43.511Z",
  "request": {
    "gender": "male",
    "weight": 65,
    "power-type": "ft",
    "power-unit": "w",
    "watts": 300
  },
  "response": {
    "status": 0,
    "result": [
      {
        "power-type": "ft",
        "watts": 300,
        "class": "good",
        "range": [
          280,
          360
        ]
      },
      {
        "power-type": "5min",
        "watts": 330,
        "class": "moderate",
        "range": [
          300,
          340
        ]
      },
      {
        "power-type": "1min",
        "watts": 540,
        "class": "good",
        "range": [
          500,
          600
        ]
      },
      {
        "power-type": "5sec",
        "watts": 920,
        "class": "good",
        "range": [
          890,
          1010
        ]
      }
    ]
  }
}

*/

#ifndef CYCLINGPOWERPROFILERQUERY_H
#define CYCLINGPOWERPROFILERQUERY_H

using namespace std;

#include <string>
#include <utility>
#include <vector>

#include "CyclingPowerProfileChart.h"

struct QueryRequest {
  Athlete::Gender gender;
  double weight;
  CyclingPowerProfileChart::PowerUnit unit;
  std::vector<std::pair<CyclingPowerProfileChart::PowerType, double> > power;
};

struct QueryResponseItem {
  CyclingPowerProfileChart::PowerType type;
  int watts;
  std::string classification;
  std::pair<double, double> class_range;
  bool is_goal;
};

struct QueryResponse {
  int status;
  std::vector<QueryResponseItem> items;
};

struct CyclingPowerProfilerQuery {
  std::string name;
  std::string date;
  QueryRequest request;
  QueryResponse response;
};

#endif  // CYCLINGPOWERPROFILERQUERY_H
