

/*******************************************************************
This is a demo of the dekay/DavisRFM69 library using a TFT LCDscreen 
for a Weather Receiver console replacement. 

It displays only  the data received from the Davis Vantage Vu ISS.
Curently, this version does not  add the internal data to make a complete 
TFT console replacement for display of all weather parameters.

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


 
02/25/2019  V0.1 (c)SBOTTS Basic Layout of TFT
02/26/2019  V0.2 Test WIND Compass 
02/27/2019  V0.3 Clock and Flashing Seconds 
            V0.31 Test DHT sensor
03/02/2019  V0.41 Updates to Cells using internal Temp Humidity
            V0.42 Inverts cells to show selected. Fixed multiple updates DHT
03/04/2019  V1.00 Initial version with DavisRFM69  
            V1.01 Replace inside with outside data but no wx data to screen
                  does not seem to be decoding incoming data.
                  clock updating, Not bad progress! 
            V1.02 Changed OK_LED pin 3 was conflicting with RTC interrupt.   
                  Added some prints to see what was going on.
                  Receiving wx on channel 2
03/05/2019  V1.03 Added Packet and Radio status displays for TFT,
                  moved positions of cells to display only outside and
                  radio data. Changed ID to #3.  Works! Sort of...
                  Runs but locks up after about 5 min.  
                  Maybe too many nested calls and interrupt? 
                  5170 bytes (79%) of program storage space.
03/05/2019  V1.04 I think there is a SPI conflict! DavisRFM69 uses SPI in the interrupt.
                  See: https://www.pjrc.com/better-spi-bus-design-in-3-steps/
                  So need to add this for RFM69: SPI.usingInterrupt(RF69_IRQ_NUM); or RF69_IRQ_PIN
                  Also add pullups to the CS pins for better design.  
                  
                  Added some rain functions too...
                  28314 bytes (89%) of program storage space.<<may need to remove internal temp and baro 
03/05/2019  V1.05 Masive clean up.  Reset rain at midnight removing debug code.                    
03/05/2019  V1.06 NWS Rain statements. Gust, Accumilated Rain total. Also added keyboard inputs to test 
                  filtered wind to make the needle less jumpy. Works OK CW but jumps CCW direction still.
03/06/2019  V1.06 Fixed logic bug in the fWind() function. Added min / max temp.  
03/17/2019  V1.07 Clean up - removed indoor functions. Now at 25028 bytes (78%) of program storage space.                  
                  Reset max/min temp at midnight.
04/23/2019  V1.08 Changed TFT Pins to match OSH Board.  Also the TFT
                  rotation from 3 > 5.  Back to station 2  as well/  
12/23/2019  V1.09 Added a scan feature that locks on any ISS.  Backed this out as it messes up RAIN 
                  Fixed Temp "MIN MAX" not to round up -- this was causing incorrect temps
                  TODO Min Max seem to be resetting at noon? - DONE Not a prolem - probabily caused by above change
01/08/2020  V1.10 Mass clean up.
                  Removing all unused features and libraties (INDOORS, Barometer etc.)  Motduino does not have 
                  enough capacity to add desired/needed features such as switch and logging

01/10/2020  V1.11 TODO LCD Backlight control.  DONE. Changed output to a PWM pin D5 was RTC INT.  
                  Mapped voltage from 16 - 255 seems to work fine.  No real change in RSSI 
                  values no PWM interference noted with backlight dimming. Works.    
                  TODO: Battery error DONE.
                  Added Day OF Week. Needed to use Adafruit/Jeelabs library, code was OK.  
                             
01/23/2020 V1.12  Added Button.h library!   Now able to set date and time w/o a PC.  All
                  settings seem to work OK.  I set the clock settings to be non-blocking of the reciever
                  operation so there is an issue with resposiveness but since this is a set up thing it
                  is not a daily user function i think it will be OK.  The whole settings thing works with
                  a global state machine.  the "GO!" ( enter ) key selects the cell to change. +/- incrs or
                  decs the numbers between ranges for HOURS, MINS, MONTH, DAY and YEAR.  SECONDs are reset with
                  HH and MM settings.  Updated a few print(F("....") 
                
02/10/2020 V1.12x Clean up the todo list...                   
                  (a) TODO - add button library  - Done!
                  (b) TODO - add set clock   - Done! 
                  (c) TODO -  Enter time/date  - Done! 
                  (d) TODO - Add ISS Chanel runtime select.  - DONE!
                  (e) TODO -  Max Wind gust of the day. DONE!
                  (f) TODO - Fix Temp and ISS Frames.  Missing line segments  DONE! 
                  (g) TODO - Daily MIN / MAX % REL HUMIDITY Displayed DONE!
                  (h) TODO - EEPROM To store ISS channel...Done (2/10/2020)
                  TODO - 
                  NOTE: Sketch uses 31220 bytes (98%) of program storage space. Maximum is 31744 bytes.
                          Global variables use 931 bytes of dynamic memory. W/O DEBUG ENABLED
                          
                  ISSUE:  Found on 2 instances the display was not locked up but radio was not updating
                  for several hours (4 AM - 8 AM) and 4PM Recovered @ 7PM by cycleing key modes. no RESET.
                  latest run seemss OK but may want to see if any changes ins V1.12 are responsible. May
                  also looke at backlight duty cycle.  Was able to wake the radio up by  cycling thru the
                  key modes, not sure if that was needed.  Keep an eye on this, may need to diff V10 and V11
                  UPDATE: May have been a loose conection?  Not seen since  

(not so) BIG TODO LIST REMAINING...
xx/xx/2019  V1.0x 
                 TODO: Remove all unused code, final release cleanup.
                 
                 TODO - EEPROM To store total rain, how many resets.
                  TODO: Dew Pt. Calculation? 
                  TODO:  WIND CHILL calculation? 

                  TODO:  SD Card / Logging  Too big for current Sketch!                       
NOTE: For <SD.h> Sketch uses 31912 bytes (100%) of program storage space. Maximum is 31744 bytes.
Global variables use 1708 bytes of dynamic memory.
Sketch too big; see http://www.arduino.cc/en/Guide/Troubleshooting#size for tips on reducing it.
Error compiling for board Moteino.

 

/*
 * //////////////////////////CHANGE MODES  V1.12/////////////////////////////////////
 * 
 * MODE
 * 0 = Running ACTION:  Normal mode, All screens updating, GO! key moves to next modes
 *     Only +/- will change.  GO! moves to next item. Items tat can be chnged are highlighted
 *     Data is sent  to RTC after each -/+ press. 
 * 1 = SET Hour.  calls SET_RTC_TIME Stops RTC UPDATE replaces screen with set screen
 *                (ENT) If enter w/out + or - keep currrent time and goto MODE2
 *                (+) INCREMENTS HH (00 -> 23) loops
 *                (-) DECREMENTS HH (23 -) 00) loops
 *                Sets Seconds to :00
 *                
 * 2 = Set Min     ENT) keeps current value and goto set minutes
 *                (+) INCREMENTS MM (00 -> 59)
 *                (-) DECREMENTS MM (59 -> 00)
 *                sets seconds to :00
 *                (ENT) go to next mode
 * 3 = SETMONTH   1 - 12  +, -, GO!
 * 4 = SET DAY    1 - 31  +, -, GO!       
 * 5 = SET YEAR   2020 - 2099 +, -, GO!  
 * 6 = SET ISS Channel  Sets channels 1 -> 8 ISS 0 = scan all channels! 
 * //////////////////////////CHANGE MODES/////////////////////////////////////
 * 
 * 
 * ////////////////////////DISPLAY Frames /////////////////////////////////////////
 * Here are where the various displays are located.  The positions use 
 * basic x, y and size in this format:
 *  drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
 *  from https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.h
 *  i didn't really plan the locations but they were added as needed. All the status 
 *  boxes on the right start at half way on the TFT and are 40 px high so the box 
 *  below is +40 from above. 
 *  
 * tft.drawRect(0, 0, tft.width(),40, ILI9341_BLUE); ///info+Clock Bar on top
 * tft.drawRect(0, 40, tft.width()/2,200, ILI9341_BLUE);  //Outlines the Wind Area
 * tft.drawRect(tft.width()/2, 40, tft.width()/2,40, ILI9341_BLUE);  //Temp Area norm   
 * tft.drawRect(tft.width()/2, 80, tft.width()/2,40, ILI9341_BLUE);  //Rh Area 
 * tft.drawRect(tft.width()/2, 120, tft.width()/2,40, ILI9341_BLUE);  //RAIN - old BAR Area
 * tft.drawRect(tft.width()/2+120, tft.height()/2+40, tft.width()/2,40, ILI9341_BLUE);  //ISS INFO
 * >>>>>>>>>>>>(tft.width()/2, 160, tft.width()/2,40, ILI9341_BLUE); //ISS Info
 * tft.drawRect(tft.width()/2, 200, tft.width()/2,40, ILI9341_BLUE);  //RADIO Area
 * 
 * 
 *****************************************************************************/

#define VERSION " v1.12h"        // Version of this program
//#define TITLE "XyGyWx"
#define TITLE "VP2_TFT"        //For display


/////////////////////Save Info Between Resets////////////////////////////////
//#include <SPIFlash.h>  //Use this for the Moteino External Flas part.
#include <EEPROM.h>  //else use the Arduino's EEPROM  V1.13(h)
////////////////////////////////////////////////////////////////////////////

#include "SPI.h"                //From standard Arduino library
#include <Adafruit_ILI9341.h>  //http://www.adafruit.com/products/1651
#include <DavisRFM69.h>       // From https://github.com/dekay/DavisRFM69 

//TODO: Include SD Card support for logging.

// For Mote (R6)Use hardware SPI like on Uno, #13, #12, #11) and the below for CS/DC
#define TFT_DC  6             // was 9
#define TFT_CS 7              //was 10

//Clock
#include <RTClib.h>           //Using Adafruit: https://github.com/adafruit/RTClib
///here are some scaled down versions for RTC ... may save some space...
//#include <RTC_DS3231.h>       // Need to try: https://github.com/mizraith/RTClib 
//#include <DS232RTC>           // Need to try: https://github.com/JChristensen/DS3232RTC
#include <Wire.h>             // From standard Arduino library
                             
//#define RTC_SQW_IN 5          // input square wave from RTC into T1 pin (D5)
                              // TIMER1 does not interfere with Arduino delay()
#define VP2 false       //we got us a Vantage VU ISS 
#define INDOORS false  //only report data from ISS on M6 (saving some room - needs Mega)

#if INDOORS //Display only outdoor sensors if FALSE ...most of these have been removed

//////DHT and BMP0805  was used for initial testing.  We are only getting data from ISS now.
#include <DHTxx.h>                             
#include "DHTxx.h"            //From: https://github.com/dekay/DavisRFM69
#define DHT_DATA_PIN    4     // Use pin D4 to talk to the DHT22
#include <Adafruit_BMP085.h>  //From: https://github.com/adafruit/Adafruit-BMP085-Library

#endif

//Other used pins:
#define LED               9       // Moteinos have LEDs on D9
#define GREEN_LED         1       // OK
#define RED_LED           0       // ERR
#define LCD_PWM           5       // LCD Backlight

///Enable the buttons for settings
#include <Button.h>  //V1.12

Button PLUS_key(A1);
Button MINUS_key(A2);
Button OK(A0);


/*  This is the PIN info for the V1 PROTOTYPE REV AHARDWARE DWG 190409A 
 *   Will need to be adjusted for V2! REV D Hardware...
 * A7 = VBATT
 * A6 = LED PWM
 * A5 = SCL
 * A4 = SDA
 * A3 = AMBIENT LIGHT SENSOR
 * A2 = S2 (-)
 * A1 = S3 (+)
 * A0 = S1 (GO!)
 * 
 * D2 = SQW (int) SD Card + Derect 
 * D1 = LED (D3)  + Serial TX
 * D0 = LED (D4)  + Serial RX
 * 
 */
////////////////BatteryVolts()///////////////////////
// Monitors the console's power and battery.  
// mostly for test, may be used to animate a power 
// graphic icon to display charge and status
// NOTE: the battery is strictly for backup power 
//       but it does get charged while the unit is plugged in
/////////////////////////////////////////////////////
 float BatteryVolts()
 {
 float temp = 0.0;
  float InputVolts = 0.0;
  int AnalogValue = analogRead(A7);
  temp = (AnalogValue * 3.3)/1024.0 ; // 3.3V REFERENCE
  InputVolts = temp/0.5;//100K||100K = 0.5
  return(InputVolts);    
 }

///////////////////LightSensor()////////////////////////////
// Monitors the output of the light sensor and maps to 
// a percentage value
// mostly for test now.  Will map to control the TFT LCD
// Back light LED, to control brightness and possibly
// save power in battery mode?
///////////////////////////////////////////////////////////
 int LightSensor()
 {
 int tmp = 0;
 int pwm = 0;
  int SensorValue = analogRead(A3);
  tmp = map(SensorValue, 0, 1023, 100, 0);
  pwm = map(SensorValue, 0, 1023, 255, 25); //V1.11 Back light test!
  analogWrite(LCD_PWM, pwm);  //set pwm pin V1.11
  //TODO add low power mode map...to extend battery life
  return(tmp);    
 }


 


// Reduces number of compiler warnings when using print(F()}, see http://bit.ly/1pU6XMe
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))

#if !defined(__time_t_defined)
  typedef unsigned long time_t;
#endif

// Header bytes from ISS (weather station tx) that determine what measurement is being sent
// Valid hex values are: 40 50 60 80 90 A0 E0  - really only care about MSB, the LSB is staion ID (where 0 is station #1)
// See http://github.com/dekay/im-me/blob/master/pocketwx/src/protocol.txt
//     http://bit.ly/1kDsXK4
//     http://www.wxforum.net/index.php?topic=10739.msg190549#msg190549
//     http://www.wxforum.net/index.php?topic=18489.msg178506#msg178506
#define ISS_UV_INDEX     0x4
#define ISS_RAIN_SECONDS 0x5
#define ISS_SOLAR_RAD    0x6
#define ISS_OUTSIDE_TEMP 0x8
#define ISS_WIND_GUST    0x9
#define ISS_HUMIDITY     0xA
#define ISS_RAIN         0xE

////////////////////////////////////////////////////////////////////////////////////////////////
// Global Weather data to send to  TFT Display
///////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////CHANGE  ISS TO LISTEN TO////////////////////////////////////
byte TRANSMITTER_STATION_ID = 3;    //station ID to be monitored.  Default station ID is normally 1
//TODO :  Make this a variable instead of a const so we can change the station   DONE! V1.12
//TODO - Save in EEPROM for power issies. DONE: V1.12(h)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int ID_Address = 0; //EEPROM address to start  from

//byte     RX_STATION_ID = TRANSMITTER_STATION_ID;
byte     ISS_rainCounter =        0;  // rain data sent from outside weather station.  1 = 0.01".  Just counts up to 127 then rolls over to zero
byte     ISS_windgustmph =        0;  // Wind in MPH
//float    VP2_dewpoint =         0.0;  // Dewpoint F
float ISS_dayRain =            0;  // Accumulated rain for the day in 1/100 inch uint16_t
float ISS_TotRain =            0;  // Accumulated rain since reset in 1/100 inch 
float    ISS_rainRate =           0;  // Rain rate in inches per hour
//float    VP2_insideTemperature =  0;  // Inside temperature in tenths of degrees
int16_t  ISS_outsideTemperature = 0;  // Outside temperature in tenths of degrees
//uint16_t ISS_barometer =          0;  // Current barometer in inches mercury * 1000
byte     ISS_outsideHumidity =    0;  // Outside relative humidity in %.
byte     ISS_windSpeed =          0;  // Wind speed in miles per hour
byte     ISS_WindMAX  =          0;  // Wind speed in miles per hour
uint16_t ISS_windDirection_MAX =  0;  // Max 24HR wind direction, from 1 to 360 degrees (0 = no wind data)
String ISS_WindMax_Time = "";  // Time of last gust

uint16_t   ISS_windDirection_Now =  0;  // Instantanious wind direction, from 1 to 360 degrees (0 = no wind data)
//uint16_t ISS_windDirection_Avg =  0;  // Average wind direction, from 1 to 360 degrees (0 = no wind data)
bool     ISS_gotInitialWeatherData = false;  // flag to indicate when weather data is first received.  Used to prevent zeros from being uploaded to Weather Underground upon startup
bool     ISS_isBatteryOk = false;    // Battery status in ISS transmitter 
bool     Error_Flash = false;    // flashing 
int16_t MinDayTemp = 1200;  //really hot - it has to be colder that this?
int16_t MaxDayTemp = -1200; //really cold - it has to be warmer than this..right?
int16_t MinDayHumid = 100;  //really humid - it has to be dryer that this?
int16_t MaxDayHumid = 0;    //really cold - it has to be wetter than this..

//TODO:cleanup these pins. 
//TODO: Add some additional LEDs! 

// I/O pins
//const byte RX_OK =    A0;  // LED flashes green every time Moteino receives a good packet
//const byte RX_BAD =   A1;  // LED flashes red every time Moteinoo receives a bad packet
const byte SD_OK =     4;  // LED flashes green when data is sucessfully written to SD card (Change PIN)
//

//TODO: Configure pins for either Type
//#ifdef __AVR_ATmega1284P__
//const byte MOTEINO_LED =      15;  // Moteino MEGAs have LEDs on D15
//  const byte SS_PIN_RADIO =      4;  // Slave select for Radio
//  const byte SS_PIN_ETHERNET =  12;  // Slave select for Ethernet module
//#else
//  const byte MOTEINO_LED =       9;  // Moteinos have LEDs on D9
//  const byte SS_PIN_RADIO =     10;  // Slave select for Radio
//  const byte SS_PIN_ETHERNET =   7;  // Slave select for Ethernet module
//#endif


const byte SS_PIN_RADIO =     10;  // Slave select for Radio
const byte MOTEINO_LED =       9;  // Moteinos have LEDs on D9
const byte TFT_PWM =       5;  // TFT LCD LEDs on D5  V1.11 
// Used to track first couple of rain readings so initial rain counter can be set
//TODO: Maybe use flash for some long term counts that can survive a reset
enum rainReading_t { NO_READING, FIRST_READING, AFTER_FIRST_READING };
rainReading_t ISS_initialRainReading = NO_READING;  // Need to know when very first rain counter reading comes so inital calculation is correct  
bool NewDay = false;
 
//Global Variables for Wind Direction Compass:
//TODO: This space can be reduced as it can track up to 3 display hands or we can use the 3rd for average direction
float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
uint16_t osx=64, osy=64, omx=64, omy=64, ohx=64, ohy=64;  // Saved H, M, S x & y coords
float sdeg=0, mdeg=0, hdeg=0;
uint16_t x0=0, x1=0, y0=0, y1=0;

//Manual pushbutton settings modes and variables
enum Set_Mode {RUNNING, SET_HR, SET_MIN, SET_MONTH, SET_DAY, SET_YEAR, SET_ISS };
Set_Mode Current_Mode = RUNNING;
enum Set_op {None,Inc,Dec};
Set_op Current_Op = None; //None, Inc, Dec

uint16_t PACKET_INTERVAL = 2500;
/*
//Precalculate packet timing...
const uint16_t INTERVAL0 = (40.0 + 0)/16.0 * 1000.0;  //2500
const uint16_t INTERVAL1 = (40.0 + 1)/16.0 * 1000.0;  //2563
const uint16_t INTERVAL2 = (40.0 + 2)/16.0 * 1000.0;  //2625
const uint16_t INTERVAL3 = (40.0 + 3)/16.0 * 1000.0;  //2688
const uint16_t INTERVAL4 = (40.0 + 4)/16.0 * 1000.0;  //2750
const uint16_t INTERVAL5 = (40.0 + 5)/16.0 * 1000.0;  //2813
const uint16_t INTERVAL6 = (40.0 + 6)/16.0 * 1000.0;  //2875
const uint16_t INTERVAL7 = (40.0 + 7)/16.0 * 1000.0;  //2938

uint16_t PACKET_INTERVALS [8] = 
  { 
    INTERVAL0,
    INTERVAL1,
    INTERVAL2,
    INTERVAL3,
    INTERVAL4,
    INTERVAL5,
    INTERVAL6,  
    INTERVAL7
   };
*/
//CREATE INSTANCE OF LIBRARY FOR TFT
Adafruit_ILI9341 tft =  Adafruit_ILI9341(TFT_CS, TFT_DC);



//CREATE INSTANCE OF LIBRARY FOR RTC
    RTC_DS3231 RTC;   //use DS3232RTC

//CREATE INSTANCE OF LIBRARY for RFM69

   DavisRFM69 radio;

//=============================================================================
//        ======================== SETUP ==============================
//=============================================================================

void setup() {
 TRANSMITTER_STATION_ID = EEPROM.read(ID_Address);  // get teh last saved ISS Number
//Set pins for buttons  //V1.12
  PLUS_key.begin();
  MINUS_key.begin();
  OK.begin();

  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);  //Turn off LED

  pinMode(RED_LED, OUTPUT);
  digitalWrite(LED,LOW);  //Turn off LED

  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(LED,HIGH);  //Turn off LED


  
///////////////Set Up TFT//////////
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setRotation(5); //We need landscape!
  tft.println("Starting TFT...");

  /////////TEST Backlight Dimming///////////////
    pinMode(LCD_PWM, OUTPUT);  //PWM PIN  V1.11
    analogWrite(LCD_PWM, 0);  //test pwm pin V1.11 OFF
//    tft.println("Backlight TEST...");
  //  delay (1000);
 //   analogWrite(LCD_PWM, 32); //DIM
//    tft.println("Backlight dim.");
    delay (1000); 
    analogWrite(LCD_PWM, 128);//Half Bright
//    tft.println("Backlight is Half.");
    delay (1000);   
    analogWrite(LCD_PWM, 255); //Exit with backlight on FULL V1.11
//    tft.println("Backlight is FULL.");
    delay (1000); 
//CLEAR TFT
  tft.fillScreen(ILI9341_BLACK);
//////////////////////NOTE/////////////////////////////
//this has to be FALSE if you want to see the
//Status LEDs on the panel - they use the SER Pins
//////////////////////NOTE///////////////////////////// 
#define SERIALMON  0
#if SERIALMON  


  Serial.begin(9600);
  
  // TODO: dont wait for serial for stand alone device.
  
  while (!Serial) ; // wait for Arduino Serial Monitor
 delay (2000); //wait a while...


  Serial.println("Begin ILI9341 Test!"); 
  tft.fillScreen(ILI9341_BLACK);

  
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
 #endif
 
//////////////IRQ NOT USED//////////////////////////////////////////
// Set up DS3231 real time clock on Moteino INT1
// INT1 on AVRs should be connected to DS3231's SQW (ex on ATmega328 it's D3, on ATmega644/1284 it's D11)

  #define DS3231_IRQ_NUM 1
//NOT USED
//    pinMode(RTC_SQW_IN, INPUT);

//CREATE INSTANCE OF LIBRARY FOR RTC
        
    
    //--------RTC SETUP ------------
    Wire.begin();
    RTC.begin();
    delay(1000);   
//TODO: Set an alarm for MIDNIGHT to reset Rain and min/max etc.
//DONE:      Currently testing hour for 00:00

// if (! RTC.isrunning()) {
  if (RTC.lostPower()) {

    Serial.println("RTC lost power, lets set the time!");

    // following line sets the RTC to the date & time this sketch was compiled

    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
 //RTC.adjust(DateTime(2014, 1, 21, 3, 0, 0));

    // This line sets the RTC with an explicit date & time, for example to set

    // January 21, 2014 at 3am you would call:

    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }
 //TODO I am not sure why this is/was not working on my RTC mod!
 //DONE: I think this is OK clock seems fine
 //   Serial.println(F("Could not start DS3231 RTC, check battery!"));
 //   tft.println(F("Could not start RTC"));
 
///////////////////////////////////////////////////////////////////////////////
// following line sets the RTC to the date & time this sketch was compiled
//    RTC.adjust(DateTime(__DATE__, __TIME__));
////////////////////////////////////////////////////////////////////////////////

  
  Serial.println( __TIME__); //show compile time?
  Serial.println(F("The clock is operating ...We're under way!"));

 //TODO: once set time in DS3231 we can comment out the following: 
//TODO: Need a manual way to set DATE/TIME  DONE V1.12(a)

//  RTC.adjust(DateTime(__DATE__, __TIME__));  //Off by about 20 Seconds! 
//////////////////////////////////////////////////////////////////////////////////
   
#define SECONDARYDISP false  //TODO:  Maybe for bigger displays? 
 
// Set up various areas on the display screen:
      tft.setRotation(5); //We need landscape!
                      
      tft.drawRect(0, 0, tft.width(),40, ILI9341_BLUE); ///info/Clock Bar on top
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
       
      tft.setTextSize(2);  //"Normal" text size
      tft.setCursor(3, 3);  //Title goes here
      tft.print(TITLE);  //Name it
      tft.setTextSize(1);   //smaller text
      tft.print(VERSION);  //Version it

#if SECONDARYDISP      //this is the second line size 1on some displays it is too small
      tft.setCursor(3,24);  //INDOOR MEASURMENTS here   
      tft.print("Inside: 69F Rh: 50%");  
#endif   
      tft.setTextSize(2);
      tft.setCursor(tft.width()/2-24,3); //HOURS here 
      tft.print(F("--"));  //hours 
      tft.setCursor(tft.width()/2,3);  //Colon is smack dab center
      tft.print(F(":"));   //colon
      tft.setCursor(tft.width()/2+10,3);  //MINs here
      tft.print(F("--"));  //minutes
      
#if SECONDARYDISP        
      tft.setCursor(tft.width()/2-24,24);//Time Zone here?  
      tft.setTextSize(1); 
      tft.print(F("PST UTC+7"));    
#endif      
      tft.setTextSize(2);
      tft.setCursor(tft.width()-110,3); //DATE   here 
      tft.print(F("--/--/--"));  //dummy date

#if 0       
      tft.setCursor(tft.width()-90,24); //DAY goes here
      tft.setTextSize(1);
      char daysOfWeek[7][12] = {"Sunday  ", "Monday","Tuesday","Wednesday","Thursday ","Friday  ","Saturday"};  //From: github.com/Adafruit/RTClib but w/spaces added
      tft.print(daysOfWeek[now.dayOfWTheWeek()]);  
#endif

      tft.drawRect(0, 40, tft.width()/2,200, ILI9341_BLUE);  //Outlines the Wind Area

            
//      tft.drawRect(0, tft.height()/4, tft.width()/2,20, ILI9341_RED);   
      
//  DisplayTempBox( +1555, true);  //Test the temp display cell.... this will break max /min

         
#if SECONDARYDISP                      
       tft.setTextSize(1); 
       tft.setTextColor(ILI9341_RED,ILI9341_BLACK);
       tft.setCursor(tft.width()/2+4,66);
       tft.print("HI+123F "); 
       tft.setTextColor(ILI9341_BLUE,ILI9341_BLACK); 
       tft.print("LO -20F ");              
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);                 
      //+100F Max / Min
 #endif
 
//      tft.drawRect(tft.width()/2, 80, tft.width()/2,40, ILI9341_BLUE);  //Rh Area 
//      tft.setCursor(tft.width()/2+8,90);  //rH% Here? 
//      tft.print("99% rH");  

      DisplayHumidBox(0xff,true);  //this can be either inside or outside rH
       
      //123456789012345678901234567890 
      //100% Rh Wet / Dry / Nice
      
      //TODO: Dewpoint calculation
//////////////////////////////////////////////////////////////////////
//Initial drawing of some of the weather info boxes using test data
/////////////////////////////////////////////////////////////////////

    DisplayRainCell();   //try it for test
    DisplayTempBox(0xff,true); //This is a test...I am not sure how to tell bad Temp
    DisplayISS();

/////////////////////////////////////////////////////////////////////////
//This area will be for Radio info on lower RIGHT of LCD
////////////////////////////////////////////////////////////////////////                
      tft.drawRect(tft.width()/2, 200, tft.width()/2,40, ILI9341_BLUE);  //RADIO Area

      
       // 123456789012345678901234567890 Fits...
       // ID#01 CHAN#01  RSSI-123dBm

       //This moved to radio packet data display thing:
      //1234567890123456789012345678901234567890
      //Last Pkt:  00:00:00 AA.BB.CC.DD.EE.FF 
//////////////////////////////////////////////////////////////////////////                     
//Set up compass dial:
/////////////////////////////////////////////////////////////////////////
 // Serial.print(F("Wind Dial... "));// DEBUG INFO
 // Serial.println(DrawCompass());  //output  status too
  DrawCompass();
   
  pinMode(TFT_CS, OUTPUT);  //V1.04 ---make sure the SPI buss knows who is boss?
  digitalWrite(TFT_CS, HIGH);
  pinMode(SS_PIN_RADIO, OUTPUT);  //V1.04 ---
  digitalWrite(SS_PIN_RADIO, HIGH);
  delay(500);  //hang on...

//////////////////////////////////////////////////////////////////////////
// Setup Moteino radio...
//
/////////////////////////////////////////////////////////////////////////
  SPI.usingInterrupt( RF69_IRQ_NUM); // since radio uses SPI in its interrupt. V1.04  
  radio.initialize();   // Maybe put using in interrupt needs DavisRFM69 needs pull request? 
  radio.setChannel(0); // Frequency - Channel is *not* set in the initialization. Need to do it now

//Set up Timer
  RTC_Millis rtc;        // software clock

//Initialize the LCD screen...
  UpdateWindDisplay( 0, 0, 0,"");
  DisplayRadioData(true);
  Serial.println(F("Done!")); //DEBUG MSG: DONE WITH SETUP
  DisplayPacket();
  
//Test LEDS
  blink(LED, 50);  //Blink 
  blink(GREEN_LED, 60);  //Blink me too
  blink(RED_LED, 100);  //Blink me too


} //End Setup

bool  fft = 0;   // this keeps the first erasures from deleting dial  TODO: DOES THIS BELONG HERE?


//=============================================================================
//        ======================== MAIN LOOP ==============================
//=============================================================================
    
void loop(void) 
{
    int          w = tft.width(),
                 h = tft.height();
     bool UpdateScreen = true;            
    tft.setRotation(5);  //Landscape will be needed
    
// This was a TEST that  does all degress fast ...Not needed 
//  for(int ddd=0; ddd<360; ddd++) {

//TODO: get rid of this polling loop?
//if (radio.receiveDone()) {... // https://github.com/dekay/DavisRFM69/blob/master/Examples/VP2/VP2.ino
//bool haveFreshWeatherData = getWirelessData();
   
{
  static uint32_t lastRxTime = 0;  // timestamp of last received data.  Doesn't have to be good data
  static byte hopCount = 0;
  
  DispISS_Batt_Status(); //I put this in the main loop so i can flash the ERR if ISS Battery is bad 
   if (OK.pressed())  // only cycle to the next
         {
          //Serial.println("OK!");  
          Current_Op = None;  //Do no harm
          if (Current_Mode == RUNNING) Current_Mode = SET_HR; 
          else if (Current_Mode == SET_HR)  Current_Mode = SET_MIN;  
               else if (Current_Mode == SET_MIN)  Current_Mode =  SET_MONTH; 
                     else if (Current_Mode == SET_MONTH)  Current_Mode = SET_DAY;     
                            else if (Current_Mode == SET_DAY)  Current_Mode =  SET_YEAR;  
                                else if (Current_Mode == SET_YEAR)  Current_Mode = SET_ISS; 
                                       else if (Current_Mode == SET_ISS)  Current_Mode = RUNNING; 
          Display_Mode(); 
             // DisplayISS();                           
         }
    if(  PLUS_key.pressed()){
      //Serial.println("+"); 
       Current_Op = Inc; //None, Inc, Dec
       DisplaySetTime();  //do it!
       Current_Op = None;  //done and none!
    }
    if(  MINUS_key.pressed())  {
     // Serial.println("-");  
       Current_Op = Dec; //None, Inc, Dec
       DisplaySetTime();  //do it!
       Current_Op = None;  //done and none!
    }
    
     DisplaySetTime();
 // bool gotGoodData = false;  // Initialize
 //process any serial input]
#define DEBUG2  0
#if DEBUG2   
  if (Serial.available() > 0)
  {
    char input = Serial.read();
     if (input == 'i')
    {
      Serial.print("Listening to ISS: ");
//      Serial.println(((radio.DATA[0] & 0x07) + 1), HEX);  
      Serial.println(TRANSMITTER_STATION_ID, HEX);
    }  

         if (input == 'r')
    {
      Serial.print("increment Rain : ");
      ISS_dayRain++; // += 
      ISS_TotRain++;
      Serial.println(ISS_dayRain/100);         
     DisplayRainCell();  
    } 

           if (input == 'Z')
    {
      Serial.print("ZERO Day Rain : ");
       NewDay = true;  //was
      Serial.println(ISS_dayRain);         
//     DisplayRainCell();  //immeadiately do it 
    } 
/*
         if (input== '!')  // only cycle to the next
         {
          if (Current_Mode == RUNNING) Current_Mode = SET_HR; 
          else if (Current_Mode == SET_HR)  Current_Mode = SET_MIN;  
               else if (Current_Mode == SET_MIN)  Current_Mode =  SET_MONTH; 
                     else if (Current_Mode == SET_MONTH)  Current_Mode = SET_DAY;     
                            else if (Current_Mode == SET_DAY)  Current_Mode =  SET_YEAR;  
                                else if (Current_Mode == SET_YEAR)  Current_Mode = RUNNING;                             
// DEBUG

//          Serial.print("Incrementing Mode : "); 
//          Serial.println(Current_Mode);  

 
          Display_Mode();
         

         }
*/ 

       /*
        if (input == '<'){
          if (Current_Mode != RUNNING) {
              if (Current_Mode = SET_HR); {
               Serial.print("Dec HRs : ");                   
              }
              if (Current_Mode = SET_MIN); {
               Serial.print("Decr MINs : ");                   
              } 
              if (Current_Mode = SET_MONTH); {
               Serial.print("Dec Months : ");                   
              }  
              if (Current_Mode = SET_DAY); {
               Serial.print("Dec Days : ");                   
              }  
              if (Current_Mode = SET_YEAR); {
               Serial.print("Dec Years : "); 
              }  
            } //END if Running
  
          } //End Decrement
 */
          Display_Mode();     


/*    
 *     The following commands were for testing
 *     They are not needed once it got working
 *     I am keeping these that i can un comment if i need
 *     to test...
 *     
//RADIO REGISTERS
    if (input == 'r') //d=dump all register values
    {
      radio.readAllRegs();
      Serial.println();
    }
    
// FLASH TESTS   
    if (input == 'd') //d=dump flash area
    {
      Serial.println("Flash content:");
      int counter = 0;

      while(counter<=256){
        Serial.print(flash.readByte(counter++), HEX);
        Serial.print('.');
      }
      while(flash.busy());
      Serial.println();
    }
    if (input == 'e')
    {
      Serial.print("Erasing Flash chip ... ");
      flash.chipErase();
      while(flash.busy());
      Serial.println("DONE");
    }
    if (input == 'i')
    {
      Serial.print("DeviceID: ");
      word jedecid = flash.readDeviceId();
      Serial.println(jedecid, HEX);
    }
 */ 
//Read the radio temp... 
    if (input == 't')
    {
      byte temperature =  radio.readTemperature(-1); // -1 = user cal factor, adjust for correct ambient
      byte fTemp = 1.8 * temperature + 32; // 9/5=1.8
      Serial.print( "Radio Temp is ");
      Serial.print(temperature);
      Serial.print("C, ");
      Serial.print(fTemp); //converting to F loses some resolution, obvious when C is on edge between 2 values (ie 26C=78F, 27C=80F)
      Serial.println('F');
    }


//          Serial.print("Incrementing Mode : "); 
//          Serial.println(Current_Mode);  

 
          Display_Mode();
    DisplaySetTime();
  }
#endif

 //////////////////////////////////////////////
 // Process wireless ISS packet
 //////////////////////////////////////////////
  if ( radio.receiveDone() )
  {
    packetStats.packetsReceived++;
    // check CRC
    unsigned int crc = radio.crc16_ccitt(radio.DATA, 6);
    if ((crc == (word(radio.DATA[6], radio.DATA[7]))) && (crc != 0))
    {
      decodePacket();  
     if ( packetStats.receivedStreak < 100) packetStats.receivedStreak++;
     //Good stuff happened...
      hopCount = 1;
      blink(GREEN_LED, 50);
      blink(LED, 50); //??
      DisplayPacket();
      DisplayRadioData(true);
    }
    else  //Bad stuff happened
    {
      packetStats.crcErrors++;
//      packetStats.receivedStreak--;
   if ( packetStats.receivedStreak <= 0) packetStats.receivedStreak = 0;
     blink(RED_LED, 50);  
     packetStats.receivedStreak = 0;
     DisplayRadioData(false);  //this displays with RED 
    }
    
    // Whether CRC is right or not, we count that as reception and hop
    lastRxTime = micros()/1000UL;
    radio.hop();
  } // end if(radio.receiveDone())
  
  // If a packet was not received at the expected time, hop the radio anyway
  // in an attempt to keep up.  Give up after 25 failed attempts.  Keep track
  // of packet stats as we go.  I consider a consecutive string of missed
  // packets to be a single resync.  Thx to Kobuki for this algorithm.
  // Formula for packet interval = (40 + STATION ID)/16 seconds.  ID is Davis ISS ID, default is 1 (which is 0 in packet data)
  // See: http://www.wxforum.net/index.php?topic=24981.msg240797#msg240797 
  // Dekay uses 2555 for Packet Interval, see: http://git.io/vqDqS
  
  if(TRANSMITTER_STATION_ID ==0) { PACKET_INTERVAL = (40.0 + 1)/16.0 * 1000.0;  }  //Default = 2500
     else{ PACKET_INTERVAL = (40.0 + TRANSMITTER_STATION_ID)/16.0 * 1000.0;   }

  if ( (hopCount > 0) && (( (micros()/1000UL) - lastRxTime) > (hopCount * PACKET_INTERVAL + 200)) )
  {
    packetStats.packetsMissed++;
           blink(RED_LED, 5);
    if (hopCount == 1)
    { 
      packetStats.numResyncs++; 
       blink(RED_LED, 5);
    }
    
    if (++hopCount > 12)
    { hopCount = 0; }
    radio.hop();
  }

} // end getWirelessData()
      

////////////////////////////////////////////////////////
//Write the Time  to LCD
///////////////////////////////////////////////////////
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK ); 
      tft.setTextSize(2);
      tft.setCursor(tft.width()/2-24,3); //HOURS here 
      //Get current clock value
      DateTime now = RTC.now(); 
      
    //Once a minute clean the display - needed?        
    if(now.second()== 0) 
    { 
    //CHECK FOR MIDNIGHT...
    UpdateScreen = true;    //screen will only be updated once a min? 
      if(now.minute()==0) {  //...or should it go here??
        //loging here? 
        ////Full Timestamp
//Serial.print(now.unixtime());  //works!
//Serial.print(now.unixtime() //works
// Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+now.timestamp(DateTime::TIMESTAMP_FULL)); //not found?

   
        if (now.hour()== 0) { 
          NewDay = true;

        }
      }
      //
   if (Current_Mode == RUNNING) {      //Don't update LCD in set modes
      if(now.hour()<10) tft.print(F("0"));  //leading zero!
      tft.print(now.hour());
      
 //  if((now.second()&1) == 0) tft.setTextColor(ILI9341_BLACK,ILI9341_BLACK);   
      tft.print(":");   
    if(now.minute()<10) tft.print(F("0")); // leading zero!
      tft.print(now.minute());
      
 //TODO: We really only need to update DATE this once a min?       
 ////////DATE////////
 //MONTH
     tft.setTextSize(2);
      tft.setCursor(tft.width()-110,3); //DATE   here 
    if(now.month()<10) tft.print(F("0"));
    tft.print(now.month(), DEC);
    tft.print(F("/"));
 //DAY   
    if(now.day()<10) tft.print(F("0"));
    tft.print(now.day(), DEC);
 
//YEAR
    tft.print(F("/"));   
    tft.print(now.year()-2000, DEC); //short year...you should know the century?

   }
/* 
 *  Set to FALSE if RTC library does not have day of week in this class/
 */ 
#if 1
//What weekday is it? 
      char daysOfWeek[7][12] = {"Sunday  ", "Monday","Tuesday","Wednesday","Thursday ","Friday  ","Saturday"};  //From: github.com/Adafruit/RTClib but w/spaces added
//char daysOfWeek[7][12] = {F("Sunday  "), F("Monday"),F("Tuesday"),F("Wednesday"),F("Thursday "),F("Friday  "),F("Saturday")};  //From: github.com/Adafruit/RTClib but w/spaces added
      tft.setCursor(tft.width()-90,24); //DAY goes here
      tft.setTextSize(1);
      tft.print(daysOfWeek[now.dayOfTheWeek()]); //DayofWeek
      tft.setTextSize(1); //Return to normal size text 
#endif  
 ////////////////////////////////        
//Now do the screen updates
////////////////////////////////
   if (UpdateScreen) {
// 1 minute
//Nothing here now was: indoor baro and humidity
//TODO: Lets move update DATE and LOGGING here
     
   }  //done 1 minute updates to screen  
      
} //Done with 1 Minute Screen updates

//////////////////////////////////
//only update once at :00 seconds
/////////////////////////////////
   if (now.second()!= 0)   UpdateScreen = false;

/////////////////////////////////
//process a new day 
//Normally done at Midnight
//but  you can set the flag to clear out
//the daily values too
////////////////////////////////
   if (NewDay) {
    ISS_dayRain = 0;
    DisplayRainCell();
    if (NewDay == true) {  
          MaxDayTemp = ISS_outsideTemperature; //reset the high and low 
          MinDayTemp = ISS_outsideTemperature; //temps as well
          MaxDayHumid = ISS_outsideHumidity; //reset the high and low 
          MinDayHumid = ISS_outsideHumidity; //Humidity as well                  
          packetStats.packetsReceived = 0; //clear all the packet info too
          packetStats.packetsMissed = 0;
          ////24 WIND MAX RESET HERE TOO...///  TODO!  DONE v1.12(e)
          ISS_WindMAX  =          0;  // Wind speed in miles per hour
          ISS_windDirection_MAX =  0;  // Max 24HR wind direction
          ISS_WindMax_Time = "";  // 
          NewDay = false;  //we only do it once on 00:00:00 
    }
    
   }
     tft.setCursor(tft.width()/2,3);  //Colon is smack dab center of TFT screen
     tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); 
     Error_Flash = true;   //this sets a flag to flash anything else in the fast loop..
     if((now.second()&1) == 1){
      tft.setTextColor(ILI9341_BLACK,ILI9341_BLACK); 
      Error_Flash = false;
     }
    tft.print(":");   //colon 
//////////////////////////////////////////////////////////////////////
// The wind display is in the fast loop for smoothing.  
/////////////////////////////////////////////////////////////////////  
 /*byte     ISS_WindMAX  =          0;  // Wind speed in miles per hour
uint16_t ISS_windDirection_MAX =  0;  // Max 24HR wind direction, from 1 to 360 degrees (0 = no wind data)
String ISS_WindMax_Time = "";  // Time o
  *   */
if(ISS_windSpeed > ISS_WindMAX){  //tag for new gust speed
 ISS_WindMax_Time = "";
 if(now.hour()<10) ISS_WindMax_Time += String("0");  //leading zero!
 ISS_WindMax_Time += String(now.hour());
 ISS_WindMax_Time += String(":");
  if(now.minute()<10) ISS_WindMax_Time += String("0");  //leading zero!
 ISS_WindMax_Time += String(now.minute());
}

  
    UpdateWindDisplay( fPoint( ISS_windDirection_Now ), ISS_windSpeed, ISS_windgustmph, ISS_WindMax_Time );

/////////////////////////////////////////////////////////////////////
//Console Battery updates all the time to monitor: 
/////////////////////////////////////////////////////////////////////
     tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); 
     tft.setCursor(3,24);  // Battery Voltage here   
     tft.setTextSize(1);
     tft.print(BatteryVolts());
     tft.print(F("V "));

/////////////////////////////////////////////////////////////////////
//Ambient light sensor updates all the time to monitor: 
//Test only?
/////////////////////////////////////////////////////////////////////       
     tft.print(LightSensor());
     tft.print(F("% "));   

////////////////////////////
////DONE WITH LOOP
////////////////////////////
     
    tft.setTextSize(2);  //Make sure we have normal text after all that   
    delay(100);   //Hang out for doneness 
    
 // }  This was for fast loop to see the wind compass do the sweep.
} //End Loop


//  =============================================================================
//======================== New TFT Display Functions ==============================
//  =============================================================================
  


//=============================================================================
//DRAW A COMPASS for wind direction on TFT from Davis ISS weather station
//Needs to be only called at setup or for screen refresh. 
//call UpdateWindDisplay( uint16_t DIRECTION, uint16_t SPEED)after to update 
//=============================================================================
// NOTES:
// This dial was ported from the examples in the TFT and GFX Libraries for
// an Analog Clock Demo.  Modified to do a wind compass weith 10-degree and card
// points.  Added Digital displays and a new smoothing algorithim i developed 
// so the needle is not randomly pointing around the face. 
//==============================================================================
unsigned long DrawCompass(){
    unsigned long start = micros();
    int         x = tft.width()/4,
                y = tft.height()/2;    
// 1. Draw dial...

  tft.fillCircle(x, y, 61, ILI9341_BLUE);
  tft.fillCircle(x, y, 57, ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREEN); 
  //Loop for Tick Marks     
    for(int i = 0; i<360; i+= 45) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*57+x;
    y0 = sy*57+y;
    x1 = sx*50+x;
    y1 = sy*50+y;
    tft.drawLine(x0, y0, x1, y1, ILI9341_WHITE);
    
 //2. Label Primary Cardinal directions...    
  if(i==0) {
      tft.setTextSize(2);
      tft.setCursor(x0-5, y0-22);
      tft.print(F("N"));  
      }
  if(i==180) {
      tft.setTextSize(2);
      tft.setCursor(x0-5, y0+10);
      tft.print(F("S"));  
      }
  if(i==90) {
      tft.setTextSize(2);
      tft.setCursor(x0+8, y0-8);
      tft.print(F("E"));  
      }

  if(i==270) {
      tft.setTextSize(2);
      tft.setCursor(x0-18, y0-8);
      tft.print(F("W"));  
      }
//3. Label Primary InterCardinal directions... 
    if(i==45) {
      tft.setTextSize(1);
      tft.setCursor(x0+8, y0-10);
      tft.print(F("NE"));  
      }
    if(i==135) {
      tft.setTextSize(1);
      tft.setCursor(x0+8, y0+1);
      tft.print(F("SE"));  
      }
    if(i==225) {
      tft.setTextSize(1);
      tft.setCursor(x0-16, y0+1);
      tft.print(F("SW"));  
      }
    if(i==315) {
      tft.setTextSize(1);
      tft.setCursor(x0-16, y0-10);
      tft.print(F("NW"));  
      }
    }

  //4.  Draw 36 x 10 degree dots...
  for(int i = 0; i<360; i+= 10) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*53+x;
    y0 = sy*53+y;
    
    tft.drawPixel(x0, y0, ILI9341_WHITE);

  }
  //5. Draw a center hub 
  tft.fillCircle(x, y, 3, ILI9341_RED);
  return micros() - start;
  
} //End DrawCompass

//=============================================================================
// TFT DISPLAY WIND DIRECTION AND VELOCITY from Davis ISS weather station
// Should only be called after:  DrawCompass()
// Updates the Wind pointer, Direction, and Speed on dial 
// should use average direction and or filtered Winddirection
//=============================================================================

void UpdateWindDisplay( uint16_t ddd, uint16_t WSpeed, uint16_t WGust, String Wtime){
  

      //TODO: Wind Chill calculation? 
      //TODO: No Sensor Error
         
      int        w = tft.width(),  //Needed? Maybe pre-calculate 
                 h = tft.height();
                 
//TODO WIND GUST MAX  DONE V1.12(e)

     if (WSpeed > ISS_WindMAX) {
      ISS_WindMAX = WSpeed;
      ISS_windDirection_MAX = ISS_windDirection_Now;
      ISS_WindMax_Time = Wtime; //gust now time direction all update
 
     }
//stramngely this is flashing....
//unless we set the colors here
  if(ISS_WindMAX != 0)  tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); 
     tft.setTextSize(1);
       tft.setCursor(8,tft.height()-22);      
          tft.print(F("GUST: "));  
          tft.print(Wtime);  
 
       tft.setCursor(8,tft.height()-13);
//       if (ISS_WindMAX<100) tft.print(F("0"));  //Add leading space/zero
       if (ISS_WindMAX<10) tft.print(F("0")); 
       tft.print(ISS_WindMAX);
       tft.print(F(" MPH  "));
       if (ISS_windDirection_MAX<100) tft.print(F("0")); 
       if (ISS_windDirection_MAX<10) tft.print(F("0")); 
       tft.print(ISS_windDirection_MAX);
//       tft.print(F(" DEG "));   
                 
 //Write the Direction in Degrees 
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); 
      tft.setTextSize(2);
      tft.setCursor(w/4-16, h/2+20); 
      if (ddd<100) tft.print("0");  //Add leading zeros
      if (ddd<10) tft.print("0");
      tft.print(ddd);
      tft.setTextSize(1);  // LC "o" in Size 1... 
      tft.print("o");      //..is Passable Degree symbol?
      tft.setTextSize(2); // back to full size
      
 //     tft.setCursor(w/4-64, h-24); //center and somwhere down here...
      tft.setCursor(w/4-22, h/2-36); 
      if (WSpeed<100) tft.print(" ");  //Add leading space/zero
      if (WSpeed<10) tft.print("0");
      tft.print(WSpeed);
      tft.setTextSize(1); 
      tft.setCursor(w/4-8, h/2-18); 
      tft.print(F("MPH"));
      tft.setTextSize(2);  
      
//Display Wind Gusts Info below the compass dile...
// if(WGust == 0) tft.setTextColor(ILI9341_BLACK,ILI9341_BLACK); //TODO: Clear if no 10 min gust?

 ////////////////////////////////////////////
//TODO: Add a daily max gust and time...   DONE V1.12(e) 
//GUST / DIR Lower Left screen?  DONE in V1.12! (e)
//
//MAX GUST: 12:34 
//99 MPH @ 360DEG 
//
    

/////////////////10 MIN GUST//////////////////////////////

     tft.setTextSize(1);
       tft.setCursor(tft.width()/4+30,tft.height()-22);    
      if (WGust<100) tft.print(" ");  //Add leading space/zero
      if (WGust<10) tft.print("0");
       tft.print(WGust);
       tft.print(F(" MPH"));
//label for 10 min gusts...    
       if(WGust != 0) tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
       tft.setCursor(tft.width()/4+35,tft.height()-13);
       tft.print(F("10-min"));     
       tft.setTextSize(2); // back to full size

  // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ddd;                  // 0-59 -> 0-354
    sx = cos((sdeg-90)*0.0174532925);    
    sy = sin((sdeg-90)*0.0174532925);
    
             
 // Erase Previous pointer unless first time
 // TODO: Makes a black line on dial ...should be background color?  DONE
 if (fft){tft.drawLine( w/4, h/2,osx, osy, ILI9341_BLACK); } //tft.drawLine(x1, y1, x2, y2, color)
      fft = 1; //once it has drawn a line it will be OK to erase it next time     
      sx = sx*47+w/4;    
      sy = sy*47+h/2;    
      osx= sx;    //Save for next seconds hand eraseure
      osy = sy;
      
 // DRAW IN POINTER to Direction
    tft.drawLine( w/4, h/2,osx, osy, ILI9341_RED);
    tft.fillCircle(w/4, h/2, 4, ILI9341_RED);
 
}//End of UpdateWindDisplay

#if INDOORS 
//
//=============================================================================
// Read Indoor temperature and humidity 
// Should be is read once per minute...TODO fix multiple reads  FIXED!
//=============================================================================

void readInsideTempHum() {
  int16_t insideTempC, insideHumidity;

 //    Serial.println(F("Reading inside "));  //this shows howmany time we enter!
     
  if (tempHum.reading(insideTempC, insideHumidity, true)) {
    // Temp and humidity are in tenths of a deg C and tenths of a percent, respectively
    // Values out of the console are tenths of a deg F and integer percent values.  PITA.
    VP2_insideTemperature = insideTempC*1.8 + 320;
    VP2_insideHumidity = (insideHumidity + 5) * 0.1;  // Round the reading
#if 1
    Serial.print(F("Inside TempC: "));
    Serial.print(insideTempC);
    Serial.print(F("  Global Inside TempF: "));
//this is decimal:     Serial.println(VP2_insideTemperature % 10);
    Serial.println(VP2_insideTemperature);

#endif
#if 1
    Serial.print(F("Inside Humidity Raw: "));
    Serial.print(insideHumidity);
    Serial.print(F(" Global Value: "));
    Serial.println(VP2_insideHumidity);

#endif
  }
}// END readInsideTempHum
#endif

//=============================================================================
// TFT DISPLAY TEMPERATURE from Davis ISS weather station (or inside)
// display either in the same tft cell area.
// can display selected (inverted) display 
//=============================================================================

void DisplayTempBox( int16_t Temp, bool InvertTemp)
{

//this inverts the display colors  if TRUE
if (InvertTemp) {
 tft.fillRect(tft.width()/2, 40, tft.width()/2,40, ILI9341_GREEN);
 tft.setTextColor(ILI9341_BLACK,ILI9341_GREEN);
} //inverted

else{
 tft.fillRect(tft.width()/2, 40, tft.width()/2,40, ILI9341_BLACK);
 tft.drawRect(tft.width()/2, 40, tft.width()/2,40, ILI9341_BLUE);  //Temp Area norm   
 tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);  
} //Normal

// tft.drawRect(tft.width()/2+62, 39, tft.width()-10,40, ILI9341_BLUE);      
 tft.setCursor(tft.width()/2+70,50);  //Outside temp
 tft.setTextSize(2);

//If sensor is off line we get a message.
//Tested at startup as well by sending the OFFLINE flag.
 
if( Temp==0xFF  ){
       tft.print("No Temp");  //  
       return;
}

//////////////////////////////////////////////
//Calculate High and low temps
/////////////////////////////////////////////
if (Temp < MinDayTemp)  MinDayTemp = Temp; 
if (Temp >= MaxDayTemp)  MaxDayTemp = Temp; //round it up?
 
if (Temp<=999 && Temp>0) tft.print(F("+"));      //so it always used 3 spaces

      tft.print(Temp/10);
      tft.print(F("."));  //one Decimal place!
      tft.print(abs(Temp%10)); //need to get rid of sign for neg-
           
// print units      
      tft.setTextSize(1);
      tft.print(F(" o")); // Lower case 'o' does fine for deg symbol
      tft.setTextSize(2);
      tft.print(F("F"));
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); //reset colors...
      
//TODO:  Need to fix this rectangle  - DONE V1.12(d)
//    tft.drawRect(tft.width()/2, 40, 60,40, ILI9341_BLUE);   // Temp Area only
      tft.drawRect(tft.width()/2, 40, 60,80, ILI9341_BLUE);   // Temp+Humid Area 
       
      tft.setCursor(tft.width()/2+3,46);  //Min Max Here? 
      tft.setTextColor(ILI9341_YELLOW,ILI9341_BLACK);  
      tft.setTextSize(1);
      tft.print(F("MAX: "));
      
      //really cold but zero degrees always gets its sign! 
      if (MaxDayTemp<999 && MinDayTemp>0) tft.print("+");
      
      //Note: temp is in 1/10 degrees.              
      tft.print(MaxDayTemp/10);

      //Min Max Here? - YES it looks good
      tft.setCursor(tft.width()/2+3,65);  
      tft.setTextColor(ILI9341_CYAN,ILI9341_BLACK);   
      tft.print(F("Min: ")); 
      
      //zero degrees always gets its sign! 
      if (MinDayTemp<=999 && MinDayTemp>0) tft.print("+");  
          
      tft.print(MinDayTemp/10);  
            
      tft.setTextSize(2); 
  
} //End display temp

//=============================================================================
// TFT DISPLAY HUMIDITY  from Davis ISS weather station (or INDOORS)
//=============================================================================
void DisplayHumidBox( uint16_t Humidity, bool InvertCell)
{
 tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); //reset colors...  
 if (InvertCell){
   tft.fillRect(tft.width()/2, 80, tft.width()/2,40, ILI9341_BLUE);
   tft.setTextColor(ILI9341_YELLOW,ILI9341_BLUE); //reset colors...
 }//inverted
 else{
 tft.fillRect(tft.width()/2, 80, tft.width()/2,40, ILI9341_BLACK);  
 tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);  
}//normal
      tft.drawRect(tft.width()/2, 80, tft.width()/2,40, ILI9341_BLUE);  //Rh Area 
      tft.setCursor(tft.width()/2+70,90);  //rH% Here? - YES Looks fine (Temp+4px?) 

//No sensor gets a message:      
if( Humidity==0xFF  ){
       tft.print(F("No % rH"));  //  
       tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); //reset colors...
       return;
}
      tft.print(Humidity);     
      tft.print(F("% rH")); 
      
//TODO:  MIN and Max rH% for day calculations and display DONE! V1.12(g)
if (Humidity < MinDayHumid)  MinDayHumid = Humidity; 
if (Humidity >= MaxDayHumid)  MaxDayHumid = Humidity;
   tft.setCursor(tft.width()/2+3,86);  //46+40 below temps
      tft.setTextColor(ILI9341_CYAN,ILI9341_BLACK);  
      tft.setTextSize(1);
      tft.print(F("MAX: "));
      tft.print(MaxDayHumid);
      tft.print(F("%"));
      tft.setCursor(tft.width()/2+3,105);  //65+40 below temps
      tft.setTextColor(ILI9341_ORANGE,ILI9341_BLACK);   
      tft.print(F("min: "));  
      tft.print(MinDayHumid);    
      tft.print(F("%"));
      tft.drawRect(tft.width()/2, 40, 60,80, ILI9341_BLUE);   // Temp+Humid Area 
            
      tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK); //reset colors...
      tft.setTextSize(2); //...and size
} //End Display Humidity


//=============================================================================
// TFT DISPLAY DATA PACKET from Davis ISS weather station
//=============================================================================
void DisplayPacket(void){

//TODO: Display Timestamp of last packet
      DateTime now = RTC.now(); 
//      tft.drawRect(tft.width()/2, 120, tft.width()/2,40, ILI9341_BLUE);  //now BARO Area  S/B RAIN?
//      tft.setCursor(tft.width()/2+8,124);  //Was Baro Here
      tft.setCursor( tft.width()/2+8,225);
      
      tft.setTextSize(1);  //MAKE IT small...
      tft.setTextColor(ILI9341_CYAN,ILI9341_BLACK); 

      if(now.hour()<10) tft.print(F("0"));  //leading zero!
      tft.print(now.hour());
      tft.print(F(":")); 
     if(now.minute()<10) tft.print(F("0"));  //leading zero!
      tft.print(now.minute());
      tft.print(F(":")); 
     if(now.second()<10) tft.print(F("0"));  //leading zero!
      tft.print(now.second()); 
      
//Show how many packets have been received...
      tft.print(F(" Pkts:"));

       tft.print(F("+"));
 //      tft.print(packetStats.packetsReceived);      //packetStats.packetsReceived
       tft.print(packetStats.receivedStreak);
       tft.print(F("    "));  //clear out old chars (up to 4 to the right now) 
       
 //TODO Not sure what to do with missed packets yet....
 //      tft.print(F(" -"));
 //      tft.print(packetStats.packetsMissed);  
       
       tft.setTextSize(2); //Lets reset the text size j/c
/////////////////TEST///////////////////////
#if 1

      if(now.hour()<10) Serial.print(F("0"));  //leading zero!
      Serial.print(now.hour());
      Serial.print(F(":")); 
     if(now.minute()<10) Serial.print(F("0"));  //leading zero!
      Serial.print(now.minute());
      Serial.print(F(":")); 
     if(now.second()<10) Serial.print(F("0"));  //leading zero!
      Serial.print(now.second()); 
      Serial.print(F("  "));
      
    Serial.print(radio.CHANNEL);  
    Serial.print(F(" - Data: "));
    for (byte i = 0; i < DAVIS_PACKET_LEN; i++) {
      if(radio.DATA[i]<0x10) Serial.print(F("0"));
      Serial.print(radio.DATA[i], HEX);
      Serial.print(F("."));
    }        

     Serial.print(F(" RSSI: "));
     Serial.println(radio.RSSI);     
     Serial.print(F(" "));
 
 //     Serial.print(packetStats.receivedStreak);     
    
#endif
 /////////////////TEST/////////////////////// 

}//End DisplayPacket


//=============================================================================
// TFT DISPLAY RADIO INFORMATION from Davis ISS weather station
//=============================================================================
void DisplayRadioData(bool GoodSignal)
{
//will it fit?  NO-Not all but TYPE, CHANNEL and RSSI
//1234567890123456789012  = 17*16 (272 or 136x1)PIXELS
//ISS ID:1 CH:01 -123dB
//
//ISS VOltage status area:
//CAP:1.23V  
//SOL:1.23V 
//BATT: OK/ERR(Flashing)

//TODO: Text Color based on Values 
//TODO: Flash on battery ERR - DONE
//TODO: "It's Dark and my battery is getting low..."
//TODO: RSSI Bars display

  
    tft.drawRect(tft.width()/2, 200, tft.width()/2,40, ILI9341_BLUE);  //RADIO Area
    tft.setTextSize(2);  
    //Change co.or for really bad signal...
    if (GoodSignal)tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
    else tft.setTextColor(ILI9341_RED ,ILI9341_BLACK); 
      
    tft.setCursor(tft.width()/2+8,204);  //Text starts here
    if (radio.DATA[0]<0x10)  tft.print(F("0"));
    tft.print(radio.DATA[0],HEX) ;
            
    tft.print(F(" "));  //Show current channel hop
    if(radio.CHANNEL <10) tft.print(F("0")); //add a leading zero
    tft.print(radio.CHANNEL);
  
    tft.print(F(" "));  //Show Signal Strength
    tft.print(radio.RSSI);
    tft.print(F("dB"));  // Removed extra space

    // Fixes wrap around.  If i put clean up space on all it erases part of wind   
    if (GoodSignal)    tft.print(F(" "));//extra space to clean up longer (low) signal 
     
}
      
//=============================================================================
// TFT DISPLAY STATION ID from Davis ISS weather station
//=============================================================================
// I put this in a call so i could hopefully change and display on the fly
// which ISS I want data from ( listing to ) 
// Currently this gets hard coded during initialisation 
//TODO:  Make this display a dynamic ISS number   -- DONE V1.12

void   DisplayISS()
{
    // station ID - the low order three bits are the station ID.  Station ID 1 on Davis is 0 in this data
   // byte stationId = (radio.DATA[0] & 0x07) + 1;
   
//TODO; Need to fix left hand side of this box...    DONE V1.12(f)

      tft.drawRect(tft.width()/2, 160, tft.width()/2,40, ILI9341_BLUE); //ISS Info area
      tft.setTextSize(2); 
      tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
 //     if(Current_Mode==SET_ISS)  tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); 
      tft.setCursor(tft.width()/2+138,164);   
//      tft.print(RX_STATION_ID);
//      tft.print(TRANSMITTER_STATION_ID);
  ///////////////////////////////////////////////////////////////////
 //////////////////TEST MODE ON TFT////////////////////////////////
/////////////////////////////////////////////////////////////////
      tft.setCursor(tft.width()/2+100,164);   //To the left of "ISS"
      tft.print(Current_Mode);  //Mode for test
      tft.setCursor(tft.width()/2+134,184); // To the left of Station #
      
//Put in the headers:
      tft.setTextSize(1);       
      tft.print(F("ISS") );

  ///////////////////////////////////////////////////////////////////
 //////////////////TEST MODE ON TFT////////////////////////////////
/////////////////////////////////////////////////////////////////
      tft.setCursor(tft.width()/2+95,184); //Same y but over 3 chars looks OK     
      tft.print(F("MOD") );
/////////////////////////////////////////////////////////////////
      tft.setTextSize(2);      
}
//=============================================================================
// TFT DISPLAY RAIN from Davis ISS weather station
//=============================================================================
void   DisplayRainCell()
{
  
//TODO: Use actual rain data.  DONE
//TODO: Calculate Rain Rate DONE
//TODO: Add "Raining" Text  DONE

     tft.drawRect(tft.width()/2, 120, tft.width()/2,40, ILI9341_BLUE);  //old BAR Area
     tft.setTextSize(2); 
     tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
     tft.setCursor(tft.width()/2+8,124);  //Rain today's total
     tft.print(ISS_dayRain/100);
     tft.print(F("\" ") ); 
     
     tft.setTextSize(1); 
     tft.setCursor(tft.width()/2+80,124);  //Rain Rate    
     tft.print(ISS_rainRate); 
     tft.print(F("\"/hr") ); 
 // Use NWS definitions for rain rates. https://en.wikipedia.org/wiki/Precipitation_types
 // LIGHT rain at a rate of between a trace and 0.098 in/hr. 
 // MODERATE rain rate of between 0.10" and 0.30" per hour. 
 // HEAVY rain is rate above 0.30 in/hr     
      tft.setCursor(tft.width()/2+8,145);  //Rain stats 
      tft.print(ISS_TotRain/100);
      tft.print(F("\"   ") ); 
      tft.setCursor(tft.width()/2+80,140);  
      
 // Rain Rate Commentary...     
 //Each message should be 12 chars including spaces...  
 //         
      if (ISS_rainRate==0) tft.print(F("Not Raining") );
//                                    ("12345678901")  Spaces
      else{
      if (ISS_rainRate<.1) tft.print(F("Lite Rain  ") ); 
//                                    ("12345678901")  Spaces      
       else if (ISS_rainRate<.3) tft.print(F(" ~Raining~ "));
//                                          ("12345678901")  Spaces
       else  tft.print(F("Hvy. Rain! ")); 
//                      ("12345678901")  Spaces 
      }
      
}//end DISPLAY RAIN

//=============================================================================
// TFT ISS Battery Status Display (with flashing error!) 
//=============================================================================
void DispISS_Batt_Status()
{
  
            tft.setTextSize(1);          
            tft.setCursor(tft.width()/2+8,185);   //in ISS Volts area
            tft.print(F("BAT:"));
            if(!ISS_isBatteryOk) {
              tft.setTextColor(ILI9341_ORANGE ,ILI9341_BLACK); 
              if (Error_Flash)tft.print(F("ERR"));
              else tft.print(F("   "));
              tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
            }
            if(ISS_isBatteryOk)tft.print(F("OK "));
            tft.setTextSize(2); 
}


  ///////////////////////////////////////////////////////////////////
 //////////////////TEST MODE ON TFT////////////////////////////////
/////////////////////////////////////////////////////////////////
void Display_Mode()
{
      tft.setTextSize(2); 
      tft.setCursor(tft.width()/2+100,164);   //To the left of "ISS"
      tft.print(Current_Mode);  //Mode for test
      tft.setTextSize(1);   
      tft.setCursor(tft.width()/2+95,184); //Same y but over 3 chars looks OK     
      tft.print(F("MOD") );
/////////////////////////////////////////////////////////////////
      tft.setTextSize(2);    
}

void Display_StationID()
{
       tft.setCursor(tft.width()/2+134,184); // To the left of Station #    
       tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK);  
//Put in the header:
      tft.setTextSize(1);       
      tft.print(F("ISS") );
      tft.setTextSize(2); 

      if(Current_Mode==SET_ISS)  tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); 
      tft.setCursor(tft.width()/2+138,164);   
//      tft.print(RX_STATION_ID);
      tft.print(TRANSMITTER_STATION_ID);
      tft.setTextSize(2);    
}
//////////////////////////////////////////////////////////////////////////
/////////// SET and DISPLAY RTC TIME ////////////////////////////////////
/*  V1.12(a)(b)(c)(d)
 * This will display abd change the time  It uses a few helper functions
 * to format the result.  The whole thing is controll by the state
 * variables set by the push button switches.  The downside so far i see
 * is that each +/- will update the RTC.  I don't know if that will be'
 * an issue... 
 */
void DisplaySetTime()
{
     DateTime change = RTC.now();  //Get RTC data 
      tft.setTextSize(2);
bool up = true; 
      
if (Current_Mode == SET_HR) 
  {    
     if(Current_Op == Inc){
     RTC.adjust(DateTime(change.year(), change.month(), change.day(), Update_Hours(change.hour(), true), change.minute(),0));//seconds are zero
     Current_Op = None;
     }
     if(Current_Op == Dec){
     RTC.adjust(DateTime(change.year(), change.month(), change.day(), Update_Hours(change.hour(), false), change.minute(),0));//seconds are zero
     Current_Op = None;
     
     }

      tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); //invert text   
      tft.setCursor(tft.width()/2-24,3); //HOURS here 
      if(change.hour()<10) tft.print(F("0"));  //leading zero!
      tft.print(change.hour());
/*  This is only needed for two directions...      
 //minutes should be normal text....
 //    tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK);
//      tft.setCursor(tft.width()/2,3);  //Colon is smack dab center
//      tft.print(":");   //colon
//     if(change.minute()<10) tft.print(F("0"));  //leading zero!
//     tft.print(change.minute()); 

*/
  }
else if (Current_Mode == SET_MIN)
  {
    if(Current_Op == Inc){
      RTC.adjust(DateTime(change.year(), change.month(), change.day(), change.hour(), Update_Minutes(change.minute(),true),0));//seconds are zero
     Current_Op = None;
     }
     if(Current_Op == Dec){
      RTC.adjust(DateTime(change.year(), change.month(), change.day(), change.hour(), Update_Minutes(change.minute(),false),0));//seconds are zero
     Current_Op = None;
    }

          tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK);  
          //With OK key we are always coming from the left 
          //so hours need to return to normal 
          tft.setCursor(tft.width()/2-24,3); //HOURS here 
          if(change.hour()<10) tft.print(F("0"));  //leading zero!  
          tft.print(change.hour());
  //TODO Not needed with OK key...        
 //         tft.setCursor(tft.width()-110,3); //DATE   here 
 //        if(change.month()<10) tft.print(F("0"));
 //        tft.print(change.month()); 
         tft.setCursor(tft.width()/2,3);  //Colon is smack dab center
         tft.print(F(":"));   //colon
         tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); //invert changing text
         if(change.minute()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.minute());
  }
  
 else if (Current_Mode == SET_MONTH)     
  {
     if(Current_Op == Inc){
     RTC.adjust(DateTime(change.year(), Update_Month(change.month(),true), change.day(), change.hour(), change.minute(),0));//seconds are zero
     Current_Op = None;
     }
     if(Current_Op == Dec){
     RTC.adjust(DateTime(change.year(), Update_Month(change.month(),false), change.day(), change.hour(), change.minute(),0));//seconds are zero
     Current_Op = None;
     
     }
         //un invert minutes always comming from the left with OK key
         tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); //Normal colors on Mins
         tft.setCursor(tft.width()/2,3);  //Colon is smack dab center
         tft.print(F(":"));   //colon
         if(change.minute()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.minute()); 
     
       tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); //invert text
       tft.setCursor(tft.width()-110,3); //MONTH DATE   here 
       if(change.month()<10) tft.print(F("0"));  
       tft.print(change.month()); 
  }

 else if (Current_Mode == SET_DAY)     
  {

     if(Current_Op == Inc){
      RTC.adjust(DateTime(change.year(), change.month(), Update_Day(change.day(),true), change.hour(), change.minute(),change.second()));
     Current_Op = None;
     }
     if(Current_Op == Dec){
     RTC.adjust(DateTime(change.year(), change.month(), Update_Day(change.day(),false), change.hour(), change.minute(),change.second()));
     Current_Op = None;
     
     }
         //un invert month always comming from the left with OK key
         tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); //Normal colors on Mins
         tft.setCursor(tft.width()-110,3); //MONTH DATE   here 
         if(change.month()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.month()); 
         tft.print(F("/"));   // print the slash too
   //OK now we are ready to show we are changing Days by inverting   
         tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); //invert text
         if(change.day()<10) tft.print(F("0"));  
         tft.print(change.day()); 
  }
else if (Current_Mode == SET_YEAR)     
  {
     if(Current_Op == Inc){
     RTC.adjust(DateTime(Update_Year(change.year(),true), change.month(), change.day(), change.hour(), change.minute(),change.second()));
     Current_Op = None;
     }
     if(Current_Op == Dec){
     RTC.adjust(DateTime(Update_Year(change.year(),false), change.month(), change.day(), change.hour(), change.minute(),change.second()));
    Current_Op = None;
     
     }
       //un invert Month, Days and Years always comming from the left with OK key
         tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); //Normal colors on Mins
         tft.setCursor(tft.width()-110,3); //MONTH DATE   here
         if(change.month()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.month()); 
         tft.print(F("/"));   // print the slash posion for DAYS here
         if(change.day()<10) tft.print(F("0"));  
         tft.print(change.day());
         tft.print(F("/"));   // print the right slash too for YRS position
         tft.setTextColor(ILI9341_BLACK ,ILI9341_GREEN); //invert text
         tft.print(change.year()-2000);  //not the century - only the decade

  }

else if (Current_Mode == SET_ISS)  //V1.12(d)
{
  if(Current_Op == Inc) {
    TRANSMITTER_STATION_ID = Update_ISS_ID(TRANSMITTER_STATION_ID, true);
    EEPROM.update(ID_Address, TRANSMITTER_STATION_ID); //Save change for next reboot
  }
  if(Current_Op == Dec) {
    TRANSMITTER_STATION_ID = Update_ISS_ID(TRANSMITTER_STATION_ID, false);
    EEPROM.update(ID_Address, TRANSMITTER_STATION_ID);
  }

  Current_Op = None;
    Display_StationID();
         tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); //Normal colors on Mins
         tft.setCursor(tft.width()-110,3); //MONTH DATE   here
         if(change.month()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.month()); 
         tft.print(F("/"));   // print the slash posion for DAYS here
         if(change.day()<10) tft.print(F("0"));  
         tft.print(change.day());
         tft.print(F("/"));   // print the right slash too for YRS position
         tft.print(change.year()-2000);  //not the century - only the decade

}


   
//now we are done with all modes. Assuming only going to left with OK key. 
//lets put them back to normal.
//the problem is we only know where the date begins so we have to re write
//the whole date to clean it up!   This is default now but will
//ned to change to the next mode...RAIN or CHANNELs    
else {  
       //un invert Month, Days and Years always comming from the left with OK key
         tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); //Normal colors on Mins
         tft.setCursor(tft.width()-110,3); //MONTH DATE   here
         if(change.month()<10) tft.print(F("0"));  //leading zero!
         tft.print(change.month()); 
         tft.print(F("/"));   // print the slash posion for DAYS here
         if(change.day()<10) tft.print(F("0"));  
         tft.print(change.day());
         tft.print(F("/"));   // print the right slash too for YRS position
         tft.print(change.year()-2000);  //not the century - only the decade
         Display_StationID();
      }
}
/////////////////////////////////////////////////////////////////
///////////Helper functions for setting date time///////////////
///////////////////////////////////////////////////////////////

uint8_t Update_Hours(uint8_t Hours, bool increment) 
{
  if(increment) {
    Hours++;
    if(Hours>= 24) Hours = 0; //wrap hours for (=)
    return Hours;
  }
 else {
  if(Hours == 0) {  //wrap hours for (-)
    Hours = 23;
    return Hours;
  }
  Hours--;
 }
  return Hours;
}

uint8_t Update_Minutes(uint8_t Minutes, bool increment) 
{
  if(increment) {
    Minutes++;
    if(Minutes>= 60) Minutes = 0;
    return Minutes;
  }
 else {   
  if(Minutes == 0) {
    Minutes = 59;
    return Minutes;
  }
  Minutes--;
 }
  return Minutes;
}
uint8_t Update_Month(uint8_t Month, bool increment) 
{
  if(increment) {
    Month++;
    if(Month>= 13) Month = 1;
    return Month;
  }
 else {   
  if(Month <= 1) {  //lets keep it positive! 
    Month = 12;
    return Month;
  }
  Month--;
 }
  return Month;
}

uint8_t Update_Day(uint8_t Day, bool increment) 
{
  if(increment) {
    Day++;
    if(Day>= 32) Day = 1;
    return Day;
  }
 else {   
  if(Day <= 1) {  //no 0th day! 
    Day = 31;
    return Day;
  }
  Day--;
 }
  return Day;
}
uint16_t Update_Year(uint16_t Year, bool increment) 
{
  if(increment) {
    Year++;
    if(Year>= 2099) Year = 2020;  //lets don't go back in time
    return Year;
  }
 else {   
  if(Year == 2020) {  //back to the future
    return Year;  //not loop but stop
  }
  Year--;
 }
  return Year;
}

uint8_t Update_ISS_ID(uint8_t ISS, bool increment) 

//      Updates (TRANSMITTER_STATION_ID);
{
  if(increment) {
    ISS++;
    if(ISS>= 8) ISS = 8; //stop at 8
    return ISS;
  }
 else {   
  if(ISS == 0) {  //go scanning
//    ISS = 0; //no 0 ISS! 
    return ISS;
  }
  ISS--;
 }
  return ISS;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////Ancillary functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////// 
void blink(uint8_t PIN, uint16_t DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

////////////////////////////RADIO & PACKET PROCESSING/////////////////////////////////
//

//=============================================================================
// Received data and it passed CRC check.  This function decodes the weather data 
// Every packet contains wind speed, wind direction and battery status
// Packets take turns reporting other data
//=============================================================================
void decodePacket() 
{
  const byte SENSOR_OFFLINE = 0xFF;
    int val;  
  // Flags are set true as each variable comes in for the first time
  static bool gotTempData =     false;
  static bool gotHumidityData = false; 
  static bool gotRainData =     false;
#if VP2
  float       uvi =               0.0;  // UV index
  float       sol =               0.0;  // Solar radiation
#endif 
  uint16_t    tt =                  0;  // Dummy variable for calculations
  uint16_t    rainSeconds =         0;  // seconds between rain bucket tips
  byte        byte4MSN =            0;  // Holds MSB of byte 4 - used for seconds between bucket tips

  // station ID - the low order three bits are the station ID.  Station ID 1 on Davis is 0 in this data
  byte stationId = (radio.DATA[0] & 0x07) + 1;

  //This is an attempt to capture which ISS we are hearing...
 // RX_STATION_ID = stationId;

//Check for SCAN mode...
  if ( TRANSMITTER_STATION_ID !=0){   //ISS 0 is scan mode ( accept any ISS Data)
    
      //Only process the data from one ISS
      if ( stationId != TRANSMITTER_STATION_ID )
       { return; }  // exit this function if this isn't the station ID program is monitoring
  }
  
  // Every packet has wind speed, wind direction and battery status in it
  ISS_windSpeed = radio.DATA[1];  

  // There is a dead zone on the wind vane. No values are reported between 8
  // and 352 degrees inclusive. These values correspond to received byte
  // values of 1 and 255 respectively
  // See http://www.wxforum.net/index.php?topic=21967.50
  //  float windDir = 9 + radio.DATA[2] * 342.0f / 255.0f; - formula has dead zone from 352 to 10 degrees
  if ( radio.DATA[2] == 0 )
  { ISS_windDirection_Now = 0; }
  else 
  { ISS_windDirection_Now = ((float)radio.DATA[2] * 1.40625) + 0.3; }  // This formula doesn't have dead zone, see: http://bit.ly/1uxc9sf
// avgWindDir(ISS_windDirection_Now);  
// Average out the wind direction with vector math...takes some memory leaving out for now 
//TODO: Display average direction?
//   UpdateWindDisplay( ISS_windDirection_Now, ISS_windSpeed, ISS_windgustmph);
//    UpdateWindDisplay( fPoint( ISS_windDirection_Now ), ISS_windSpeed, ISS_windgustmph);
//      Serial.println(ISS_windDirection_Now); 

////////////////////////////////////////////////////////////////
///////Here is where we set the ISS Litium Battery's status        
////// 0 = battery is OK, 1 = battery low.  
///////////////////////////////////////////////////////////////
  if ( ((radio.DATA[0] & 0x8) >> 3) == 0 )
  { ISS_isBatteryOk = true; }
  else
  { ISS_isBatteryOk = false; }
 
  // Look at MSB in first byte to get data type
  switch (radio.DATA[0] >> 4)
  {
  case ISS_OUTSIDE_TEMP:
  //TODO: Check for bad sensor data.  TEMP!=0xFF?
      ISS_outsideTemperature = (int16_t)(word(radio.DATA[3], radio.DATA[4])) >> 4;
      gotTempData = true;  // one-time flag when data first arrives. 
      DisplayTempBox( ISS_outsideTemperature, false); 
 
    break;

  case ISS_HUMIDITY:
    // Round humidity to nearest integer
    ISS_outsideHumidity = (byte) ( (float)( word((radio.DATA[4] >> 4), radio.DATA[3]) ) / 10.0 + 0.5 );
    gotHumidityData = true;  // one-time flag when data first arrives
    DisplayHumidBox(ISS_outsideHumidity, false);
    break;
  
  case ISS_WIND_GUST:
  //This is the 10 minute gust from the ISS
    ISS_windgustmph = radio.DATA[3];
    break;
      
  case ISS_RAIN: 
    ISS_rainCounter = radio.DATA[3];
    if ( ISS_initialRainReading == NO_READING )
    { ISS_initialRainReading = FIRST_READING; } // got first rain reading
    else if ( ISS_initialRainReading == FIRST_READING )
    { ISS_initialRainReading = AFTER_FIRST_READING; } // already had first reading, now it's everything after the first time
    gotRainData = true;   // one-time flag when data first arrives
    
    if(TRANSMITTER_STATION_ID != 0)  //Don't update - the total will be all messed up if it comes in from two stations V1.12
    {
        updateRainAccum();  

    //Debug on serial port
    /*
       Serial.print(ISS_dayRain/100);
       Serial.print(F("\" ") ); 
       Serial.print(ISS_rainRate); 
       Serial.print(F("\"/hr Count:") ); 
       Serial.println(ISS_rainCounter); 
       */  
    DisplayRainCell();   
      }
    break;

  case ISS_RAIN_SECONDS:  // Seconds between bucket tips, used to calculate rain rate.  See: http://www.wxforum.net/index.php?topic=10739.msg190549#msg190549
    byte4MSN = radio.DATA[4] >> 4;
    if ( byte4MSN < 4 )
    { rainSeconds =  (radio.DATA[3] >> 4) + radio.DATA[4] - 1; }  
    else
    { rainSeconds = radio.DATA[3] + (byte4MSN - 4) * 256; }   

   updateRainRate(rainSeconds);
    break;
    //SOLAR    
        case 0x07:
//          Serial.print("SOLAR: ");
          val = (radio.DATA[3] << 2) | (radio.DATA[4] & 0xc0) >> 6;
// for test lets just print it here...
          tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
           tft.setCursor(tft.width()/2+8,165);
           tft.setTextSize(1); 
           tft.print("SOL:");    
           tft.print( (float)(val / 300.0));
           tft.println("V ");
 //          tft.setTextSize(2); 
          
 //         Serial.print( (float)(val / 300.0));
  //        Serial.println(" V ");
         

    break;

        case 0x02:
    //ISS SUPERCAP BACKUP BATTERY
        val = (radio.DATA[3] << 2) | (radio.DATA[4] & 0xc0) >> 6;
// for test lets just print it here...
          tft.setTextColor(ILI9341_GREEN ,ILI9341_BLACK); 
           tft.setCursor(tft.width()/2+8,175);
           tft.setTextSize(1); 
           tft.print("CAP:");    
           tft.print( (float)(val / 300.0));
           tft.print("V ");

           tft.setTextSize(2); 
//Print out for debug TODO - maybe put SDCARD here??    
//          Serial.print("CAP: ");
//          Serial.print( (float)(val / 300.0));
//          Serial.println(" V ");

      break; 
//We are only doing Vu stuff now...i don't have these sensors...  
#if VP2     
  case ISS_SOLAR_RAD:
    if ( radio.DATA[3] != SENSOR_OFFLINE )
    {
      // Calculation source: http://www.wxforum.net/index.php?topic=18489.msg178506#msg178506
      // tt = word(radio.DATA[3], radio.DATA[4]);
      // tt = tt >> 4;
      // sol = (float)(tt - 4) / 2.27 - 0.2488;
      
      sol = (radio.DATA[3] * 4) + ((radio.DATA[3] && 0xC0) / 64 );  // Another source: http://www.carluccio.de/davis-vue-hacking-part-2/
    }
    else
    { sol = 0.0; }
    break;
     
  case ISS_UV_INDEX:
    if ( radio.DATA[3] != SENSOR_OFFLINE )
    {
      // Calculation source: http://www.wxforum.net/index.php?topic=18489.msg178506#msg178506
      tt = word(radio.DATA[3], radio.DATA[4]);
      tt = tt >> 4;
      uvi = (float)(tt-4) / 200.0;
    }
    else
    { uvi = 0.0; }
    break;
#endif
  default:
    break;
  }
  
  // See if all weather data has been received
 
  if ( gotTempData && gotHumidityData && gotRainData )
  { ISS_gotInitialWeatherData = true; }
  
  #ifdef PRINT_DEBUG
    printData(rainSeconds);  // Print data, useful for debuggging
  #endif
  
} //  end decodePacket()




//=============================================================================
// Track daily rain accumulation.  Reset at midnight. 
//TODO: Alarm with RTC for midnight 
// Everything is in 0.01" units of rain
//=============================================================================

void updateRainAccum()

{

  static byte newRain =         0; // incremental new rain since last bucket tip
  static byte prevRainCounter = 0; // previous ISS rain counter value

  // If program has recently restarted, set previous rain counter to current counter
  if ( ISS_initialRainReading == FIRST_READING )
  {  prevRainCounter = ISS_rainCounter; }
  
   // If the ISS rain counter changed since the last transmission, then update rain accumumulation
  if ( ISS_rainCounter != prevRainCounter )

  {
    // See how many bucket tips counter went up.  Should be only one unless it's raining really hard or there is a long transmission delay from ISS
    if ( ISS_rainCounter < prevRainCounter )
    { newRain = (128 - prevRainCounter) + ISS_rainCounter; } // ISS rain counter has rolled over (counts from 0 - 127)
    else
    { newRain = ISS_rainCounter - prevRainCounter; }

    // Increment daily rain counter
    ISS_dayRain += newRain;
    ISS_TotRain += newRain;
    
  }

  prevRainCounter = ISS_rainCounter;
  
    //
   // reset daily rain accumulation
  //  very weird way but should work...
 //
  if ( NewDay )  //this gets set the at 00:00:00
  { ISS_dayRain = 0;
   delay(1000);  /// don't go anywhere for at least 1 sec.
   NewDay = false;
  }

} // end updateRainAccum()




//=============================================================================
// Calculate rain rate in inches/hour
// rainSeconds seconds is sent from ISS.  
// It's the number of seconds since the last bucket tip
//=============================================================================

void updateRainRate( uint16_t rainSeconds )

{

  if ( rainSeconds < 1020 )

  { ISS_rainRate = 36.0 / (float)rainSeconds; }

  else

  { ISS_rainRate = 0.0; }  // More then 15 minutes since last bucket tip, can't calculate rain rate until next bucket tip

  

}  // end updateRainRate()


/* ===============================================================================
 * This will smooth the wind pointer.  The time it takes depnds on the loop delay
 * input: is Direction sent from ISS.
 * output: is intermeiate pointer position
 * ===============================================================================
 */



uint16_t fPoint( uint16_t rawDirector ){

  static  uint16_t filDirector = 0;

// if (rawDirector == 0)  return rawDirector; //dont care if zero
 if (rawDirector == filDirector)  return rawDirector ; //no need to move if same
//now move the point to the raw direction


    
     if (rawDirector<filDirector)  //if incoming direction is less
       { 
         // if ((rawDirector-filDirector)>300 ){  //the other side of the dial 
        //  filDirector = rawDirector; //go ahead and jump
         // return rawDirector;
       //   }
    
        if(filDirector==0)return rawDirector; //should be above zero her but if not its bad
  
        filDirector--;         //head towards CCW
      
        return filDirector;
       
     //end move CCW
       }
       
   if (rawDirector>filDirector){  //if incomming is more
    filDirector++; }//move CW
   //we need to move it
    return filDirector;   //send current step towards out


 } //End fPoint

  //////////////////////////////////////////////////////////////////////
 //#define SDLOG = 1  //rats! We cant use file on this target
//  cant use on ths version...98% + memory used 
////////////////////////////////////////////////////////////////////

#ifdef SDLOG
void logdata() {

  DateTime now = RTC.now();

  String dataString = "";
  dataString += String(now.unixtime());
  dataString += String(";");
  dataString += String(now.year());
  dataString += String("-");
  dataString += String(now.month());
  dataString += String("-");
  dataString += String(now.day());
  dataString += String(" ");
  dataString += String(now.hour());
  dataString += String(":");
  dataString += String(now.minute());
  dataString += String(":");
  dataString += String(now.second());
  dataString += String(",");
  

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
      }

    // print to the serial port too:
    Serial.println(dataString);
 
} 
#endif
