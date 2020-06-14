*Davis Vantage Pro Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display*

This folder provides the hardware info for this project. The circuit board in the main page is an early version.  The current board will be available on OSHPark so you can just order boards if you want them as-is.  The main differences are some minor circuit fixes, a slight size adjustment (to fit in a case I have in mind for the station) and embedding the RTC and battery on the board.  The original PCB was ony intended to use plug in modules and make it a little more robust than protoboards.  From the software, which is pretty ugly, you can probabily tell I am not a software expert, but this board has a strange combo of thru-hole and SMT technologies that reflect mostly what was on hand or could get easily for this proto. is not making the hardware hall of fame either, but it works.   

# Schematic

The schematic is in KiCAD format, here is it is if you don't have that software. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/Schematic.png)

The circuit board is shown assembled in these 3D renderings.  The circuit board will accomodate 2 sizes of 320x240 displays. The LiPo battery connector is on this side as well as it is sandwiched in between the display and main PCB.  There are 3 tactile switches:
**"+"  "-"  "GO!"**
Used to set the clock and other parameters. You may want to use the long plunger types (13mm - 15mm)  should reach thru a front or rear panel in this configuration especially if you are putting it in some sort of case. They can be mounted on either side of the board as well. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_TOPSIDE.jpg)

The back side is where the Moteino and other modules plug in. The power connectors are on the left side.  I used a mini-USB connector for just power.  The Pin out for the USB_Power_Only is setup to match the SPARKFUN Breakout board 
[BOB-09966](https://www.sparkfun.com/products/9966) enables a power plug to be moved depending on the case requirements. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_SOLDERSIDE.jpg)

# Circuit Description

The parts list is here: [BOM](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1.html) but not all parts are installed depending of software support and features. 

* **Arduino.** The brains of this project is the **Low Power Lab** [Moteino](https://lowpowerlab.com/shop/product/99)  Remember when ordering that you must add the RFM69CW 868/916MHz RF Module option or you won't be receiving any data!  You can also get the RFM69HCW but that version has more transmit power that you really don't need for this project since we never transmit anything. Also, you can add the headers and possibly the memory chip but i really diddn't use that in the software. It come with a simple wire antenna that actully works OK. There is also a small heilical antenna you may consider ordering as well. Speaking of antennas, I went full up with a real ISM band rubber ducky antenna, that works fantasctic! But when is a good thing *too good?*  When you recieve a neighbor's ISS, *from blocks away,* which seems not a big issue until you recive a rain count from it...it causes an erronious rain indication. For signal, the Motieno receiver decodes comfortably down to about -90dBm by my observations. 

* **Displays.** The part that makes this a console replacement is the TFT color LCD display. I used the ones that feature the ILI9341 chip in 240x320 resolution.  It turns out they that come in two sizes that work on the same software.  These are very common on e-bay and Amazon.  In the final version I intend to use the **Adafruit** versions for supply chain longevity i don't think the China clones will have. If you use the ones I found then thes will plug into the PCB directly.  You can jumper in others but if you want to use my software without modificaiton you need ILI9341 and 240x320 to be compatible. The two boards  used are 2.8" TFT SPI 240x320 v1.1 TJCTM24028-SPI and the smaller 2.2" CR2013-M12420 ( shown in pics).  Backlight is provided by white LEDs in the display. Reistor R4 sets the current to control the max brightness.  A PWM dimmer comprised of Q1 (NPN Transistor) R14 base resistor (10K) controled by one of he PWM pins (D3).  Note; even if this feature is not active, R20 (100k) provides a pull up to keep the transistor turned on, even if D3 is not active in hi Z (input) state. The value from the AMBIENT Sensor can be use to dim the backlight. This sensor is described in the SENSORS section.  In a dark room, at full brightness, the LED puts out a lot of light!  The other reason we need to be able to dim it is for power savings on battery power, LEDs taka a lot of current. If you want the display backlight on, set the brightness with R4, solder short the jumper J1, ( see JUMPERS) and DNI Q1, R14, and R20. Note: I did not see any noticable degredation in the RF perfomace while the PWM was running.  

* **SD Card.** The other feature of these TFT Displays is both have SPI controlled SD card sockets. I intended to use these as a data logging feature, but the current sofware does not support it. Also, in reading complaints and warnings about using these display SD cards I suspect there are SPI circuit issues so I added two buffer chips to try to eliminate these issues. The two 74AHC1G125 single-package gates U1 and U3 to only allow SPI traffic when the cards are specifically selected via the chip selet pin. This hardware will hopefully keep the SD cards from getting corrupted. To bypass these chips if it turns out we don't need to install the buffer(s), JP1 and JP2 will povide a non-switched path by soldering them closed with a blob of solder. LED D5 "ACTY" and R19 can be added to monitor the SD card activity. At this time the hardware and the logging feature have not been tested.

* **RTC.** The original prototype used a RTC on a board. This is easy to breadboard with but takes a lot of board space and height. I thought it would be OK, considering the Motieno is on a socket too, but decided to try an embedded approach in this version using a compact **SO-8**  *-z*  version of the **DS3231Z chip**. I also reduced the battery from the standard CR2023 3V Li Coin cell to a smaller **CR1220**.  I am not sure how long this cell will last, but that is only really needed if the main power *and* the battery back up fails as well.  

* **Options.**  Various *"solder blob"* configuraton jumpers are on the board to bypass or enable some features.  Pin D2 is selectabe between one of two features, shown below I don't think both will be usable at the same time so it is an either/or selecton for it. 

Jumper | Label | Function
------------ | ------------ | -------------
JP1| NO PWM | Disables Display dimming, Bypass Q1
JP2| NO SO BUFF | Short for SD Card MISO Bypass U1
JP3| NO SI BUFF | Short for SD Card MOSI Bypass U3
JP4| xxx | Not Used
JP5| IRQ | Enable IRQ for RTC on Pin D2 (not used) *OR*
JP6| CD | Enable SD Card insert Detect on pin D2 (TBD)


* Sensors.
* LEDs.


