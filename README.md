# esp8266-nfc-reader
## Background
This was originally written with inspiration from https://shawnrk.github.io/songblocks/ but without the overhead of a pi.  I've since updated this code to run with the homie 2.0 spec homie-esp8266 code and published here.

## Compiling
You need the Arduino development environment for this. Plus the PM532 lib from https://github.com/Seeed-Studio/PN532. Apparently the Adafruit flavor of the PM532 lib does not support i2c on esp8266 so we have to jump through a couple hoops to make this go.

## Tested and working hardware
* NodeMCU Board

## Todo
* Thinking of adding some feedback mechanism such as haptic, neopixel or led options.
* Need to publish the glue between this code and sonos.
* come up with some example automations for Home Asssistant for fun.
* photo/video of the final build (wood enclosure with wood sound blocks).
