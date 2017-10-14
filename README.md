# Power Profiler for Cycling

Multi platform (Linux, Windows, macOS, Android etc.) app to determine power profile for road cyclists that use power meter when riding, training or racing. The app uses cycling power profile chart developed by Hunter Allan & Dr. Andrew Coggan for comparison and classification.    

Depends on Qt cross-platform application development toolkit.

Following image shows the power profile chart utilized in profile calculations:

<p align="left">
  <img src="https://user-images.githubusercontent.com/22800635/31544246-846eff42-b022-11e7-826b-8b9e1a825474.gif" width="720"/>
</p>


Following CLI test program output shows profile query and results in JSON format:

>./PowerProfiler -gender male -weight 64 -ftp 257 -vo2 304 -ana 539 -nmu 937
```
{
    "date_time": "13-10-2017 14-49-40",
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
                "value": 937.0
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
                "range_position": 23,
                "range_power_value": [
                    3.47,
                    4.18
                ],
                "target": "no"
            },
            {
                "category": "Good",
                "effort": "5min Best Power",
                "power_unit": "W/kg",
                "power_value": 4.75,
                "range_position": 31,
                "range_power_value": [
                    4.19,
                    5.01
                ],
                "target": "no"
            },
            {
                "category": "Good",
                "effort": "1min Best Power",
                "power_unit": "W/kg",
                "power_value": 8.42,
                "range_position": 22,
                "range_power_value": [
                    7.71,
                    8.63
                ],
                "target": "no"
            },
            {
                "category": "Moderate",
                "effort": "5sec Best Power",
                "power_unit": "W/kg",
                "power_value": 14.64,
                "range_position": 44,
                "range_power_value": [
                    13.44,
                    15.61
                ],
                "target": "no"
            }
        ],
        "status": 0
    }
}

```
Proper GUI is under development. Following image shows the rider property and profile view pages:

<p align="left">
  <img src="https://user-images.githubusercontent.com/22800635/31576907-91cc72c8-b10d-11e7-94b1-a64a6427809a.jpg" />
</p>
