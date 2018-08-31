# ESP32-BME280_I2C-Blynk

## About

This example Arduino based code implements procedure of reading data - Temperature,Humidity and Atmospheric Pressure from 4 pins based BME280 module (I2C) and send it to Blynk app.Used Blynk Virtual Pins are V10,V11 and V12 respectively for Pressure,Temperature and Humidity.
It needs to be installed Blynk library in Arduino program.

Driver(ESP32_BME280_I2C) for I2C module is located at directory "/driver".
SDA pin is connected to GPIO26 and SCL pin - to GPIO27.

Image of the module is shown at /IMG/module.jpg

