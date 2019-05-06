
#include <NewPing.h>
#define m1 9
#define m11 8
#define m2 4
#define m22 3
#define SONAR_NUM     3 
#define MAX_DISTANCE 50
#define PING_INTERVAL 33 

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = { // Sensor object array.
  
  NewPing(11,10, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(5,6, MAX_DISTANCE),
  NewPing(7,12, MAX_DISTANCE),

};

void setup() {
  pinMode(m1,OUTPUT);
  pinMode(m11,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m22,OUTPUT);
  Serial.begin(115200);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1)
      oneSensorCycle();// Sensor ping cycle complete, do something with the results.
      { if (cm[0]==0&&cm[1]==0&&cm[2]==0)
  {lrotate();}
   else if(cm[0]>0&&cm[1]==0&&cm[2]==0)
  {stop1();
  delay(10);
  if(cm[0]>0&&cm[1]==0&&cm[2]==0)
    {forward();
    delay(100);}
    else
    {rrotate();
    delay(20);}
    }
else if(cm[0]>0&&cm[1]>0&&cm[2]==0) 
{stop1();
}
else if(cm[0]>0&&cm[1]==0&&cm[2]>0)
{stop1();
}
else if(cm[0]==0&&cm[1]>0&&cm[2]>0)
{stop1();}
else if(cm[0]==0&&cm[1]>0&&cm[2]==0)
{lrotate();
}
else if(cm[0]==0&&cm[1]==0&&cm[2]>0)
{rrotate();
}
else if(cm[0]>0&&cm[1]>0&&cm[2]>0) 
{stop1();}}
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
    
  }
  // The rest of your code would go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
 /**/ 
}
void forward()
{ Serial.println("forward");
digitalWrite(m1,HIGH);
digitalWrite(m11,LOW);
digitalWrite(m2,HIGH);
digitalWrite(m22,LOW);}
void lrotate()
{ Serial.println("left");
digitalWrite(m1,LOW);
digitalWrite(m11,LOW);
digitalWrite(m2,HIGH);
digitalWrite(m22,LOW);
}
void rrotate()
{ Serial.println("right");
digitalWrite(m1,HIGH);
digitalWrite(m11,LOW);
digitalWrite(m2,LOW);
digitalWrite(m22,LOW);}
void stop1()
{ Serial.println("stop");
digitalWrite(m1,LOW);
digitalWrite(m11,LOW);
digitalWrite(m2,LOW);
digitalWrite(m22,LOW);}
