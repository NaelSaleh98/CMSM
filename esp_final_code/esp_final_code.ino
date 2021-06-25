#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "CMSM";
const char* password = "12345678";

const unsigned char Active_buzzer = D5;

const long utcOffsetInSeconds = 10800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(115200); // serial to arduino
  while(!Serial){}      // wait to connect to arduino
  ConnectToWiFi();      // connect to WiFi
  timeClient.begin(); //---------
  pinMode (Active_buzzer,OUTPUT) ;
}

// ----------------------//
void loop() 
{
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    String data = Serial.readString();
    if(data.equals("checkTime"))
    {
      timeClient.update();
      if( (timeClient.getHours() < 6) && (timeClient.getHours() > 18) )
      {
        digitalWrite(Active_buzzer,HIGH) ; //Turn on active buzzer
      }

      String day = daysOfTheWeek[timeClient.getDay()];
      if( ( day.equals("Friday")) || ( day.equals("Saturday") ) )
      {
        digitalWrite(Active_buzzer,HIGH) ; //Turn on active buzzer
      }
    }
    else if(data.equals("turnoffbuzz"))
    {
      digitalWrite(Active_buzzer,LOW) ; //Turn off active buzzer
    }
    else 
    {
      Serial.println(data);
    }
    sendGetRequest(data);
  }
}

// -------------------------//
void ConnectToWiFi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting ");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" .");
  }
  Serial.println("Connected Successfully!");
}

// -------------------------- //
void sendGetRequest(String data)
{
    if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
    { 
      HTTPClient http;  //Declare an object of class HTTPClient
 
      http.begin(data);  //Specify request destination
      int httpCode = http.GET();                                  //Send the request
      if (httpCode > 0) //Check the returning code
      { 
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);             //Print the response payload
      }
      http.end();   //Close connection
    }
    else
    {
      ConnectToWiFi();
    }
}
