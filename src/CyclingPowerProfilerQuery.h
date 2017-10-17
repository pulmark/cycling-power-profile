/*
** Copyright (c) 2017 Markku Pulkkinen. All rights reserved.
** Contact: markku.j.pulkkinen@gmail.com
**
** This file is part of CyclingPowerProfiler software distribution.
**
** This software is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This software is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this software.  If not, see <http://www.gnu.org/licenses/>.
*/

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
  std::string category_name{};
  PowerType type{};
  double watts{};
  double rank_category{};
  std::pair<double, double> category_range;
  double rank_gender{};
  std::pair<double, double> gender_range;
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
