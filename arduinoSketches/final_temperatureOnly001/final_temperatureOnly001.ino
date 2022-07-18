// Include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//The LCD address and size.
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Data wire is plugged into port 2 on the Arduino

//GLOBAL VARIABLE
#define ONE_WIRE_BUS D3 //pin for temperature sensor

boolean isRead = true;
int NodeNumber = 1;
//oneWire instance to communicate with any OneWire devices:
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
   $$$$$$------- SETUP FUNTION-------$$$$$
*/
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  //Start up the library

  sensors.begin();
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" HEALTH MONITOR ");
  lcd.setCursor(0, 1);
  lcd.print("     SYSTEM     ");
  delay(5000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(4, 1);
  lcd.print("NODE: ");
  lcd.setCursor(10, 1);
  lcd.print(NodeNumber);
  delay(2000);
  lcd.clear();
}
/*
   Main function, get and show the temperature
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  // After we got the temperatures, we can print them here.
  // We use the function ByIndex,since there only 01.
  float tempC = sensors.getTempCByIndex(0);
  //#########------ TEMPERATURE DATA AND HEART RATE  ----##############
  // Check if temp reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature is: ");
    Serial.println(tempC);
    delay(500);


    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.setCursor(6, 0);
    lcd.print(tempC);
    lcd.print((char)223);
    lcd.print("C");
    //    lcd.print(" | ");
    //    lcd.print(DallasTemperature::toFahrenheit(tempC));
    //    lcd.print(" F");
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SENSOR CHECKING");
    lcd.setCursor(5, 1);
    lcd.print("READING");

    delay(800);
    lcd.clear();
    Serial.println("Error: Could not read temperature data");
  }
}
