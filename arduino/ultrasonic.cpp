#include "Arduino.h"
#include "ultrasonic.h"

/*
 * Variabls.
 */
  int distance [ANTIQUE_COUNT];
  unsigned long US_Start [ANTIQUE_COUNT];
  unsigned long US_End [ANTIQUE_COUNT];

/*
 * Set Ultrasonic Pins Mod
 */
  void setUltraSonicPinsMod()
  {
    for (int i = 0; i < ANTIQUE_COUNT; i++)
    {
        pinMode(PIN_US_TRIG[i], OUTPUT); // Sets the trigPin as an Output
        pinMode(PIN_US_ECHO[i], INPUT); // Sets the echoPin as an Input
        distance[i] = 0;
        US_Start[i] = 0;
        US_End[i] = 0;
    }
    Serial.println("Ultrasonic pins set successfully.");
    delay(500);
  }

/*
 * Get distance from ultrasonic sensor.
 */
  int getDistance(int trigPin , int echoPin)
  {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    return duration*0.034/2;
  }

/*
 * Get time that visitor spent on staring on antiaue.
 */
  unsigned long getVistorTime(int distance, unsigned long *US_Start, unsigned long *US_End)
  {
    unsigned long visitorTime = 0;
    /*
     * Come for first time.
     */
    if( (distance <=  DISTANCE_THRESHOLD) && (*US_Start == 0) )
    {
      *US_Start = millis();
    }

    /*
     * Visitor was here and gone.
     */
    if( (distance > DISTANCE_THRESHOLD) && (*US_Start != 0))
    {
      *US_End = millis();
    }

    /*
     * return time.
     */
    if ( (*US_End != 0) && (*US_Start != 0) )
    {
      if (*US_End > *US_Start)
      {
        visitorTime = *US_End - *US_Start;
        *US_End = 0;
        *US_Start = 0;
      }
      else 
      {
        *US_End = 0;
        *US_Start = 0;
      }
    }
    return visitorTime / 1000;
  }
