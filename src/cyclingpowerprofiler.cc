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

#include "CyclingPowerProfiler.h"
// #include "json.hpp"

double watts_per_kg(double power, const Weight& weight) {
    return static_cast<double>(power / weight.kg());
}

// Power profile charts for male cyclists
const CyclingPowerProfileChart male_ftp =
{ PowerType::kFt,
  "Functional Threshold Power",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     1.86, 2.58),
      CyclingPowerProfileCategory(Category::kFair,          2.40, 3.11),
      CyclingPowerProfileCategory(Category::kModerate,      2.93, 3.64),
      CyclingPowerProfileCategory(Category::kGood,          3.47, 4.18),
      CyclingPowerProfileCategory(Category::kVeryGood,      4.09, 4.80),
      CyclingPowerProfileCategory(Category::kExcellent,     4.62, 5.33),
      CyclingPowerProfileCategory(Category::kExceptional,   5.15, 5.87),
      CyclingPowerProfileCategory(Category::kWorldClass,    5.69, 6.40)
  }
};

const CyclingPowerProfileChart male_map =
{ PowerType::k5Min,
  "Maximum Aerobic Power",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     2.33, 3.15),
      CyclingPowerProfileCategory(Category::kFair,          2.95, 3.77),
      CyclingPowerProfileCategory(Category::kModerate,      3.57, 4.39),
      CyclingPowerProfileCategory(Category::kGood,          4.19, 5.01),
      CyclingPowerProfileCategory(Category::kVeryGood,      4.91, 5.74),
      CyclingPowerProfileCategory(Category::kExcellent,     5.53, 6.36),
      CyclingPowerProfileCategory(Category::kExceptional,   6.15, 6.98),
      CyclingPowerProfileCategory(Category::kWorldClass,    6.77, 7.60)
  }
};

const CyclingPowerProfileChart male_ana =
{ PowerType::k1Min,
  "Anaerobic",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     5.64, 6.56),
      CyclingPowerProfileCategory(Category::kFair,          6.33, 7.25),
      CyclingPowerProfileCategory(Category::kModerate,      7.02, 7.94),
      CyclingPowerProfileCategory(Category::kGood,          7.71, 8.63),
      CyclingPowerProfileCategory(Category::kVeryGood,      8.51, 9.43),
      CyclingPowerProfileCategory(Category::kExcellent,     9.20, 10.12),
      CyclingPowerProfileCategory(Category::kExceptional,   9.89, 10.81),
      CyclingPowerProfileCategory(Category::kWorldClass,    10.58, 11.50)
  }
};

const CyclingPowerProfileChart male_nmu =
{ PowerType::k5Sec,
  "Neuro Muscular",
  {
      //                          Category                  Low    High
      CyclingPowerProfileCategory(Category::kUntrained,     10.17, 12.35),
      CyclingPowerProfileCategory(Category::kFair,          11.80, 13.98),
      CyclingPowerProfileCategory(Category::kModerate,      13.44, 15.61),
      CyclingPowerProfileCategory(Category::kGood,          15.07, 17.24),
      CyclingPowerProfileCategory(Category::kVeryGood,      16.97, 19.45),
      CyclingPowerProfileCategory(Category::kExcellent,     18.60, 20.78),
      CyclingPowerProfileCategory(Category::kExceptional,   20.23, 22.41),
      CyclingPowerProfileCategory(Category::kWorldClass,    21.86, 24.04)
  }
};

// Power profile charts for female cyclists
const CyclingPowerProfileChart female_ftp =
{ PowerType::kFt,
  "Functional Threshold Power",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     1.50, 2.16),
      CyclingPowerProfileCategory(Category::kFair,          1.99, 2.65),
      CyclingPowerProfileCategory(Category::kModerate,      2.49, 3.14),
      CyclingPowerProfileCategory(Category::kGood,          2.98, 3.64),
      CyclingPowerProfileCategory(Category::kVeryGood,      3.55, 4.21),
      CyclingPowerProfileCategory(Category::kExcellent,     4.05, 4.70),
      CyclingPowerProfileCategory(Category::kExceptional,   4.54, 5.20),
      CyclingPowerProfileCategory(Category::kWorldClass,    5.03, 5.69)
  }
};

const CyclingPowerProfileChart female_map =
{ PowerType::k5Min,
  "Maximum Aerobic Power",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     1.89, 2.63),
      CyclingPowerProfileCategory(Category::kFair,          2.45, 3.19),
      CyclingPowerProfileCategory(Category::kModerate,      3.00, 3.74),
      CyclingPowerProfileCategory(Category::kGood,          3.56, 4.30),
      CyclingPowerProfileCategory(Category::kVeryGood,      4.20, 4.94),
      CyclingPowerProfileCategory(Category::kExcellent,     4.76, 5.50),
      CyclingPowerProfileCategory(Category::kExceptional,   5.31, 6.05),
      CyclingPowerProfileCategory(Category::kWorldClass,    5.87, 6.61)
  }
};

const CyclingPowerProfileChart female_ana =
{ PowerType::k1Min,
  "Anaerobic",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     4.67, 5.39),
      CyclingPowerProfileCategory(Category::kFair,          5.21, 5.94),
      CyclingPowerProfileCategory(Category::kModerate,      5.76, 6.48),
      CyclingPowerProfileCategory(Category::kGood,          6.30, 7.02),
      CyclingPowerProfileCategory(Category::kVeryGood,      6.93, 7.66),
      CyclingPowerProfileCategory(Category::kExcellent,     7.48, 8.20),
      CyclingPowerProfileCategory(Category::kExceptional,   8.02, 8.75),
      CyclingPowerProfileCategory(Category::kWorldClass,    8.56, 9.29)
  }
};

const CyclingPowerProfileChart female_nmu =
{ PowerType::k5Sec,
  "Neuro Muscular",
  {
      //                          Category                  Low   High
      CyclingPowerProfileCategory(Category::kUntrained,     8.43, 10.15),
      CyclingPowerProfileCategory(Category::kFair,          9.72, 11.45),
      CyclingPowerProfileCategory(Category::kModerate,      11.01, 12.74),
      CyclingPowerProfileCategory(Category::kGood,          12.31, 14.03),
      CyclingPowerProfileCategory(Category::kVeryGood,      13.82, 15.54),
      CyclingPowerProfileCategory(Category::kExcellent,     15.11, 16.83),
      CyclingPowerProfileCategory(Category::kExceptional,   16.40, 18.13),
      CyclingPowerProfileCategory(Category::kWorldClass,    17.70, 19.42)
  }
};

void CyclingPowerProfiler::Init()
{
    LoadPowerProfileChart(CyclingPowerProfiler::kInternal);
}

void CyclingPowerProfiler::ResetQuery() {
    query_.request.power.clear();
}

bool CyclingPowerProfiler::InitQuery(PowerType type,
                                     int watts) {
    // sanity checks: power <= 2000W
    if (watts > 2000) return false;

    query_.request.power.push_back(std::make_pair(type, double(watts)));
    return true;
}

bool CyclingPowerProfiler::SaveQuery(ProfileFormat /* format */) {
    return false;
}

bool CyclingPowerProfiler::Run(const Athlete& athlete) {
    double power_ftp, power_map, power_ana, power_nmu = double(0);
    // calc input power values as W/kg for different power types
    for (auto&& i : query_.request.power) {
        switch (i.first)
        {
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
    if (power_ftp < 0 && power_map < 0 && power_ana < 0 && power_nmu < 0)
        return false;

    // determine chart to be used for calculations
    std::vector<CyclingPowerProfileChart>& chart =
            (query_.request.gender == Gender::kFemale ? female_ : male_);


    // calculate power profiles
    for (auto&& c : chart) {
        // indexes into chart table power values
        // int idx_ftp, idx_map, idx_ana, idx_nmu = -1;

        if (c.type == PowerType::kFt && power_ftp > 1)
            /* idx_ftp = */ CalcPowerProfile(power_ftp, c, query_.response);
        if (c.type == PowerType::k5Min && power_map > 1)
            /* idx_map = */ CalcPowerProfile(power_map, c, query_.response);
        if (c.type == PowerType::k1Min && power_ana > 1)
            /* idx_ana = */ CalcPowerProfile(power_ana, c, query_.response);
        if (c.type == PowerType::k5Sec && power_nmu > 1)
            /* idx_nmu = */ CalcPowerProfile(power_nmu, c, query_.response);
    }

    /*
    // find goals based on other chart table indexes if power not given
    if (idx_ftp < 0) {
        for (auto&& c : chart) {
            std::vector<int> idx;
            if (c.type == PowerType::kFt) {
                if (idx_map >= 0)
                    idx.push_back(idx_map);
                else if (idx_ana >= 0)
                    idx.push_back(idx_ana);
                else if (idx_nmu >= 0)
                    idx.push_back(idx_nmu);

                long avg =
                        lround(std::accumulate(idx.begin(), idx.end(), 0) / idx.size());
                idx_ftp = CalcPowerProfileGoal(avg, c, query_.response);
                break;
            }
        }
    }
    if (idx_map < 0) {
        for (auto&& c : chart) {
            std::vector<int> idx;
            if (c.type == PowerType::k5Min) {
                if (idx_ana >= 0)
                    idx.push_back(idx_ana);
                else if (idx_ftp >= 0)
                    idx.push_back(idx_ftp);
                else if (idx_nmu >= 0)
                    idx.push_back(idx_nmu);

                long avg =
                        lround(std::accumulate(idx.begin(), idx.end(), 0) / idx.size());
                idx_map = CalcPowerProfileGoal(avg, c, query_.response);
                break;
            }
        }
    }
    if (idx_ana < 0) {
        for (auto&& c : chart) {
            std::vector<int> idx;
            if (c.type == PowerType::k1Min) {
                if (idx_map >= 0)
                    idx.push_back(idx_map);
                else if (idx_nmu >= 0)
                    idx.push_back(idx_nmu);
                else if (idx_ftp >= 0)
                    idx.push_back(idx_ftp);

                long avg =
                        lround(std::accumulate(idx.begin(), idx.end(), 0) / idx.size());
                idx_ana = CalcPowerProfileGoal(avg, c, query_.response);
                break;
            }
        }
    }
    if (idx_nmu < 0) {
        for (auto&& c : chart) {
            std::vector<int> idx;
            if (c.type == PowerType::k5Sec) {
                if (idx_ana >= 0)
                    idx.push_back(idx_ana);
                else if (idx_map >= 0)
                    idx.push_back(idx_map);
                else if (idx_ftp >= 0)
                    idx.push_back(idx_ftp);

                long avg =
                        lround(std::accumulate(idx.begin(), idx.end(), 0) / idx.size());
                idx_nmu = CalcPowerProfileGoal(avg, c, query_.response);
                break;
            }
        }
    }
    */
    return true;
}

int CyclingPowerProfiler::CalcPowerProfile(double /* power */,
                                           CyclingPowerProfileChart& /* chart */,
                                           QueryResponse& /* result */) {
    return -1;
}

int CyclingPowerProfiler::CalcPowerProfileGoal(long /* idx */,
                                               CyclingPowerProfileChart& /* chart */,
                                               QueryResponse& /* result */) {
    return -1;
}

bool CyclingPowerProfiler::LoadPowerProfileChart(ProfileFormat format) {

    if (format == CyclingPowerProfiler::kInternal)
    {
        male_.clear();
        male_ = { male_ftp, male_map, male_ana, male_nmu };
        female_.clear();
        female_ = { female_ftp, female_map, female_ana, female_nmu };
        return true;
    }

    return false;
}
