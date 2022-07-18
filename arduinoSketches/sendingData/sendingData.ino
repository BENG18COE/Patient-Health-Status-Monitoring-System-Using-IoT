void setup() {
 void PostingData()                        //Score on screen
{
  //Setting up HTTPClient as http
  HTTPClient http;

  //Naming the WifiClient as client
  WiFiClient client;
  
  //Host to post Data
  String host = "http://monitorsystem.herokuapp.com/sensor/data";
////monitorsystem.herokuapp.com/
///sensor/data/<int:sensorId>/<float:temperature>/<int:heart_rate>

  int nodeNum = NodeNumber;
  float temp = tempC;
  int myBPM = myBPM;

  String serverName = host + "/" + nodeNum + "/" + temp + "/" + myBPM;
  String serverPath = serverName;

  //  Begin HTTP
  http.begin(client, serverPath);

  int httpResponseCode = http.GET();

  String payload = http.getString();
  Serial.println(payload);
  http.end();

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Data Sent");
  delay(2000)
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
