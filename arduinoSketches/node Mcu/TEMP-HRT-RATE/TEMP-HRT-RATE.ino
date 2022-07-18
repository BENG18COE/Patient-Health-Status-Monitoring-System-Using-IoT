
//==================ADIM
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

#define USE_ARDUINO_INTERRUPTS true //--> Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> //--> Includes the PulseSensorPlayground Library. 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
//GLOBAL VARIABLE
#define ONE_WIRE_BUS D3 //pin for temperature sensor

boolean noErrors = true;
int NodeNumber = 1;
//oneWire instance to communicate with any OneWire devices:
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);



//----------------------------------------Variable Declaration
const int PulseWire = A0; //--> PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED_3 = 5; //--> LED to detect when the heart is beating. The LED is connected to PIN 3 on the Arduino UNO.
int Threshold = 550; //--> Determine which Signal to "count as a beat" and which to ignore.
//--> Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
//--> Otherwise leave the default "550" value.
//----------------------------------------

//----------------------------------------Draw "Heart" on LCD.
byte heart1[8] = {B11111, B11111, B11111, B11111, B01111, B00111, B00011, B00001};
byte heart2[8] = {B00011, B00001, B00000, B00000, B00000, B00000, B00000, B00000};
byte heart3[8] = {B00011, B00111, B01111, B11111, B11111, B11111, B11111, B01111};
byte heart4[8] = {B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11111};
byte heart5[8] = {B00011, B00111, B01111, B11111, B11111, B11111, B11111, B11111};
byte heart6[8] = {B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11110};
byte heart7[8] = {B11000, B10000, B00000, B00000, B00000, B00000, B00000, B00000};
byte heart8[8] = {B11111, B11111, B11111, B11111, B11110, B11100, B11000, B10000};
//----------------------------------------

int Instructions_view = 500; //--> Variable for waiting time to display instructions on LCD.

PulseSensorPlayground pulseSensor; //--> Creates an instance of the PulseSensorPlayground object called "pulseSensor"

/*
  $$$$$$------- SETUP FUNTION-------$$$$$
*/
//--------------------------------------------------------------------------------void setup
void setup() {
  Serial.begin(9600);//--> Set's up Serial Communication at certain speed.
  Serial.println("ADIM TEMPERATURE AND HEART RATE MONITOR");
  sensors.begin();
  lcd.init();                      // initialize the lcd\
  // Print a message to the LCD.
  lcd.backlight();

  //----------------------------------------Create a custom character (glyph) for use on the LCD
  lcd.createChar(1, heart1);
  lcd.createChar(2, heart2);
  lcd.createChar(3, heart3);
  lcd.createChar(4, heart4);
  lcd.createChar(5, heart5);
  lcd.createChar(6, heart6);
  lcd.createChar(7, heart7);
  lcd.createChar(8, heart8);
  //----------------------------------------

  lcd.setCursor(0, 0);
  lcd.print(" HEALTH MONITOR ");
  lcd.setCursor(0, 1);
  lcd.print("     SYSTEM     ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(4, 1);
  lcd.print("NODE: ");
  lcd.setCursor(10, 1);
  lcd.print(NodeNumber);
  //----------------------------------------Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED_3); //--> auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  //----------------------------------------
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("WELCOME");
    lcd.setCursor(4, 1);
    lcd.print("NODE: ");
    lcd.setCursor(10, 1);
    lcd.print(NodeNumber);
  //----------------------------------------Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
    //--> This prints one time at Arduino power-up,  or on Arduino reset.

    Serial.println("We created a pulseSensor Object !");

    
  }
  else {
//    noErrors = false;
  Serial.println("No pulse ON Sensor HR");
  }
  //----------------------------------------

  delay(2000);
  lcd.clear();
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------void loop
void loop() {
  if (noErrors) {
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");

    int myBPM = pulseSensor.getBeatsPerMinute(); //--> Calls function on our pulseSensor object that returns BPM as an "int". "myBPM" hold this BPM value now.
    float tempC = sensors.getTempCByIndex(0);// We use the function ByIndex,since there only 01.
    //----------------------------------------Condition if the Sensor does not detect the heart rate / the sensor is not touched.
    if (Instructions_view < 500) {
      Instructions_view++;
    }


    if (Instructions_view > 499) {
      lcd.setCursor(0, 0);
      lcd.print("PUT YOUR FINGER");
      lcd.setCursor(3, 1);
      lcd.print("ON HOLDER");
      delay(1000);
      lcd.clear();
      delay(500);
    }
    //----------------------------------------

    //----------------------------------------Constantly check on and beat and temperature".
    if (pulseSensor.sawStartOfBeat() || tempC != DEVICE_DISCONNECTED_C ) { //--> If test is "true", then the following conditions will be executed.
      Serial.println("♥  A HeartBeat Happened ! ");
      //--> Print a message "a heartbeat happened".
      delay(1500);
      clearLCDLine(1,9);
      Serial.print("BPM: "); //--> Print phrase "BPM: "
      Serial.println(myBPM); //--> Print the value inside of myBPM.
      Serial.print("Temperature is: ");
      Serial.println(tempC);
      

      //----------------------------------------Displays a "Heart" shape on the LCD.
      lcd.setCursor(1, 1);
      lcd.write(byte(1));
      lcd.setCursor(0, 1);
      lcd.write(byte(2));
      lcd.setCursor(0, 0);
      lcd.write(byte(3));
      lcd.setCursor(1, 0);
      lcd.write(byte(4));
      lcd.setCursor(2, 0);
      lcd.write(byte(5));
      lcd.setCursor(3, 0);
      lcd.write(byte(6));
      lcd.setCursor(3, 1);
      lcd.write(byte(7));
      lcd.setCursor(2, 1);
      lcd.write(byte(8));
      //----------------------------------------

      //----------------------------------------Displays the BPM  AND TEMPERATURE
      lcd.setCursor(5, 0);
      lcd.print("TEM:");
      lcd.setCursor(9, 0); //Eg tempC = 36.6;
      lcd.print(tempC);
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(5, 1);
      lcd.print("HTR:");
      lcd.setCursor(9, 1);
      lcd.print(myBPM);
      lcd.setCursor(13, 1);
      lcd.print("BPM");
      //----------------------------------------

      Instructions_view = 0;
    }
    //----------------------------------------

    delay(20); //--> considered best practice in a simple sketch.
  }
  else {

    lcd.setCursor(0, 0);
    lcd.print("SENSOR ERRORS");
    lcd.setCursor(4, 1);
    lcd.print("RESTART");
    delay(200);
  }
}



void clearLCDLine(int row, int col) {
  for (int n = col; n < 16; n++) { // 20 indicates symbols in line. For 2x16 LCD write - 16
    lcd.setCursor(n, row);
    lcd.print(" ");
  }
  lcd.setCursor(col, row);
  delay(500);// set cursor in the beginning of deleted line
}
//--------------------------------------------------------------------------------
//===============================================================================================
