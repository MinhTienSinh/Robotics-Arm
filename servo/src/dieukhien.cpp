#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo1, myservo2, myservo3;  // create servo object to control servos
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;   // initial position of the servos

void setup(){
   myservo1.attach(13); // attaches on GPIO 13
   myservo2.attach(12); // attaches on GPIO 12
   myservo3.attach(14); // attaches on GPIO 14

   Serial.begin(115200); // monitor speed
   Serial.setTimeout(10000); // 10 giây

   myservo1.setPeriodHertz(50); // standard 50 hz servo
   myservo2.setPeriodHertz(50); // standard 50 hz servo
   myservo3.setPeriodHertz(50); // standard 50 hz servo

   Serial.println("Servo is ready");
   Serial.println("Use format: s1=90 or s2=45 or s3=120"); // instruction
}

void loop(){

  // check if data is available from Serial
  if (Serial.available()){

     String s = Serial.readStringUntil('\n'); // read 1 line
     s.trim(); // remove spaces / newline

     int servoNum = 0; // servo index (1,2,3)
     int angle = 0;    // input angle

     // read format: s1=90
     if (sscanf(s.c_str(), "s%d=%d", &servoNum, &angle) == 2){

        // check valid angle
        if (angle >= 0 && angle <= 180){

           // control each servo separately
           if (servoNum == 1){
              pos1 = angle;
              myservo1.write(pos1); // move servo 1
              Serial.println("Servo 1 moved to position:");
              Serial.println(pos1);
           }

           else if (servoNum == 2){
              pos2 = angle;
              myservo2.write(pos2); // move servo 2
              Serial.println("Servo 2 moved to position:");
              Serial.println(pos2);
           }

           else if (servoNum == 3){
              pos3 = angle;
              myservo3.write(pos3); // move servo 3
              Serial.println("Servo 3 moved to position:");
              Serial.println(pos3);
           }

           else{
              Serial.println("Invalid servo number (1-3)");
           }
        }

        else{
           Serial.println("Invalid position (0-180 only)");
        }
     }

     else{
        Serial.println("Wrong format! Example: s1=90");
     }
  }
}
