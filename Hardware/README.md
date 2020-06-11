# VP3-Weather-Receiver Hardware
*Davis Vantage Pro Weather Station Reciever using a Moteieino board with RFM69 and Color TFT Display*

This folder provides the hardware info for this project. The circuit board in the main page is an early version.  The current board will be available on OSHPark so you can just order boards if you want them as-is.  The main differences are some minor circuit fixes, a slight size adjustment (to fit in a case i have for the station) and embedding the RTC and battery on th board.  The original PCB was ony intended to use plug in modules and make it a little more robust than protoboards.  It is a strange combo of thru-hole and SMT technologies that reflect mostly what i had on hand or could get for this proto. 

# Schematic

The schematic is in KiCAD format, here is it is if you don't have that software. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Docs/Schematic.png)

The circuit board is shown assembled in these 3D renderings.  The circuit board will accomodate 2 sizes of 320x240 displays. The LiPo battery connector is on this side as well as it is sandwiched in between the display and main PCB.  There are 3 tactile #switches "+"  "-" and "GO!" labels# to set the clock and other parameters. You may want to use the long plunger types (13mm) if you are putting in some sort of case. They can be mounted on either side of the board as well. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_TOPSIDE.jpg)

The back side is where the Moteino and other modules plug in. The power connectors are on the left side.  I used a mini-USB connector for just power.  The Pin out for the USB_Power_Only is setup to match the SPARKFUN Breakout board enables a power plug to be moved depending on the case requirements. 

![VP2_TFT-Weather-Receiver](https://github.com/b-wave/VP2_TFT-Weather-Receiver/blob/master/Hardware/VP2_TFT_1_SOLDERSIDE.jpg)

