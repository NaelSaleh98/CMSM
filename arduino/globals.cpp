 #include "Arduino.h"
#include "globals.h"
#include "ultrasonic.h"
#include "lcd.h"
#include "esp.h"


 int numberOfVisitors = 0;
 
 Buzzer buzzer(2);
 
 void checkinSound()
 {
    buzzer.begin(0);
    buzzer.sound(NOTE_A8, 100);
    buzzer.sound(NOTE_B8, 100);
    buzzer.sound(NOTE_C8, 100);
    buzzer.sound(NOTE_D8, 100);
    buzzer.sound(NOTE_E8, 100);
    buzzer.end(500);
 }

 void checkVisitorDistance()
 {
  for (int i = 0; i< ANTIQUE_COUNT; i++)
  {
    if( distance[i] <= 10 )
    {
      Serial1.print("checkTime");
      delay(2000);
    }
    
    if ( (distance[i] <= 10) && (distance[i] > 5) )
    {
      Lcd.clear();
      delay(500);
      Lcd.print("Warning");
      Lcd.setCursor(0,1);
      Lcd.print("Forbidden area!");
      delay(500);
    }
    else if ( distance[i] <= 5 )
    {
       String requet = "UnauthorizedAccess/";
       requet.concat(i+1);
       Serial.println(requet);
       SendRequestToESP(requet);
       delay(2000);
    }
  }
 }
