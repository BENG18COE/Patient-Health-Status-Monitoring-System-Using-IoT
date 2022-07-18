#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);

// WiFi parameters
const char* ssid = "Mbarikiwa";
const char* password = "1234567890";

boolean buttonFalse;
boolean buttonRight;
boolean buttonUnknown;

//Verb forms: PS Past Simple - PP Part Participle - T Translation
String topQuestions[] = {"Umepata huduma sahihi?", "Umeridhika na huduma uliopata?", "Umeombwa rushwa?"};

int maxNumQuestions = 3;
int NumQuestions = 0;

int questionNumber[] = {1, 2, 3};    //1 is correct - 0 is wrong

int answersArray[4];


void setup()
{
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D8, INPUT);

  //  Initiate Serial Communication at Baud rate of 9600
  Serial.begin(9600);

  Wire.begin(D3, D4);

  // initializing the LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");

  lcd.setCursor(14, 0);
  lcd.print(ssid);
  delay(3000);
  lcd.clear();

  //  Begin Connecting to Wifi with the given ssid and password
  WiFi.begin(ssid, password);

  // Checking wether the Device is connected to Network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }

  delay(3000);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("WiFi connected");
  delay(2000);

  lcd.clear();

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Mfumo wa kutoa maoni");
  delay(3000);
  lcd.clear();
}


void getAnswers(int question, int answer) {
  if (answer == 1) {
    answersArray[NumQuestions] = answer;
    delay(500);
  }

  if (answer == 2) {
    answersArray[NumQuestions] = answer;
    delay(500);
  }

  if (answer == 3) {
    answersArray[NumQuestions] = answer;
    delay(500);
  }
  lcd.clear();
}

void showScore()                        //Score on screen
{
  //Naming the HTTPClient as http
  HTTPClient http;

  //Naming the WifiClient as client
  WiFiClient client;
  
  //Host to post Data
  String host = "http://surverysys2022.herokuapp.com/data";

  int qn1 = answersArray[0];
  int qn2 = answersArray[1];
  int qn3 = answersArray[2];

  String serverName = host + "/" + qn1 + "/" + qn2 + "/" + qn3;
  String serverPath = serverName;

  //  Begin HTTP
  http.begin(client, serverPath);

  int httpResponseCode = http.GET();

  String payload = http.getString();
  Serial.println(payload);
  http.end();

  lcd.clear();
  lcd.setCursor(1, 1);

  lcd.print("Ahsante karibu tena");
}


void loop()
{
  buttonRight = digitalRead(D5);         //True button
  buttonFalse = digitalRead(D6);         //False button
  buttonUnknown = digitalRead(D8);       // Unknown button

  int questionNum = questionNumber[NumQuestions];

  if (NumQuestions != maxNumQuestions)
  {
    //Display question number
    lcd.setCursor(5, 0);
    lcd.print("Swali la ");

    lcd.setCursor(14, 0);
    lcd.print(questionNum = questionNumber[NumQuestions]);

    //    Display the Question
    lcd.setCursor(0, 1);
    lcd.print(topQuestions[NumQuestions]);

    if (buttonRight == HIGH)                     //if True button is clicked
    {
      getAnswers(questionNum, 1);
      NumQuestions++;
    }

    if (buttonFalse == HIGH)                     //if False button is clicked
    {
      getAnswers(questionNum, 3);
      NumQuestions++;
    }

    if (buttonUnknown == HIGH) {          //if Unknown button is clicked
      getAnswers(questionNum, 2);
      NumQuestions++;
    }
  }

  if (NumQuestions == maxNumQuestions)            //3 questions solved?
  {
    showScore();
    delay(5000);
    ESP.restart();
  }

}
