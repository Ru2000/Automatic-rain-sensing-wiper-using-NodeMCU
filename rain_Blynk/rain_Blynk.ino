

/* Connection pins:
Arduino     Rain Sensor
  A0         Analog A0
  5V           VCC
  GND          GND
*/

#include <Servo.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = " Authentication code ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSid of newtwork";
char pass[] = "password of network";

//servo
Servo servo;

BlynkTimer timer;
float vref = 3.3;
float resolution = vref/1023;
const int sensor_pin = D0;
float sensorReading ;


void setup() {
  Serial.begin(9600);  
  servo.attach(5); //D1
    servo.write(0);
    delay(2000);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void myTimerEvent()
{
 
 sensorReading = ( 100.00 - ( (analogRead(A0)/1024.00) * 100.00 ) );
  Blynk.virtualWrite(V5, sensorReading);
   Serial.print("Rain(in Percentage) = ");
  Serial.print(sensorReading);
  Serial.println("%");
  if (sensorReading>30&&sensorReading<50) {
    servo.write(180);
    delay(1000);
    servo.write(0);
    delay(1000);
  }
  else if(sensorReading>50){
    servo.write(180);
    delay(500);
    servo.write(0);
    delay(500);
  }

}





void loop() {
 Blynk.run();
  timer.run(); // Initiates BlynkTimer
  }
   
