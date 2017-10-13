# Power Profiler for Cycling

Multi platform (Linux, Windows or Android) app to determine power profile for road cyclists that use power meter for riding and training. Uses cycling power profile chart developed by Hunter Allan & Dr. Andrew Coggan for comparison and classification.    

Depends on Qt cross-platform application development toolkit.

Below image of the power profile chart utilized in profile calculations:

<p align="left">
  <img src="https://user-images.githubusercontent.com/22800635/31544246-846eff42-b022-11e7-826b-8b9e1a825474.gif" width="720"/>
</p>


Below is CLI test program output in JSON format:

>./PowerProfiler -g m -w 64 -ftp 257 -vo2 304 -ana 539 -nmu 937
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
                "power_id": "60min Best Power(FTP)",
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
                "power_id": "5min Best Power",
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
                "power_id": "1min Best Power",
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
                "power_id": "5sec Best Power",
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
