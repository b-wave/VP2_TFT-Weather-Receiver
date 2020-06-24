*Davis Vantage Vu Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display*

This folder provides the hardware info for this project. The circuit board in the main page picture is an early version.  The current board will be available on OSH Park so you can just order boards if you want them as-is.  The main differences are some minor circuit fixes, a slight size adjustment (to fit in a case I have in mind for the station) and embedding the RTC and battery on the board.  The original PCB was ony intended to use plug in modules and make it a little more robust than protoboards.  From the software, which is pretty ugly, you can probabily tell I am not a software expert, but this board has a strange combo of thru-hole and SMT technologies that reflect mostly what was on hand or could get easily for this proto. is not making the hardware hall of fame either, but it works.   

# Schematic

The schematic is in KiCAD format, here it is as a .JPEG if you don't have that software. You will notice a lot of hardware features on the board are not in use in the VP3 console receiver project.  If you order the boards from [OSH Park](https://oshpark.com/)  you get 3 boards so one can programmed to be a console, one can be a logger, and the third can be an APRS packet generator/controller.  ISS does not care how many receivers are listening!  *See Note (2)*

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/Schematic.png)

The circuit board is shown assembled in these 3D renderings.  The circuit board will accomodate 2 sizes of 320x240 displays. The 3D renderings also show the assembly with the smaller 2.2" display.  You can see the outline of the optional 2.8" display and that i Put the LED indicators outside its outline. The LiPo battery connector is on this side as well as it is sandwiched in between the display and main PCB.  There are 3 tactile switches:
**"+"  "-"  "GO!"**
Used to set the clock and other parameters. You may want to use the long plunger types (13mm - 15mm)  should reach thru a front or rear panel in this configuration especially if you are putting it in some sort of case. They can be mounted on either side of the board as well.  With the 2.8" display the swithes will need to be relocated as they are blocked from the front by that display. See Note (1)

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_TOPSIDE.jpg)

The back side is where the Moteino and other modules plug in. The power connectors are on the left side.  I used a mini-USB connector for just power.  The Pin out for the USB_Power_Only is setup to match the SPARKFUN Breakout board 
[BOB-09966](https://www.sparkfun.com/products/9966) enables a power plug to be moved depending on the case requirements. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_SOLDERSIDE.jpg)

# Circuit Description

The  [Parts List](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1.xlsx) is generated from the schematics, the format is wierd.  Not all parts are installed depending of software support and features. You may want to read through these circuit descriptions before getting parts. I also did not provide much specific supplier information yet, except for the few noted, the others are fairly common parts you can order from [Digikey](https://digikey.com) or [Mouser](https://mouser.com) or other simular suppliers. I may supply a complete parts list with suppliers used on OSH Park that are compatible with the version of board. 

* **Arduino.** The brains of this project is the **Low Power Lab** [Moteino](https://lowpowerlab.com/shop/product/99)  Remember when ordering that you must add the RFM69CW 868/916MHz RF Module option or you won't be receiving any data!  You can also get the RFM69HCW but that version has more transmit power that you really don't need for this project since we never transmit anything. Also, you can add the headers and possibly the memory chip but can use the on-chip non-volitile memory in the software. It come with a simple wire antenna that actully works OK. There is also a small $2.00 [915 MHz Helical Antenna](https://lowpowerlab.com/shop/product/160?search=antenna) you may consider ordering as well. Speaking of antennas, I went full up with a real ISM band rubber ducky antenna, that works fantasctic! But when is a good thing *too good?*  When you receive a neighbor's ISS, *from blocks away,* which seems not a big issue until you recive a rain count from it...it causes an erronious rain indication. For signal, the Motieno receiver decodes comfortably down to about -90dBm by my observations. If all else fails...there is a reset button (S4) that will restart the software.  This actully comes in more handy as the battery is always connected and you can't easily power cycle the unit. 

* **TFT Display.** The part that makes this a [Davis Vantage Vu](https://www.davisinstruments.com/solution/vantage-vue/) console is the TFT color LCD display. I used the ones that feature the ILI9341 chip in 240x320 QVGA resolution.  It turns out they that come in two sizes that work on the same software (see image below).  These are very common on e-bay and Amazon if you match the pinouts it should plug into the board just fine.  In the final version I intend to use the **Adafruit** versions for supply chain longevity i don't think the China clones will have. If you use the ones I found then thes will plug into the PCB directly.  You can jumper in others but if you want to use my software without modificaiton you need ILI9341 and 240x320 to be compatible. The two boards  used are 2.8" TFT SPI 240x320 v1.1 TJCTM24028-SPI and the smaller 2.2" CR2013-M12420 (the 2.2" version is shown in the pics).  Backlight is provided by white LEDs in the display. Reistor R4 sets the current to control the max brightness.  A PWM dimmer comprised of Q1 (NPN Transistor) R14 base resistor (10K) controled by one of he PWM pins (D3).  Note: R20 (100k) provides a pull up to keep the transistor turned on, even if D3 is not active in hi Z (input) state. The value from the AMBIENT Sensor can be used to dim the backlight. This sensor is described in the SENSORS section.  In a dark room, at full brightness, the LED puts out a lot of light!  The other reason we need to be able to dim it is for power savings on battery power, LEDs take a lot of current. If you want the display backlight on, set the brightness with R4, solder short the jumper J1, (see: JUMPERS) and DNI Q1, R14, and R20. Note: I did not see any noticable degredation in the RF perfomace while the PWM was running.  

![VP2_TFT Displays](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/Displays.jpg)

[Two compatible TFT display boards]

* **SD Card.** The other feature of these TFT Displays is both have SPI controlled SD card sockets. I intended to use these as a data logging feature, but the current software does not support it. Also, in reading complaints and warnings about using these display SD cards I suspect there are SPI circuit issues so I added two buffer chips to try to eliminate these issues. The two 74AHC1G125 single-package gates U1 and U3 to only allow SPI traffic when the cards are specifically selected via the chip selet pin. This hardware will hopefully keep the SD cards from getting corrupted. To bypass these chips if it turns out we don't need to install the buffer(s), JP1 and JP2 will povide a non-switched path by soldering them closed with a blob of solder. LED D5 "ACTY" and R19 can be added to monitor the SD card activity. At this time the hardware and the logging feature have not been tested.

* **RTC.** The original prototype used a RTC on a board. This is easy to breadboard with but takes a lot of board space and height. I thought it would be OK, considering the Motieno is on a socket too, but decided to try an embedded approach in this version using a compact **SO-8**  *-z*  version of the **DS3231Z chip**.  Time is backed up by a coin cell (BT1).  See Batteries section.
* **Sensors.**  Several on board sensors and conectors for sensors are provided.  
  * **Voltage sensor.** Consists of two high-value resistors (100k) R10 and R11 Take the input voltage of the battery and divide it in half. Capacitor C2 can be used for smoothing or noise reduction if needed, this signal is fed into VBATT (Analog Pin A7).  The voltage is scaled and is currently only used as a display of the battery voltage as a charge indication. 
  * **Ambient Sensor.**  An analog voltage proportional to the ambient light is provide by a voltage divider formed by R16 a **LDR** and scaled by R16 (100k). A capacitor (C10) is provided to smooth the voltage input. The sensor used was harvested from a broken lawn solar light. 
  * **Indoor Humidity and Tempature Sensor.**  J7 provides a pin compatible connector for this sensor. It has a unique interface provided into pin D2 with a 4.7K pull up (R21)  These integrated temp/humidity sensors are pretty common on Amazon and other suppliers.  This was only used in early code versions before i relized there would not be enough code storage space on the Moteuino board. 
  * **Barometric Sensor.** J8 is an i2C connector arranged with voltage and ground pins to match an  I2C mems barometer breakout board, alas, i did not have code space to keep it.  Pins A5 and A4 provide the i2C SCL and SDA signals. Any other I2C board can work with these pins as well. 
* **LEDs.** Several LEDs indicators are also sprinkled around the board, mostly for debugging, and what fun is having no blinking lights?

LED| Label | Function
------------ | ------------ | -------------
D1| CHARGE | MCP73831 STAT Pin "Charging"
D3| Red |  Controlled by Pin A3, flashes for bad stuff
D4| Green |Controlled by Pin D9 (same as Motieno LED) good stuff
D5| ACTY | Controlled by Pin D4 to show some status? Maybe as SD card issues?
D6| Yellow | (DNI) TP6 connect if needed for debug, visible from front panel 
D7| SD_CS | on if SD Card chip is selected (SPI activity)


* **Back up Batteries.**  
Two battery circuits are provided for back up purposes. 

  * **Main Power** The provided battery charger circuit is intended to keep the main battery charged and take over in the event of a power failure or if you just want to move the receiver around.  It keeps the Max/Mins and rain totals in memory as well. The charge controller is a (U2) MCP73831.   An and old cell phone battery was used with a soldered JST type battery pigtail from [Adafruit](https://www.digikey.com/product-detail/en/adafruit-industries-llc/1131/1528-1494-ND/5761282?utm_adgroup=Accessories&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&utm_content=Accessories&gclid=EAIaIQobChMIx6-Q28GF6gIVEQnnCh3sRQ0aEAQYASABEgJNKPD_BwE). It  but it fit nicely between the board and display and holds a charge long enough. I did not connect the other pad(s)on the battery, which is probabily a thermistor or battery ID pin, which is not needed in this circuit only "+" and "-". The battery connector BATT (J1) is a standard JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical common for batteries and is polarized. 
  
[Battery figure here?]

The charging current is set by R13.  For this application, a large (10K or larger) resistor should be used to just maintain the battery charge at 100mA or even less, I used an old battery, that may now suck as a cell phone battery, but it is only intended to run for *a few hours at most* and is not intended to be a portable device *per se*, so a slow charge is fine. When the battery is charging LED (D1) is on and turns off when a full charge is reached. Input power (5V) comes from J2 or J3 and the battery takes over when the supply is unplugged or interrupted. An MBRA140 SHOTTKY Diode (D2) diode switches depending on the voltage difference of Vin and Vbatt. The voltage sensor (described in the Sensors Section) circuit can be used to monitor the voltage on the batery to let you know when it it time to plug in, but we only use that for display.  

Also, two PTC fuses are provided (F1, F2) to protect the circuits. F1 is a .5A PTC resettable fuse that protects the circuitry when powered by an external power supply from (J2 or J3). F2 is in-line with the battery from  (J1)  in case there is too much current from the battery. F1 is the most importaint as the console is intended to be plugged in most of the time.  F2 is only if there is a battery issue, which is an unlikely possibility, but if the device is dropped or worse yet stepped on which can cause a short and these little batteries contain a lot of energy. If you do accidentally trip one of these they heat up and essentally open then reset themselves when they cool down. 
  * **RTC Backup**  BT1 is the RTC back up. I  reduced the battery from the standard **CR2023** 3V Li Coin cell to a smaller **CR1220**.  I am not sure how long this cell will last, but that is only really needed if the main power *and* the battery back up fails as well.  The holder is soldered to the circuit board.
  
* **Connectors and Misc.**  Here are descriptions of the various connectors, jumpers, and test points on the board. Various *"solder blob"* configuraton jumpers (JP) are on the board to bypass or enable some features.  Pin D2 is selectabe between one of two features, shown below I don't think both will be usable at the same time so it is an either/or selecton for it

ITEM | Label | Type |Function
----- | -------- | ------------ | -------------
J1| BATT | 2-pin JST | LiPo Battery 
J2 | USB_POWER_ONLY  | Header, 5-Pin, 0.1"  | SparkFun USB Breakout board (+5V, GND No data pins)
J3 | USB-B POWER  | USB Mini-B, SMT | USB VBUS Power Only (+5V,  GND  No Data pins) 
J4 | EXTERNAL ANTENNA  | U.FL RF COAX  | Connects Board to Moteino Antenna 
J5 | EXTERNAL ANTENNA   | SMA (R-P or NORM)   | Antenna Connector
J6 | GPS/APRS  | Header, 4-Pin, 0.1"  | Serial data (D0, D1 ) + 3.3V Power + GND
J7 | DHT-11   | Header, 4 Pin 0.1"  | Humidity and Temp Sensor 
J8 | I2C  | Header, 4-pin 0.1"   | Baro Sensor or other I2C, SCL SDA 3.3V POWER GND
JP1 | NO PWM  |  SMT Jumper | To Bypass Backlight PWM Transistor Q1
JP2 | NO SI BUFF   | SMT Jumper  | Bypass MOSI Switch  U3 to SD Card
JP3 | NO SO BUFF   | SMT Jumper |  Bypass MISO Switch U1 from SD Card
JP4 | N/A   | N/A   | Not used - removed from board version
JP5 | IRQ   | SMT Jumper   | Connects RTC IRQ to pin D2
JP6 | CARD DET  | SD card inserted  | No card = low Connects to pin D2
TP1 | 32KHZ  | Test Point  | RTC 32KHz Output
TP2 | SQW  | Test Point  | RTC Square Wave Output (for interrupt)
TP3 | LED  | Test Point  | Moteino LED Signal (D9)
TP4 | GND  | Test Point  | Power / Test Ground
TP5 | VBATT | Test Point  | Battery Voltage
TP6 | TST  | Test Point  | Connetct a digital signal to LED6 ( or Peizo Speaker!) 
TP7 | /RST   | Test Point  | RTC Reset, GND = Resets RTC clock

 * **NOTES** 
   * *1. The 2.8" display has a touch screen but the pins are not connected in in this version.*
   * *2. I have started a version that uses a Teensey 3.2.  Early software shows promise as it now sucessfully communicates to the RF-69 radio and TFT.
