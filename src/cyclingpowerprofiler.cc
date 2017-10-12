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

#include <chrono>
#include <ctime>

#include "CyclingPowerProfiler.h"
// #include "json.hpp"

double watts_per_kg(double power, const Weight &weight) {
  return static_cast<double>(power / weight.kg());
}

const std::map<Category, std::string> CategoryList{
    {Category::kUntrained, "Untrained"},
    {Category::kFair, "Fair"},
    {Category::kModerate, "Moderate"},
    {Category::kGood, "Good"},
    {Category::kVeryGood, "Very Good"},
    {Category::kExcellent, "Excellent"},
    {Category::kExceptional, "Exceptional"},
    {Category::kWorldClass, "World Class Professional"}};

// Power profile charts for male cyclists
const CyclingPowerProfileChart male_ftp = {
    PowerType::kFt,
    "Functional Threshold Power",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 1.86, 2.58),
     CyclingPowerProfileCategory(Category::kFair, 2.40, 3.11),
     CyclingPowerProfileCategory(Category::kModerate, 2.93, 3.64),
     CyclingPowerProfileCategory(Category::kGood, 3.47, 4.18),
     CyclingPowerProfileCategory(Category::kVeryGood, 4.09, 4.80),
     CyclingPowerProfileCategory(Category::kExcellent, 4.62, 5.33),
     CyclingPowerProfileCategory(Category::kExceptional, 5.15, 5.87),
     CyclingPowerProfileCategory(Category::kWorldClass, 5.69, 6.40)}};

const CyclingPowerProfileChart male_map = {
    PowerType::k5Min,
    "Maximum Aerobic Power",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 2.33, 3.15),
     CyclingPowerProfileCategory(Category::kFair, 2.95, 3.77),
     CyclingPowerProfileCategory(Category::kModerate, 3.57, 4.39),
     CyclingPowerProfileCategory(Category::kGood, 4.19, 5.01),
     CyclingPowerProfileCategory(Category::kVeryGood, 4.91, 5.74),
     CyclingPowerProfileCategory(Category::kExcellent, 5.53, 6.36),
     CyclingPowerProfileCategory(Category::kExceptional, 6.15, 6.98),
     CyclingPowerProfileCategory(Category::kWorldClass, 6.77, 7.60)}};

const CyclingPowerProfileChart male_ana = {
    PowerType::k1Min,
    "Anaerobic",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 5.64, 6.56),
     CyclingPowerProfileCategory(Category::kFair, 6.33, 7.25),
     CyclingPowerProfileCategory(Category::kModerate, 7.02, 7.94),
     CyclingPowerProfileCategory(Category::kGood, 7.71, 8.63),
     CyclingPowerProfileCategory(Category::kVeryGood, 8.51, 9.43),
     CyclingPowerProfileCategory(Category::kExcellent, 9.20, 10.12),
     CyclingPowerProfileCategory(Category::kExceptional, 9.89, 10.81),
     CyclingPowerProfileCategory(Category::kWorldClass, 10.58, 11.50)}};

const CyclingPowerProfileChart male_nmu = {
    PowerType::k5Sec,
    "Neuro Muscular",
    {//                          Category              Low    High
     CyclingPowerProfileCategory(Category::kUntrained, 10.17, 12.35),
     CyclingPowerProfileCategory(Category::kFair, 11.80, 13.98),
     CyclingPowerProfileCategory(Category::kModerate, 13.44, 15.61),
     CyclingPowerProfileCategory(Category::kGood, 15.07, 17.24),
     CyclingPowerProfileCategory(Category::kVeryGood, 16.97, 19.45),
     CyclingPowerProfileCategory(Category::kExcellent, 18.60, 20.78),
     CyclingPowerProfileCategory(Category::kExceptional, 20.23, 22.41),
     CyclingPowerProfileCategory(Category::kWorldClass, 21.86, 24.04)}};

// Power profile charts for female cyclists
const CyclingPowerProfileChart female_ftp = {
    PowerType::kFt,
    "Functional Threshold Power",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 1.50, 2.16),
     CyclingPowerProfileCategory(Category::kFair, 1.99, 2.65),
     CyclingPowerProfileCategory(Category::kModerate, 2.49, 3.14),
     CyclingPowerProfileCategory(Category::kGood, 2.98, 3.64),
     CyclingPowerProfileCategory(Category::kVeryGood, 3.55, 4.21),
     CyclingPowerProfileCategory(Category::kExcellent, 4.05, 4.70),
     CyclingPowerProfileCategory(Category::kExceptional, 4.54, 5.20),
     CyclingPowerProfileCategory(Category::kWorldClass, 5.03, 5.69)}};

const CyclingPowerProfileChart female_map = {
    PowerType::k5Min,
    "Maximum Aerobic Power",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 1.89, 2.63),
     CyclingPowerProfileCategory(Category::kFair, 2.45, 3.19),
     CyclingPowerProfileCategory(Category::kModerate, 3.00, 3.74),
     CyclingPowerProfileCategory(Category::kGood, 3.56, 4.30),
     CyclingPowerProfileCategory(Category::kVeryGood, 4.20, 4.94),
     CyclingPowerProfileCategory(Category::kExcellent, 4.76, 5.50),
     CyclingPowerProfileCategory(Category::kExceptional, 5.31, 6.05),
     CyclingPowerProfileCategory(Category::kWorldClass, 5.87, 6.61)}};

const CyclingPowerProfileChart female_ana = {
    PowerType::k1Min,
    "Anaerobic",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 4.67, 5.39),
     CyclingPowerProfileCategory(Category::kFair, 5.21, 5.94),
     CyclingPowerProfileCategory(Category::kModerate, 5.76, 6.48),
     CyclingPowerProfileCategory(Category::kGood, 6.30, 7.02),
     CyclingPowerProfileCategory(Category::kVeryGood, 6.93, 7.66),
     CyclingPowerProfileCategory(Category::kExcellent, 7.48, 8.20),
     CyclingPowerProfileCategory(Category::kExceptional, 8.02, 8.75),
     CyclingPowerProfileCategory(Category::kWorldClass, 8.56, 9.29)}};

const CyclingPowerProfileChart female_nmu = {
    PowerType::k5Sec,
    "Neuro Muscular",
    {//                          Category              Low   High
     CyclingPowerProfileCategory(Category::kUntrained, 8.43, 10.15),
     CyclingPowerProfileCategory(Category::kFair, 9.72, 11.45),
     CyclingPowerProfileCategory(Category::kModerate, 11.01, 12.74),
     CyclingPowerProfileCategory(Category::kGood, 12.31, 14.03),
     CyclingPowerProfileCategory(Category::kVeryGood, 13.82, 15.54),
     CyclingPowerProfileCategory(Category::kExcellent, 15.11, 16.83),
     CyclingPowerProfileCategory(Category::kExceptional, 16.40, 18.13),
     CyclingPowerProfileCategory(Category::kWorldClass, 17.70, 19.42)}};

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

bool CyclingPowerProfiler::SaveQuery(ProfileFormat /* format */) {
  return false;
}

bool CyclingPowerProfiler::Run(const Athlete &athlete) {
  double power_ftp, power_map, power_ana, power_nmu = double(-1);

  query_.request.gender = athlete.gender();
  query_.request.weight = athlete.weight().kg();

  auto now = std::chrono::system_clock::now();
  auto time_now = std::chrono::system_clock::to_time_t(now);
  query_.date = std::ctime(&time_now);
  query_.name = "CyclingPowerProfiler";
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

  for (auto &&c : chart.categories) {
    if (watts >= c.low && watts <= c.high) {
      QueryResponseItem item;
      item.type = chart.type;
      item.watts = watts;
      item.category_name = CategoryList.at(c.id);
      item.category_range = std::make_pair(c.low, c.high);
      item.procents = ((watts - c.low) / (c.high - c.low)) * 100;
      item.is_goal = false;
      result.items.push_back(item);
      return c.id;
    }
  }

  return Category::kUndefined;
}

Category CyclingPowerProfiler::CalcPowerProfileGoal(
    Category cat, CyclingPowerProfileChart &chart, QueryResponse &result) {

  for (auto &&c : chart.categories) {
    if (cat == c.id) {
      QueryResponseItem item;
      item.type = chart.type;
      item.watts = 0;
      item.procents = 0;
      item.category_name = CategoryList.at(c.id);
      item.category_range = std::make_pair(c.low, c.high);
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
