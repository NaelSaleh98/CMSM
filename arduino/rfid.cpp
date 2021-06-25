#include "Arduino.h"
#include "globals.h"
#include "rfid.h"
#include "lcd.h"
#include "ultrasonic.h"
#include "esp.h"

CmsmVisitor* Visitors = new CmsmVisitor[MAX_VISITORS];

bool checkVisitor(String RfidTag)
{
   for(int i = 0; i< MAX_VISITORS; i++)
    {
      if(Visitors[i].tagId == RfidTag){
        Serial.println("Visitor Exist");
        Serial1.print("turnoffbuzz");
        return false;
      }
    }
    for(int i = 0; i< MAX_VISITORS; i++)
    {
      if(Visitors[i].tagId == ""){
        Visitors[i] = CmsmVisitor(RfidTag);
        Visitors[i].setVisited(0);    
        Serial.println("New Visitor.");
        numberOfVisitors++;
        String requet = "visitorscount/";
        requet.concat(numberOfVisitors);
        Serial.println(requet);
        SendRequestToESP(requet);
        return true;
      }
    }
}

void showNextPosition()
{
    if(distance[1] > DISTANCE_THRESHOLD)
    {
          LcdNextPosition(2); // print next position on LCD for the visitor. //
    }
    else if(distance[2] > DISTANCE_THRESHOLD)
    {
          LcdNextPosition(3); // print next position on LCD for the visitor. //
    }
    else 
    {
          LcdNextPosition(2); // print next position on LCD for the visitor. //
    }  
}
