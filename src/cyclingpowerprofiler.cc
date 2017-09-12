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
#include "json.hpp"

void CyclingPowerProfiler::ResetQuery() {
  query_.request.power.clear();
  query_.request.power.resize(
      4, std::make_pair(CyclingPowerProfileChart::kUndefined, -1.0));
}

bool CyclingPowerProfiler::InitQuery(CyclingPowerProfileChart::PowerType type,
                                     int watts) {
  // sanity checks: power <= 2000W and loading of PP chart succeeds
  if (watts > 2000 || !LoadPowerProfileChart()) return false;

  query_.request.power.push_back(std::make_pair(type, double(watts)));
  return true;
}

bool CyclingPowerProfiler::Run(Athlete& athlete) {
  // sanity check: athlete weight must be set between [20, 200]
  if (athlete.weight() < 20 || athlete.weight() > 200) return false;

  // retrieve input power values as W/kg for different power types
  double power_ftp, power_map, power_ana, power_nmu = double(-1);
  for (auto&& i : query_.request.power) {
    // FTP
    if (i.first == CyclingPowerProfileChart::kFt && i.second > 1)
      power_ftp = double(i.second / athlete.weight());
    // Peak Power 5min
    if (i.first == CyclingPowerProfileChart::k5Min && i.second > 1)
      power_map = double(i.second / athlete.weight());
    // Peak Power 1min
    if (i.first == CyclingPowerProfileChart::k1Min && i.second > 1)
      power_ana = double(i.second / athlete.weight());
    // Peak Power 5sec
    if (i.first == CyclingPowerProfileChart::k5Sec && i.second > 1)
      power_nmu = double(i.second / athlete.weight());
  }

  // sanity check: at least one of power values must be set
  if (lround(power_ftp) == lround(power_map) == lround(power_ana) ==
      lround(power_nmu) == 0)
    return false;

  // determine chart to be used for calculations
  std::vector<CyclingPowerProfileChart>& chart =
      (query_.request.gender == Athlete::kFemale ? female_ : male_);

  // indexes into chart table power values
  int idx_ftp, idx_map, idx_ana, idx_nmu = -1;

  // calculate power profiles
  for (auto&& c : chart) {
    if (c.type == CyclingPowerProfileChart::kFt && power_ftp > 1)
      idx_ftp = CalcPowerProfile(power_ftp, c, query_.response);
    if (c.type == CyclingPowerProfileChart::k5Min && power_map > 1)
      idx_map = CalcPowerProfile(power_map, c, query_.response);
    if (c.type == CyclingPowerProfileChart::k1Min && power_ana > 1)
      idx_ana = CalcPowerProfile(power_ana, c, query_.response);
    if (c.type == CyclingPowerProfileChart::k5Sec && power_nmu > 1)
      idx_nmu = CalcPowerProfile(power_nmu, c, query_.response);
  }

  // find goals based on other chart table indexes if power not given
  if (idx_ftp < 0) {
    for (auto&& c : chart) {
      std::vector<int> idx;
      if (c.type == CyclingPowerProfileChart::kFt) {
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
      if (c.type == CyclingPowerProfileChart::k5Min) {
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
      if (c.type == CyclingPowerProfileChart::k1Min) {
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
      if (c.type == CyclingPowerProfileChart::k5Sec) {
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
  return true;
}

int CyclingPowerProfiler::CalcPowerProfile(double power,
                                           CyclingPowerProfileChart& chart,
                                           QueryResponse& result) {
  return -1;
}

int CyclingPowerProfiler::CalcPowerProfileGoal(long idx,
                                               CyclingPowerProfileChart& chart,
                                               QueryResponse& result) {
  return -1;
}

bool CyclingPowerProfiler::LoadPowerProfileChart(ProfileFormat format) {
  return true;
}

bool CyclingPowerProfiler::SavePowerProfilerQuery(ProfileFormat format) {
  return true;
}
