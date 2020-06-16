*Davis Vantage Pro Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display*

This folder provides the hardware info for this project. The circuit board in the main page is an early version.  The current board will be available on OSH Park so you can just order boards if you want them as-is.  The main differences are some minor circuit fixes, a slight size adjustment (to fit in a case I have in mind for the station) and embedding the RTC and battery on the board.  The original PCB was ony intended to use plug in modules and make it a little more robust than protoboards.  From the software, which is pretty ugly, you can probabily tell I am not a software expert, but this board has a strange combo of thru-hole and SMT technologies that reflect mostly what was on hand or could get easily for this proto. is not making the hardware hall of fame either, but it works.   

# Schematic

The schematic is in KiCAD format, here it is as a .JPEG if you don't have that software. You will notice a lot of hardware features on the board are not in use in the VP3 console receiver project.  If you order the boards from OSH Parkn  you get 3 boards so one can be a console, one can be a logger, and the third can be an APRS packet generator/controller.  ISS does not care how many receivers are listening!  

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/Schematic.png)

The circuit board is shown assembled in these 3D renderings.  The circuit board will accomodate 2 sizes of 320x240 displays. The LiPo battery connector is on this side as well as it is sandwiched in between the display and main PCB.  There are 3 tactile switches:
**"+"  "-"  "GO!"**
Used to set the clock and other parameters. You may want to use the long plunger types (13mm - 15mm)  should reach thru a front or rear panel in this configuration especially if you are putting it in some sort of case. They can be mounted on either side of the board as well. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_TOPSIDE.jpg)

The back side is where the Moteino and other modules plug in. The power connectors are on the left side.  I used a mini-USB connector for just power.  The Pin out for the USB_Power_Only is setup to match the SPARKFUN Breakout board 
[BOB-09966](https://www.sparkfun.com/products/9966) enables a power plug to be moved depending on the case requirements. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_SOLDERSIDE.jpg)

# Circuit Description

The  [Parts Llist](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1.html) is generated from the schematics but not all parts are installed depending of software support and features. You may want to read through these circuit descriptions before getting parts. I also did not provide much specific supplier information yet, except for the few noted, the others are fairly common parts you can order from [Digikey](http://digikey.com) or [Mouser](http://mouser.com) or other simular suppliers. I may supply a complete parts list with suppliers used on OSH Park that are compatible with the version of board. 

* **Arduino.** The brains of this project is the **Low Power Lab** [Moteino](https://lowpowerlab.com/shop/product/99)  Remember when ordering that you must add the RFM69CW 868/916MHz RF Module option or you won't be receiving any data!  You can also get the RFM69HCW but that version has more transmit power that you really don't need for this project since we never transmit anything. Also, you can add the headers and possibly the memory chip but can use the on-chip non-volitile memory in the software. It come with a simple wire antenna that actully works OK. There is also a small $2.00 [915 MHz Helical Antenna](https://lowpowerlab.com/shop/product/160?search=antenna) you may consider ordering as well. Speaking of antennas, I went full up with a real ISM band rubber ducky antenna, that works fantasctic! But when is a good thing *too good?*  When you recieve a neighbor's ISS, *from blocks away,* which seems not a big issue until you recive a rain count from it...it causes an erronious rain indication. For signal, the Motieno receiver decodes comfortably down to about -90dBm by my observations. 

* **Displays.** The part that makes this a console replacement is the TFT color LCD display. I used the ones that feature the ILI9341 chip in 240x320 QVGA resolution.  It turns out they that come in two sizes that work on the same software (see image below).  These are very common on e-bay and Amazon if you match the pinouts it should plug into the board just fine.  In the final version I intend to use the **Adafruit** versions for supply chain longevity i don't think the China clones will have. If you use the ones I found then thes will plug into the PCB directly.  You can jumper in others but if you want to use my software without modificaiton you need ILI9341 and 240x320 to be compatible. The two boards  used are 2.8" TFT SPI 240x320 v1.1 TJCTM24028-SPI and the smaller 2.2" CR2013-M12420 (the 2/2" is shown in pics).  Backlight is provided by white LEDs in the display. Reistor R4 sets the current to control the max brightness.  A PWM dimmer comprised of Q1 (NPN Transistor) R14 base resistor (10K) controled by one of he PWM pins (D3).  Note: R20 (100k) provides a pull up to keep the transistor turned on, even if D3 is not active in hi Z (input) state. The value from the AMBIENT Sensor can be use to dim the backlight. This sensor is described in the SENSORS section.  In a dark room, at full brightness, the LED puts out a lot of light!  The other reason we need to be able to dim it is for power savings on battery power, LEDs take a lot of current. If you want the display backlight on, set the brightness with R4, solder short the jumper J1, (see: JUMPERS) and DNI Q1, R14, and R20. Note: I did not see any noticable degredation in the RF perfomace while the PWM was running.  

![VP2_TFT Displays](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/Hardware/Displays.jpg)

           [Two compatible TFT display boards.]

* **SD Card.** The other feature of these TFT Displays is both have SPI controlled SD card sockets. I intended to use these as a data logging feature, but the current sofware does not support it. Also, in reading complaints and warnings about using these display SD cards I suspect there are SPI circuit issues so I added two buffer chips to try to eliminate these issues. The two 74AHC1G125 single-package gates U1 and U3 to only allow SPI traffic when the cards are specifically selected via the chip selet pin. This hardware will hopefully keep the SD cards from getting corrupted. To bypass these chips if it turns out we don't need to install the buffer(s), JP1 and JP2 will povide a non-switched path by soldering them closed with a blob of solder. LED D5 "ACTY" and R19 can be added to monitor the SD card activity. At this time the hardware and the logging feature have not been tested.

* **RTC.** The original prototype used a RTC on a board. This is easy to breadboard with but takes a lot of board space and height. I thought it would be OK, considering the Motieno is on a socket too, but decided to try an embedded approach in this version using a compact **SO-8**  *-z*  version of the **DS3231Z chip**.  Time is backed up by a coin cell (BT1).  See Batteries section. 

* **Options.**  Various *"solder blob"* configuraton jumpers are on the board to bypass or enable some features.  Pin D2 is selectabe between one of two features, shown below I don't think both will be usable at the same time so it is an either/or selecton for it. 

Jumper | Label | Function
------------ | ------------ | -------------
JP1| NO PWM | Disables Display dimming, Bypass Q1
JP2| NO SO BUFF | Short for SD Card MISO Bypass U1
JP3| NO SI BUFF | Short for SD Card MOSI Bypass U3
JP4| xxx | Not Used
JP5| IRQ | Enable IRQ for RTC on Pin D2 (not used) *OR*
JP6| CD | Enable SD Card insert Detect on pin D2 (TBD)


* **Sensors.**  Several on board sensors and conectors for sensors are provided.  
  * **Voltage sensor.** Consists of two high-value resistors (100k) R10 and R11 Take the input voltage of the battery and divide it in half. Capacitor C2 can be used for smoothing or noise reduction if needed, this signal is fed into VBATT (Analog Pin A7).  The voltage is scaled and is currently only used as a display of the battery voltage as a charge indication. 
  * **Ambient Sensor.**  An analog voltage perportional to the light is provide by a voltage divider formed by R16 a **LDR** and scaled by R16 (100k). A capacitor (C10) is provided to smooth the voltage input. The sensor used was harvested from a broken lawn solar light. 
  * **Indoor Humidity and Tempature Sensor.**  J7 provides a pin compatible connector for this sensor. It has a unique interface provided into pin D2 with a 4.7K pull up (R21)  These integrated temp/humidity sensors are pretty common on Amazon and other suppliers.  This was only used in early code versions before i relized there would not be enough code storage space on the Moteuino board. 
  * **Barometric Sensor.** J8 is an i2C connector arranged with voltage and ground pins to match an  I2C mems barometer breakout board, alas, i did not have code space to keep it.  Pins A5 and A4 provide the i2C SCL and SDA signals. Any other I2C board can work with these pins as well. 

* **LEDs.** Several LEDs indicators are also sprinkled around the board, mostly for debugging, and what fun is having no blinking lights?

LED| Label | Function
------------ | ------------ | -------------
D1| CHARGE | MCP73831 STAT Pin "Charging"
D3| Red |  Controlled by Pin A3, flashes for bad stuff
D4| Green |Controlled by Pin D9 (same as Motieno LED) good stuff
D5| ACTY | Controlled by Pin D4 to show some status? Maybe as SD card issues?
D6| Yellow | (DNI) TP6 connect if needed for debug, visile from front panel 
D7| SD_CS | on if SD Card chip is selected (SPI activity)


* **Back up Batteries.**  
Two battery circuits are provided for back up purposes. 

  * **Main Power** The provided battery charger circuit is intended to keep the main battery charged and take over in the event of a power failure or if you just want to move the receiver around.  It keeps the Max/Mins and rain totals in memory as well. The charge controller is a (U2) MCP73831.   An and old cell phone battery was used with a soldered JST type battery pigtail from [Adafruit](https://www.digikey.com/product-detail/en/adafruit-industries-llc/1131/1528-1494-ND/5761282?utm_adgroup=Accessories&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&utm_content=Accessories&gclid=EAIaIQobChMIx6-Q28GF6gIVEQnnCh3sRQ0aEAQYASABEgJNKPD_BwE). It  but it fit nicely between the board and display and holds a charge long enough. I did not connect the other pad(s)on the battery, which is probabily a thermistor or battery ID pin, which is not needed in this circuit only "+" and "-". The battery connector BATT (J1) is a standard JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical common for batteries and is polarized. The charging current is set by R13.  For this application, a large (10K or larger) resistor should be used to just maintain the battery charge ad 100mA or even less, it was an old battery, may suck as a cell phone battery, but it is only intended to run for a few hours at most and is not a portable device *per se*, so a slow charge is fine. When the battery is charging LED (D1) is on and turns off when a full charge is reached. Input power (5V) comes from J2 or J3 and the battery takes over when the supply is unplugged or interrupted. The voltage sensor circuit can be used to monitor the voltage on the batery to let you know when it it time to plug in!  Also two PTC fuses are provided (F1, F2). F1 is a .5A PTC resettable fuse that protects the circuitry when powered by an external power supply from (J2 or J3). F2 is in-line with the battery from  (J1)  in case there is too much current from the battery. F1 is the most importaint as the console is intended to be plugged in most of the time.  F2 is only if there is a battery issue, which is an unlikely possibility, but if the device is dropped or worse yet stepped on which can cause a short and these little batteries contain a lot of energy. If you do accidentally trip one of these they reset themselves when they cool down. 
  * **RTC Backup**  BT1 is the RTC back up. I  reduced the battery from the standard **CR2023** 3V Li Coin cell to a smaller **CR1220**.  I am not sure how long this cell will last, but that is only really needed if the main power *and* the battery back up fails as well.  The holder is soldered to the circuit board.  
