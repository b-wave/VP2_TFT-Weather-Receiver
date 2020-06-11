# VP3-Weather-Receiver
*Davis Vantage Pro Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display.(1)*

This project is mainly a demo of the dekay/DavisRFM69 library (et.al.) @dekay using a TFT LCD screen 
it was intended to be a low-cost replacement for a broken Davis Vu Weather station that the ISS still works (with a few issues) 
*...but that is another story.* Hopefully *someone* will find this useful. I had a fun time developing it and
you can still see the saga of revisions in the source code listing as it evolved over several months. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/20200610_172159.jpg)
Display in action - Front view

Because i used a low cost Motieno, https://lowpowerlab.com/ it ran out of memory so this version
can display mainly only the data received from the Davis Vantage Vu ISS.
With some derived info like,  max and mins, rain, and cool TFT wind compass displays. 

Curently, this project version does not  add the internal data to make a complete 
TFT console replacement for display of all weather parameters. I had to remove
indoor temp, humidity and barometric pressure to make a usable replacement. 

I designed a circuit board and added some usefull features such as push button setting
a LiPo battery backup and charger, and a real time clock.  Some features will need to move to
the: *next version that uses a Teensey 3.2 board will do all this and more!*

## CREDITS:
This is a derivitive work from several authors i give credit
to the original works in line as i use them, without their work
this would not be possible.  The original work here includes the
additions for using TFT LCD displays. But I credit to getting the 
TFT to work with the RFM69 was because of this excellent article:
 https://www.pjrc.com/better-spi-bus-design-in-3-steps/  
 Thanks Paul! @PaulStoffregen


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

## Notes:
1. The VP3 refernce to the never produced color LCD console from Davis Instrumnents https://www.davisinstruments.com/weather-monitoring/
that all of us fans of thier products wish for. 
