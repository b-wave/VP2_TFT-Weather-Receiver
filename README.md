# VP3-Weather-Reciever
Davis Vantage Pro Weather Station Reciever using a Moteieino with RFM69 and Color TFT Display.
This is mainly a demo of the dekay/DavisRFM69 library (et.al.) using a TFT LCDscreen 
It was intended as a Davis VP2 Weather console replacement. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/20200610_172159.jpg)
Display in action - Front view


It displays only  the data received from the Davis Vantage Vu ISS.
Curently, this version does not  add the internal data to make a complete 
TFT console replacement for display of all weather parameters.
## CREDITS:
This is mostly a derivitive work from several authors i give credit
to the original works in line as i use them, without their work
this would not be possible.  The original work here includes the
additions for using TFT LCD displays. But I credit to getting the 
TFT to work with the RFM69 was because of this excellent article:
 https://www.pjrc.com/better-spi-bus-design-in-3-steps/  Thanks Paul! 

This project was intended to be a low cost replacement for a broken 
Davis Vu Weather staion that the ISS still works (with a few issues) 
but that is another story. Hopefully someone can find this useful.

https://github.com/kobuki/VPTools
VPTools is a Davis(TM) weather station compatible transceiver library. 
It is a work in progress. It can receive from multiple RF transmitters (ISS, ATK, etc.) 
It tries to serve as a basis for similar hobby projects. 
Example sketches provide simple, parseable and RAW packet output among others.


https://github.com/dekay/DavisRFM69  By DeKay
Licence: Creative Commons Attribribution Share-Alike License http://creativecommons.org/licenses/by-sa/3.0/
This library is a modified version of the LowPowerLab's RFM69 library that enables reception of weather data 
from a Davis Instruments Integrated Sensor Suite (ISS) weather station.

https://github.com/LowPowerLab/RFM69  By Felix Rusu, LowPowerLab.com 
RFM69 library for RFM69W, RFM69HW, RFM69CW, RFM69HCW (semtech SX1231, SX1231H) 
Licence:GPL 3.0, please see the License.txt file for details. 
Be sure to include the same license with any fork or redistribution of this library.

ADAFRUIT Libraries and awesome info:
Written by Limor Fried/Ladyada for Adafruit Industries. MIT license, 
Licence : MIT https://github.com/adafruit/RTClib/blob/master/LICENSE
https://github.com/adafruit

https://github.com/adafruit/RTClib
This is a fork of JeeLab's fantastic real time clock library for Arduino.

These libraries are for the Adafruit ILI9341 display products:  
https://github.com/adafruit/Adafruit_ILI9341
https://github.com/adafruit/Adafruit-GFX-Library

