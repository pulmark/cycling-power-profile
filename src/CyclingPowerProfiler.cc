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

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "CyclingPowerProfiler.h"
#include "json.hpp"
using json = nlohmann::json;

double watts_per_kg(double power, const Weight &weight) {
  return static_cast<double>(power / weight.kg());
}

void CyclingPowerProfiler::Init() {
  LoadPowerProfileChart(CyclingPowerProfiler::kInternal);
}

void CyclingPowerProfiler::ResetQuery() { query_.request.power.clear(); }

bool CyclingPowerProfiler::InitQuery(PowerType type, double watts,
                                     PowerUnit unit) {
  // sanity checks: power <= 2000W and unit is watts
  if (unit != PowerUnit::kWatt && watts > 2000)
    return false;

  query_.request.power.push_back(std::make_pair(type, double(watts)));
  return true;
}

bool CyclingPowerProfiler::SaveQuery(std::ostream &s, ProfileFormat format) {

  if (format == ProfileFormat::kJson) {
    return (SaveQueryJson(s));
  }
  return false;
}

bool CyclingPowerProfiler::Run(const Athlete &athlete) {
  double power_ftp, power_map, power_ana, power_nmu = double(-1);

  query_.request.gender = athlete.gender();
  query_.request.weight = athlete.weight().kg();

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%YT%H-%M-%S%z");
  query_.date = oss.str();
  query_.name = "cycling power profile";
  query_.request.unit = PowerUnit::kWatt;

  // calc input power values as W/kg for different power types
  for (auto &&i : query_.request.power) {
    switch (i.first) {
    default:
      break;
    case PowerType::kFt:
      power_ftp = watts_per_kg(i.second, athlete.weight());
      break;
    case PowerType::k5Min:
      power_map = watts_per_kg(i.second, athlete.weight());
      break;
    case PowerType::k1Min:
      power_ana = watts_per_kg(i.second, athlete.weight());
      break;
    case PowerType::k5Sec:
      power_nmu = watts_per_kg(i.second, athlete.weight());
      break;
    }
  }

  // sanity check: at least one of power values must be set
  if (power_ftp < 0 && power_map < 0 && power_ana < 0 && power_nmu < 0) {
    query_.response.status = -1;
    return false;
  }

  // determine chart to be used for calculations
  auto &chart = (query_.request.gender == Gender::kFemale ? female_ : male_);

  // calculate power profiles
  Category ftp_cat, map_cat, ana_cat, nmu_cat = Category::kUndefined;
  for (auto &&c : chart) {
    switch (c.type) {
    default:
      break;

    case PowerType::kFt:
      ftp_cat = CalcPowerProfile(power_ftp, c, query_.response);
      break;

    case PowerType::k5Min:
      map_cat = CalcPowerProfile(power_map, c, query_.response);
      break;

    case PowerType::k1Min:
      ana_cat = CalcPowerProfile(power_ana, c, query_.response);
      break;

    case PowerType::k5Sec:
      nmu_cat = CalcPowerProfile(power_nmu, c, query_.response);
      break;
    }
  }

  bool no_ftp{ftp_cat == Category::kUndefined};
  bool no_map{map_cat == Category::kUndefined};
  bool no_ana{ana_cat == Category::kUndefined};
  bool no_nmu{nmu_cat == Category::kUndefined};

  if (!no_ftp && !no_map && !no_ana && !no_nmu)
    return true;

  // calculate goals for power types not given
  Category cat{Category::kUndefined};
  for (auto &&c : chart) {
    switch (c.type) {
    default:
      break;

    case PowerType::kFt:
      // determine ftp goal using map->ana->nmu category ordering
      if (no_ftp && !no_map)
        cat = map_cat;
      else if (no_ftp && !no_ana)
        cat = ana_cat;
      else if (no_ftp && !no_nmu)
        cat = nmu_cat;
      if (cat != Category::kUndefined)
        ftp_cat = CalcPowerProfileGoal(cat, c, query_.response);
      break;

    case PowerType::k5Min:
      // determine maximum aerobic goal using ftp category
      if (no_map) {
        map_cat = CalcPowerProfileGoal(ftp_cat, c, query_.response);
      }
      break;

    case PowerType::k1Min:
      // determine anaerobic goal using maximum aerobic power category
      if (no_ana) {
        ana_cat = CalcPowerProfileGoal(map_cat, c, query_.response);
      }
      break;

    case PowerType::k5Sec:
      // determine neuromuscular goal using anaerobic category
      if (no_nmu) {
        nmu_cat = CalcPowerProfileGoal(ana_cat, c, query_.response);
      }
      break;
    }
  }

  return true;
}

Category CyclingPowerProfiler::CalcPowerProfile(double watts,
                                                CyclingPowerProfileChart &chart,
                                                QueryResponse &result) {

  // init overall wgender range to [chart[first].low, chart[last].high]
  double gender_low = chart.categories.begin()->low;
  double gender_high = chart.categories.rbegin()->high;

  for (auto &&c : chart.categories) {
    if (watts >= c.low && watts <= c.high) {
      QueryResponseItem item;
      item.type = chart.type;
      item.watts = watts;
      item.category_name = CategoryList.at(c.id);
      item.category_range = std::make_pair(c.low, c.high);
      item.rank_category =
          100 - (((item.watts - c.low) / (c.high - c.low)) * 100);
      item.rank_gender =
          100 -
          (((item.watts - gender_low) / (gender_high - gender_low)) * 100);
      item.gender_range = std::make_pair(gender_low, gender_high);
      item.is_goal = false;
      result.items.push_back(item);
      return c.id;
    }
  }

  return Category::kUndefined;
}

Category CyclingPowerProfiler::CalcPowerProfileGoal(
    Category cat, CyclingPowerProfileChart &chart, QueryResponse &result) {

  // init overall gender range to [chart[first].low, chart[last].high]
  double gender_low = chart.categories.begin()->low;
  double gender_high = chart.categories.rbegin()->high;

  for (auto &&c : chart.categories) {
    if (cat == c.id) {
      QueryResponseItem item;
      item.type = chart.type;
      item.watts = c.low;
      item.rank_category = 100;
      item.category_name = CategoryList.at(c.id);
      item.category_range = std::make_pair(c.low, c.high);
      item.rank_gender =
          100 -
          (((item.watts - gender_low) / (gender_high - gender_low)) * 100);
      item.gender_range = std::make_pair(gender_low, gender_high);
      item.is_goal = true;
      result.items.push_back(item);
      return c.id;
    }
  }

  return Category::kUndefined;
}

bool CyclingPowerProfiler::LoadPowerProfileChart(ProfileFormat format) {

  if (format == CyclingPowerProfiler::kInternal) {
    male_.clear();
    male_ = {male_ftp, male_map, male_ana, male_nmu};
    female_.clear();
    female_ = {female_ftp, female_map, female_ana, female_nmu};
    return true;
  }

  return false;
}

bool CyclingPowerProfiler::SaveQueryJson(std::ostream &s) {
  json j;
  j["date_time"] = query_.date;
  j["description"] = query_.name;

  json request;
  request["athlete"] = {
      {"gender", (query_.request.gender == Gender::kMale ? "male" : "female")},
      {"weight", query_.request.weight}};
  // request["power unit"] = query_.request.unit;
  json items;
  for (auto &&k : query_.request.power) {
    json item;
    item["unit"] = "W";
    item["effort"] = PowerTypeList.at(k.first);
    item["value"] = k.second;
    items.push_back(item);
  }
  request["cycling_power"] = items;
  j["query"] = request;

  json response;
  response["status"] = query_.response.status;

  for (auto &&k : CategoryList) {
    std::ostringstream ss;
    ss << static_cast<int>(k.first);
    response["categories"][ss.str()] = k.second;
  }

  items.clear();
  for (auto &&k : query_.response.items) {
    json item;
    item["category"] = k.category_name;
    item["effort"] = PowerTypeList.at(k.type);
    item["power_unit"] = "W/kg";
    std::stringstream tmp;
    tmp << std::setprecision(2) << std::fixed << k.watts;
    item["power_value"] = stod(tmp.str());
    item["ranking_category"]["position"] = static_cast<int>(k.rank_category);
    item["ranking_category"]["range"] = k.category_range;
    item["ranking_gender"]["position"] = static_cast<int>(k.rank_gender);
    item["ranking_gender"]["range"] = k.gender_range;
    item["target"] = (k.is_goal ? "yes" : "no");
    items.push_back(item);
  }
  response["cycling_profile"] = items;
  j["result"] = response;

  s << std::setw(4) << j << std::endl;

  return true;
}
