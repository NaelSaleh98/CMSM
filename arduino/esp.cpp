#include "Arduino.h"
#include "esp.h"

/*
 * Connect To ESP
 */
 void ConnectToESP()
 {
    Serial1.begin(115200);
    Serial.print("Connect To ESP");
    while (!Serial1)
    {
      Serial.println(".");
    }
    Serial.println(" . Connected Successfully");
    delay(500);
 }

/*
 * Send Request To ESP And Then To server
 */
 void SendRequestToESP(const String& request)
 {
    Serial1.println(URL + request);
    delay(500);
    Serial.println("New Request Sent.");
 }

 
