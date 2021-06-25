#include "globals.h"
#include "esp.h"
#include "ultrasonic.h"
#include "lcd.h"
#include "rfid.h"

void setup() 
{
  Serial.begin(115200);
  ConnectToESP(); // Connect To ESP on TX1 and RX1. //
  setUltraSonicPinsMod(); // Set Ultrasonic Pins Mod and do Initialization. //
  LcdInit();  // Begin communication with LCD //
  Rfid.init();  // Initialize RFID //
  Serial.println("Welcome to CMSM");
}

// Card UID: D9 DD AA 13 --> White card
// Card UID: FB 86 9F 0D --> Blue Card

void loop()
{
  unsigned long vTime [ANTIQUE_COUNT];
  String RfidTag = Rfid.readTag();
  if(RfidTag != "")
  {
    checkinSound();
    //Serial.print("UID: ");
    //Serial.println(RfidTag);
    bool newVisitor = checkVisitor(RfidTag);
    showNextPosition();
  }
  
  for (int i=0; i<ANTIQUE_COUNT; i++)
  {
      distance[i] = getDistance(PIN_US_TRIG[i], PIN_US_ECHO[i]);  // get distance of visitor. //
      vTime[i] = getVistorTime(distance[i], &US_Start[i], &US_End[i]); // get vistor time. //
      if(vTime[i] >0)
      {
        String Antique = ANTIQIES[i];
        Serial.print(Antique + " Visitor Time: ");
        Serial.println(vTime[i]);
        Antique += "/";
        Antique.concat(vTime[i]);
        Antique = "antique/" + Antique;
        SendRequestToESP(Antique);  // Send Request To ESP And Then To server. //
      }
  }
  checkVisitorDistance();
  //Serial.println("------------------------");
}
