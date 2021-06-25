/*
 * Constants.
 */
 const int ANTIQUE_COUNT = 3;
 const String ANTIQIES[ANTIQUE_COUNT] = {"Antique-1", "Antique-2", "Antique-3"};
 const int DISTANCE_THRESHOLD = 20;

/*
 * Variabls.
 */
 extern int distance [ANTIQUE_COUNT];
 extern unsigned long US_Start [ANTIQUE_COUNT];
 extern unsigned long US_End [ANTIQUE_COUNT];

/*
 * Pins Config.
 */
 const int PIN_US_TRIG[ANTIQUE_COUNT] = {35 , 33 , 31};
 const int PIN_US_ECHO[ANTIQUE_COUNT] = {34 , 32 , 30};

/*
 * Set Ultrasonic Pins Mod.
 */
 void setUltraSonicPinsMod();

/*
 * Get distance from ultrasonic sensor.
 */
 int getDistance(int trigPin , int echoPin);

/*
 * Get time that visitor spent on staring on antiaue.
 */
 unsigned long getVistorTime(int distance, unsigned long *US_Start, unsigned long *US_End);
