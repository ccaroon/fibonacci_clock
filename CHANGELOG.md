# CHANGELOG

## 2024-11-17
* Reset time b/c of DST ending
* Added `upload_port` & `monitor_port` to `platformio.ini`
  - `pio` was defaulting to `ttyUSB0`, but that's a USB Drive
  - Uno is now on `ttyUSB1`

## 2022-10-16
* Added some color mappings for a selection of different holidays
  - NewYear, VDay, BDay, StPatty, Indy, Halloween, Thanksgiving, Christmas

## 2022-04-10
* Defined a color set for each season (winter, spring, summer, fall)
* Added code to change the color set based on the season as determined by the current date.

## 2022-01-15
* Changed to "Winter" (cold) colors
* Show the time always; no effects

## 2021-12-20
* Added Effects
* Re-programmed to display the time every 15 minutes, otherwise it displays a
  rainbow color wheel.

## 2020-12-16
* Updated to work with latest PlatformIO
* Updated light color for Christmas
