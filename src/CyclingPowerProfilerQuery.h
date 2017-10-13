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

/* power profiler query and response contents (JSON format):

{
    "date_time": "13-10-2017 09-35-18",
    "description": "cycling power profile",
    "query": {
        "athlete": {
            "gender": "female",
            "weight": 67.5
        },
        "athlete_power": [
            {
                "id": "60min Best Power(FTP)",
                "unit": "W",
                "value": 257.0
            },
            {
                "id": "5min Best Power",
                "unit": "W",
                "value": 304.0
            },
            {
                "id": "1min Best Power",
                "unit": "W",
                "value": 539.0
            },
            {
                "id": "5sec Best Power",
                "unit": "W",
                "value": 905.0
            }
        ]
    },
    "result": {
        "categories": [
            {
                "category_name": "Very Good",
                "power_id": "60min Best Power(FTP)",
                "power_unit": "W/kg",
                "power_value": 3.81,
                "range_position": 61,
                "range_power_value": [
                    3.55,
                    4.21
                ],
                "target": "no"
            },
            {
                "category_name": "Very Good",
                "power_id": "5min Best Power",
                "power_unit": "W/kg",
                "power_value": 4.5,
                "range_position": 59,
                "range_power_value": [
                    4.2,
                    4.94
                ],
                "target": "no"
            },
            {
                "category_name": "Excellent",
                "power_id": "1min Best Power",
                "power_unit": "W/kg",
                "power_value": 7.99,
                "range_position": 30,
                "range_power_value": [
                    7.48,
                    8.2
                ],
                "target": "no"
            },
            {
                "category_name": "Good",
                "power_id": "5sec Best Power",
                "power_unit": "W/kg",
                "power_value": 13.41,
                "range_position": 37,
                "range_power_value": [
                    12.31,
                    14.03
                ],
                "target": "no"
            }
        ],
        "status": 0
    }
}

*/

#ifndef CYCLINGPOWERPROFILERQUERY_H
#define CYCLINGPOWERPROFILERQUERY_H

#include <string>
#include <utility>
#include <vector>

#include "Athlete.h"
#include "CyclingPowerProfileChart.h"

struct QueryRequest {
  Gender gender{};
  double weight{};
  PowerUnit unit{};
  std::vector<std::pair<PowerType, double>> power;
};

struct QueryResponseItem {
  PowerType type{};
  double watts{};
  double procents{};
  std::string category_name{};
  std::pair<double, double> category_range;
  bool is_goal{};
};

struct QueryResponse {
  int status{};
  std::vector<QueryResponseItem> items;
};

struct CyclingPowerProfilerQuery {
  std::string name{};
  std::string date{};
  QueryRequest request{};
  QueryResponse response{};
};

#endif // CYCLINGPOWERPROFILERQUERY_H
