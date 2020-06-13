
# VP3-Weather-Receiver Hardware
*Davis Vantage Pro Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display*

This folder provides the hardware info for this project. The circuit board in the main page is an early version.  The current board will be available on OSHPark so you can just order boards if you want them as-is.  The main differences are some minor circuit fixes, a slight size adjustment (to fit in a case i have in mind for the station) and embedding the RTC and battery on th board.  The original PCB was ony intended to use plug in modules and make it a little more robust than protoboards.  It is a strange combo of thru-hole and SMT technologies that reflect mostly what i had on hand or could get for this proto. 

# Schematic

The schematic is in KiCAD format, here is it is if you don't have that software. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/Schematic.png)

The circuit board is shown assembled in these 3D renderings.  The circuit board will accomodate 2 sizes of 320x240 displays. The LiPo battery connector is on this side as well as it is sandwiched in between the display and main PCB.  There are 3 tactile switches:
## "+"  "-"  "GO!" ##
labels to set the clock and other parameters. You may want to use the long plunger types (13mm should reach thru a front panel in this configuration) if you are putting in some sort of case. They can be mounted on either side of the board as well. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_TOPSIDE.jpg)

The back side is where the Moteino and other modules plug in. The power connectors are on the left side.  I used a mini-USB connector for just power.  The Pin out for the USB_Power_Only is setup to match the SPARKFUN Breakout board 
[BOB-09966](https://www.sparkfun.com/products/9966) enables a power plug to be moved depending on the case requirements. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_SOLDERSIDE.jpg)

# Parts 

The parts list is here: [BOM](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1.html) but not all parts are installed depending of software support and features. 

* Arduino. The brains of this project is the [Moteino](https://lowpowerlab.com/shop/product/99)  Remember when ordering that you must add the RFM69CW 868/916MHz RF Module option or you won't be receiving any data!  You can also get the RFM69HCW but that version has more transmit power that you really don't need. Also, you can add the headers and possibly the memory chip but i really diddn't use that in the software. 
* Displays.The part that makes this a consol replacement is the TFT color LCD display. I used the ILI9341 240x320 that come in two sizes.  These are very common on e-bay ane Amazon.  If you use the ones i found then thes will plug into the PCB directly.  You can jumper in others but if you want to use my software without modificaiton you need ILI9341 and 240x320 to be compatible. The two boards  used are 2.8" TFT SPI 240x320 v1.1 TJCTM24028-SPI and the smaller 2.2" CR2013-M12420 ( shown in pics) 

The other feature of both boards is they have SPI controlled SD cards.  I intended to use these as a data loging feature, but the sofware does not support.  Also, in reading complaints about these display cards I added two buffer chips to try to eliminate these issues. The two xxxx gates U? and U? only allow SPI traffic when the cards are specifically selected via the chip selet pin. To bypass tehse chips if we don't need, JP? and JP? will povide a non switched path by soldering them. This hardware will hopefully keep the cards from getting corrupted. LED D? "ACTY" and R? can be added to monitor the SD card activity.  At this time the hardware and the logging feature have not been tested. 


* RTC.
* Jumpers.

Jumper | Label | Function
------------ | ------------ | -------------
JP1| NO PWM | Disables Display dimming, Bypass Q1
JP2| NO SO BUFF | Short for SD Card MISO Bypass U1
JP3| NO SI BUFF | Short for SD Card MOSI Bypass U3
JP4| xxx | Not Used
JP5| IRQ | Enable IRQ for RTC on Pin D2 (not used)
JP6| CD | Enable SD Card insert Detect on pin D2 (TBD)


* Sensors.
* LEDs.


