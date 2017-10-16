# Power Profiler for Cycling

## Abstract
Multi platform (Linux, Windows, macOS, Android etc.) app to determine power profile for road cyclists that use power meter when riding, training or racing. The app uses cycling power profile chart developed by Hunter Allan & Dr. Andrew Coggan for comparison and classification.    

Depends on Qt cross-platform application development toolkit.

## Power Profiling Chart
Following image shows the power profile chart utilized in profile calculations:

<p align="left">
  <img src="https://user-images.githubusercontent.com/22800635/31544246-846eff42-b022-11e7-826b-8b9e1a825474.gif" width="720"/>
</p>


## Power Profiling API V1
The following rider properties are needed for power profile calculation:
* gender,
* weight,
* best effort power in watts for following durations: 
  * 5 sec (neuromuscular capacity),
  * 1 min (anaerobic capacity),
  * 5 min (maximal aerobic capacity, VO2 max),  
  * 60 min (functional threshold power, FTP)
  
The calculation results shows the following parameters for each effort:
  * category (Untrained, Fair, Moderate, Good, Very Good, Excellent, Exceptional, World Class),
  * power as watts per kg,
  * position within category (1-100),
  * overall position by gender (1-100)
  
Following CLI test program output shows profile query and results in JSON format:

> **./PowerProfiler -gender male -weight 64 -ftp 257 -vo2 304 -ana 539 -nmu 905**
```
{
    "date_time": "16-10-2017 13-25-54",
    "description": "cycling power profile",
    "query": {
        "athlete": {
            "gender": "male",
            "weight": 64.0
        },
        "cycling_power": [
            {
                "effort": "60min Best Power(FTP)",
                "unit": "W",
                "value": 257.0
            },
            {
                "effort": "5min Best Power",
                "unit": "W",
                "value": 304.0
            },
            {
                "effort": "1min Best Power",
                "unit": "W",
                "value": 539.0
            },
            {
                "effort": "5sec Best Power",
                "unit": "W",
                "value": 905.0
            }
        ]
    },
    "result": {
        "categories": {
            "1": "Untrained",
            "2": "Fair",
            "3": "Moderate",
            "4": "Good",
            "5": "Very Good",
            "6": "Excellent",
            "7": "Exceptional",
            "8": "World Class Professional"
        },
        "cycling_profile": [
            {
                "category": "Good",
                "effort": "60min Best Power(FTP)",
                "power_unit": "W/kg",
                "power_value": 4.02,
                "ranking_category": {
                    "position": 23,
                    "range": [
                        3.47,
                        4.18
                    ]
                },
                "ranking_gender": {
                    "position": 52,
                    "range": [
                        1.86,
                        6.4
                    ]
                },
                "target": "no"
            },
            {
                "category": "Good",
                "effort": "5min Best Power",
                "power_unit": "W/kg",
                "power_value": 4.75,
                "ranking_category": {
                    "position": 31,
                    "range": [
                        4.19,
                        5.01
                    ]
                },
                "ranking_gender": {
                    "position": 54,
                    "range": [
                        2.33,
                        7.6
                    ]
                },
                "target": "no"
            },
            {
                "category": "Good",
                "effort": "1min Best Power",
                "power_unit": "W/kg",
                "power_value": 8.42,
                "ranking_category": {
                    "position": 22,
                    "range": [
                        7.71,
                        8.63
                    ]
                },
                "ranking_gender": {
                    "position": 52,
                    "range": [
                        5.64,
                        11.5
                    ]
                },
                "target": "no"
            },
            {
                "category": "Moderate",
                "effort": "5sec Best Power",
                "power_unit": "W/kg",
                "power_value": 14.14,
                "ranking_category": {
                    "position": 67,
                    "range": [
                        13.44,
                        15.61
                    ]
                },
                "ranking_gender": {
                    "position": 71,
                    "range": [
                        10.17,
                        24.04
                    ]
                },
                "target": "no"
            }
        ],
        "status": 0
    }
}
```

## User Interface
GUI is under development. Following image shows the rider property and profile view pages:

<p align="left">
  <img src="https://user-images.githubusercontent.com/22800635/31576907-91cc72c8-b10d-11e7-94b1-a64a6427809a.jpg" />
</p>
