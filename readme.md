# ESP8266 Demo Board - HAL

[![Build Status](https://travis-ci.org/bastlirna/esp8266-board-hal.svg?branch=master)](https://travis-ci.org/bastlirna/esp8266-board-hal)

## Description

Base [PlatformIO](https://platformio.org) library for ESP8266 Demo Board (github repo at [/bastlirna/esp8266-board](https://github.com/bastlirna/esp8266-board)). 

### Main Goal
Main goal is access a board periphery as simple as is possible. Library adds new layer between HW and user application, so aplication can be simly tested.

### Key features

-	Access to buttons (with debounce support)
-	Read temperature and humidity from DHT11 (or DHT22 is configured)
-	Setup RGB led provide simply access to it.

### TODO
-	Implement both board versions (actualy is implmemented only Lite version)
-	Implement beeper for tone generation

### Dependency
Library uses these libraries:
-	DHT sensor library@1.3.4
-	Adafruit Unified Sensor@1.0.3
-	DebouncedInput@1.0.13