# esp8266-nfc-reader
## Background
This was originally written with inspiration from https://shawnrk.github.io/songblocks/ but without the overhead of a pi.  I've since updated this code to run with the homie 2.0 spec homie-esp8266 code and published here.

## Compiling
You need the Arduino development environment for this. Plus the PM532 lib from https://github.com/Seeed-Studio/PN532. Apparently the Adafruit flavor of the PM532 lib does not support i2c on esp8266 so we have to jump through a couple hoops to make this go.

## Tested and working hardware
* NodeMCU Board https://amzn.to/2SZWLJ6
* NXP PM532 Breakout https://amzn.to/2VXHtGX
* itead NXP PM532 Breakout https://amzn.to/2sx4H9b

## Todo
* Thinking of adding some feedback mechanism such as haptic, neopixel or led options.
* <strike>Need to publish the glue between this code and sonos.</strike>
* come up with some example automations for Home Asssistant for fun.
* photo/video of the final build (wood enclosure with wood sound blocks).


## MQTT Messages after touching and removing a translink.ca Compass card.
```

homie/legacy-songblock/rfid/uid 04905042763f80
homie/legacy-songblock/rfid/present true
homie/legacy-songblock/rfid/uid (null)
homie/legacy-songblock/rfid/present false
homie/legacy-songblock/rfid/previous_uid 04905042763f80

```

## Sonos Controller 
Assign a song to each tag/card/whatever.
https://github.com/jayaras/sonos-agent

## Home Assistant Exmaple
Binary sensor from a card being present or not.
```yaml
binary_sensor:
  - platform: mqtt
    state_topic: "homie/rfid-reader/present"
    payload_on: "true"
    payload_off: "true"
    availability_topic: "homie/rfid-reader/$online"
```
