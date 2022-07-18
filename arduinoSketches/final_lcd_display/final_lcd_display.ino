//ADIM
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display



int temperature_data = 36.7;
int heart_rate_data = 90;

//
//float temperature_data = 0;
//float Fahrenheit = 0;

void setup()
{
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
  lcd.print("NODE 01");
  delay(2000);
  //lcd.clear()
}


void loop()
{
  //#####################------ CHECKING SENSOR----#########################
  for (int counter = 0; counter < 6 ; counter++) {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("SYSTEM CHECK");
    lcd.setCursor(0, 1);
    lcd.print("PLEASE WAIT::");

    lcd.print(counter);
    delay(800);

  }
  ///+++++++++++ IF READY READY IF PRINT READY ELSE END THE LOOP BY PRINTING FAILING SENSOR

  //#####################------ TEMPERATURE DATA ----#########################

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.setCursor(6, 0);
  lcd.print(temperature_data);
  lcd.setCursor(10, 0);
  lcd.print("C");


  lcd.setCursor(0, 1);
  lcd.print("HEART: ");
  lcd.setCursor(6, 1);
  lcd.print(heart_rate_data);
  lcd.setCursor(10, 1);
  lcd.print("BPM");
  delay(8000);

  //#####################------ HEART BEAT DATA   ----#########################






}
