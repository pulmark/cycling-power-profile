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

#ifndef CYCLINGPOWERPROFILECHART_H
#define CYCLINGPOWERPROFILECHART_H

#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>

// enums for different categories
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

// enums for power types
enum class PowerType {
  kUndefined = 0,
  kFt,   // functional threshold power
  k5Min, // 5min best power
  k1Min, // 1min best power
  k5Sec  // 5sec best power
};

enum class PowerUnit { kUndefined = 0, kWatt, kWattKg };

enum class EnergySystem {
  kUndefined = 0,
  kMlss,      // maximum lactate steady sate
  kMap,       // maximum aerobic power
  kAnaerobic, // ananerobic
  kNm         // neuromuscular
};

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

// power type to string
const std::map<PowerType, std::string> PowerTypeList{
    {PowerType::kFt, "60min Best Power(FTP)"},
    {PowerType::k5Min, "5min Best Power"},
    {PowerType::k1Min, "1min Best Power"},
    {PowerType::k5Sec, "5sec Best Power"},
};

// category to string
const std::map<Category, std::string> CategoryList{
    {Category::kUntrained, "Untrained"},
    {Category::kFair, "Fair"},
    {Category::kModerate, "Moderate"},
    {Category::kGood, "Good"},
    {Category::kVeryGood, "Very Good"},
    {Category::kExcellent, "Excellent"},
    {Category::kExceptional, "Exceptional"},
    {Category::kWorldClass, "World Class Professional"}};

// power profile charts for male cyclists
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

// power profile charts for female cyclists
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

#endif // CYCLINGPOWERPROFILECHART_H
