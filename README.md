# Arduino code 2020-21

## Overview

Low-level software for the Newcastle University ROV 2021. Takes key:value pairs from [Raspberry Pi](https://github.com/ncl-ROVers/raspberry-pi) in MsgPack format and acts on them accordingly.

## Installation

### Software Dependencies

You need to install the following libraries in your IDE:

- ArduinoJson
- Servo

### Identification

Arduino A and Arduino B have different pin assignments as shown below. By default, the code assumes it is running on Arduino A. To switch it to Arduino B, connect pin 17 to GND.

### Device keys and pin allocation

Thrusters are given an ID which describes their position on the ROV. Motors are named in a similar fashion.

| Device Name                                  | Key   | Attached to  | Pin | Location    |
|----------------------------------------------|-------|--------------|-----|-------------|
| Top Forward Port Thruster (front left)       | T_VFP | Arduino A    |   2 | Enclosure 1 |
| Top Forward Starboard Thruster (front right) | T_VFS | Arduino A    |   3 | Enclosure 1 |
| Top Aft Port Thruster (back left)            | T_VAP | Arduino A    |   4 | Enclosure 1 |
| Top Aft Starboard Thruster (back right)      | T_VAS | Arduino A    |   5 | Enclosure 1 |
| Forward Port Thruster (front left)           | T_HFP | Arduino B    |   2 | Enclosure 2 |
| Forward Starboard Thruster (front right)     | T_HFS | Arduino B    |   3 | Enclosure 2 |
| Aft Port Thruster (back left)                | T_HAP | Arduino B    |   4 | Enclosure 2 |
| Aft Starboard Thruster (back right)          | T_HAS | Arduino B    |   5 | Enclosure 2 |
| Arm Gripper Motor                            | M_G   | Arduino B    |   6 | Enclosure 2 |
| Micro ROV return cord                        | M_C   | Arduino B    |   7 | Enclosure 2 |
| Micro ROV Thruster                           | T_M   | Arduino B    |   8 | Enclosure 2 |
| Arduino A                                    | A_A   | Raspberry Pi |     | Enclosure 1 |
| Arduino B                                    | A_B   | Raspberry Pi |     | Enclosure 2 |

## Arduino A Behaviour

### Incoming data from Pi

| Key   | Min  | Max  |
|-------|------|------|
| T_VFP | 1100 | 1900 |
| T_VFS | 1100 | 1900 |
| T_VAP | 1100 | 1900 |
| T_VAS | 1100 | 1900 |

### Outgoing data to Pi

| Key     |  Min |  Max |
|---------|------|------|
| ID      | A_A  | A_A  |
| S_A     | -    | -    |

## Arduino B Behaviour

### Incoming data from Pi

| Key   | Min  | Max  |
|-------|------|------|
| T_HFP | 1100 | 1900 |
| T_HFS | 1100 | 1900 |
| T_HAP | 1100 | 1900 |
| T_HAS | 1100 | 1900 |
| M_G   | 1200 | 1800 |
| M_C   | 1650 | 1350 |
| T_M   | 1100 | 1900 |

### Outgoing data to Pi

| Key     |  Min |  Max |
|---------|------|------|
| ID      | A_B  | A_B  |
| S_B     | -    | -    |

## Status Codes

These will be returned with the S_A or S_B keys.

| Status   Code | Description                                    |
|---------------|------------------------------------------------|
| 0             | No error                                       |
| 1             | Outputs halted                                 |
| 2             | Left   limit hit. Motor stopped                |
| 3             | Right   limit hit. Motor stopped               |
| 4             | Arduino booting                                |
| 5             | Heartbeat                                      |
| -1            | Received value out of range                    |
| -6            | This is not an Output Arduino                  |
| -7            | This is not an Input Arduino                   |
| -8            | Invalid Output device key                      |
| -9            | Invalid Input device key                       |
| -10           | Can't stop outputs on an Input Arduino         |
| -11           | Incoming data parsing failed                   |
| -12           | Arduino ID is not set up                       |
| -13           | No messages received, outputs halted           |
| -23           | Index not valid for setting a sensor parameter |
