#include <Servo.h>
int cap = 2;                                            //Capacitive Sensor Input
int ind = 3;                                            //Inductive Sensor Input
int trigger = 4;                                        //Trigger Signal For Ultrasonic Sensor
int echo = 5;                                           //Echo Signal For Ultrasonic Sensor
int bin = 7;                                            //Servo Motor Output For Bin
int detection = 12;                                     //LED indicator For Object presence
int holder = 8;                                         //Servo Motor Output For Holder
const int Red = 9;
const int Green = 10;
const int Blue = 11;
int angle = 0;                                          //Initializing Angle For Bin
int towrite;                                            //Angle to be written onto bin servo motor 
Servo servo_bin;
Servo servo;
float duration_us, distance_cm;                         //Duration of echo signal and distance of object detected by ultrasonic sensor
const float speed_cm_us = 0.034;                        //cm per microsecond
const float dist_threshold = 20;                        //Start object material analysis when an object is 20cm from the ultrasonic sensor
bool start_analysis = false;                            //Object detected = True, else False

void rgbwrite(int, int, int);
void openlid();
void setup() {
  pinMode(detection, OUTPUT);
  pinMode(bin, OUTPUT);
  pinMode(holder, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(cap, INPUT_PULLUP);
  pinMode(ind, INPUT_PULLUP);
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  servo_bin.attach(bin);
  servo.attach(holder);
  servo_bin.write(0);
  servo.write(0);
  digitalWrite(detection, LOW);
  Serial.begin(9600);
}

void loop() {
  //Infinite loop to search for incoming user
  while (!start_analysis) {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    
    duration_us = pulseIn(echo, HIGH);
    distance_cm = (speed_cm_us*duration_us)/2;
    
    delay(250);
    if (distance_cm <= dist_threshold) {
      Serial.print("Distance detected: ");
      Serial.println(distance_cm);
      Serial.println("Object detected!!!");
      digitalWrite(detection, HIGH);
      delay(3000);
      
      start_analysis = true;
    }
    delay(1000);
  }

  delay(3000);

  //Start analyse material
  int c, in;
  c = digitalRead(cap);
  in = digitalRead(ind);

  delay(100);
  Serial.print("Cap: ");
  Serial.println(c);
  Serial.print("Ind: ");
  Serial.println(in);
  Serial.print("Current bin angle: ");
  Serial.println(angle);
  
  delay(500);

  //-------------------------------------START BIN SELECTION-----------------------------//
  if (in==0) {
    rgbwrite(0, 255, 0);
    towrite = 90;
    Serial.println("Metal detected!");


  //--------------------------------------BIN ROTATE-------------------------------//


    switch (angle) {
      case 0: 
        for (int i=0; i<towrite; i++) {
          angle++;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      case 90:
        if (towrite > 90) {
          for (int i = 90; i<towrite; i++) {
            angle++;
            servo_bin.write(angle);
            delay(28);
          }
        }
        else {
          for (int i = 90; i>towrite; i--) {
            angle--;
            servo_bin.write(angle);
            delay(28);
          } 
        }
        break;
      case 180:
        for (int i=180; i>towrite; i--) {
          angle--;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      default: 
        break;
    }

    
  //--------------------------------BIN ROTATE ENDS-------------------------------//

  }
  else if (c==0) {
    rgbwrite(255, 0, 0);
    towrite = 0;
    Serial.println("Paper or other material detected!");


  //--------------------------------BIN ROTATE-----------------------------------//

  
    switch (angle) {
      case 0: 
        for (int i=0; i<towrite; i++) {
          angle++;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      case 90:
        if (towrite > 90) {
          for (int i = 90; i<towrite; i++) {
            angle++;
            servo_bin.write(angle);
            delay(28);
          }
        }
        else {
          for (int i = 90; i>towrite; i--) {
            angle--;
            servo_bin.write(angle);
            delay(28);
          } 
        break;
        }
      case 180:
        for (int i=180; i>towrite; i--) {
          angle--;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      default: 
        break;
    }


  //--------------------------------BIN ROTATE ENDS-------------------------------//


  }

  else {
    
    rgbwrite(0, 0, 255);
    towrite = 180;
    Serial.println("Water bottle, plastic bag or other unidentified object detected!");


  //--------------------------------BIN ROTATE-----------------------------------//

  
    switch (angle) {
      case 0: 
        for (int i=0; i<towrite; i++) {
          angle++;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      case 90:
        if (towrite > 90) {
          for (int i = 90; i<towrite; i++) {
            angle++;
            servo_bin.write(angle);
            delay(28);
          }
        }
        else {
          for (int i = 90; i>towrite; i--) {
            angle--;
            servo_bin.write(angle);
            delay(28);
          } 
        }
        break;
      case 180:
        for (int i=180; i>towrite; i--) {
          angle--;
          servo_bin.write(angle);
          delay(28);
        }
        break;
      default: 
        break;
    }


  //--------------------------------BIN ROTATE ENDS-------------------------------//

  }

  //--------------------------------BIN SELECTION ENDS---------------------------------//

  delay(4000);
  //--------------------------------HOLDER OPEN-----------------------------------//

  openlid();

  //--------------------------------HOLDER CLOSE----------------------------------//
  start_analysis = false;
  digitalWrite(detection, LOW);
  delay(3000);

}

void openlid() {
  servo.write(90);
  delay(3000);
  servo.write(0);
}

void rgbwrite(int r, int g, int b) {
  analogWrite(Red, r);
  analogWrite(Green, g);
  analogWrite(Blue, b);
}
