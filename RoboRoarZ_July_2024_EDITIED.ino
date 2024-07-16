#include "HUSKYLENS.h"          // Library for HuskyLens
#include <smorphi_single.h>            // Library for Smorphi
#include "SoftwareSerial.h"     // Library for Software Serial

Smorphi_single my_robot;
HUSKYLENS huskylens;
//SoftwareSerial myHuskySerial(26, 27);
SoftwareSerial myHuskySerial(16, 17);

// please dont change this
#define straightSpeed 70
#define leftSpeed 300
#define rightSpeed 300
#define angV 80
#define speedBoost 100
#define the180Speed 290 //unused

// dont change this else we cooked
int right_sensor_status = my_robot.module1_sensor_status(4);
int bottom_right_sensor_status = my_robot.module1_sensor_status(2);
int left_sensor_status = my_robot.module1_sensor_status(10);
int bottom_left_sensor_status = my_robot.module1_sensor_status(0);

bool isGoingStraight = 0;
bool isGoingLeft = 0;
bool isGoingRight = 0;
bool is180ing = 0;
bool isSpeedBoost = 0;
// int is180flipStatus  = 0;
unsigned long startTime = 0;
unsigned long detectTime = 0;

int color_signature;
int command_block;

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  myHuskySerial.begin(9600);                  //Baud rate for HuskyLens communication. Can change from GUI of the HuskyLens
  my_robot.BeginSmorphi_single();
  while (!huskylens.begin(myHuskySerial)) {
      Serial.println(F("Begin failed!"));
      delay(100);
  }
  my_robot.BeginSmorphi_single();
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  
// DO NOT DELETE / COMMENT THESE LINES !!!!
  red_on();
  delay(1000);
  led_off();
  green_on();
  delay(1000);
  led_off();
  blue_on();
  delay(1000);
  led_off();
  white_on();
  delay(1000);
  
}

void loop() {
  Serial.println("isGoingStraight " + isGoingStraight);
  Serial.println("isSpeedBoost " + isSpeedBoost);
  // DO NOT DELETE / COMMENT THESE LINES !!!!
  int x = 0;
  if (huskylens.request()) {
    if (huskylens.available())  {
          // HUSKYLENSResult result = huskylens.read();
          // Serial.println(F("###########"));
          HUSKYLENSResult result = huskylens.read();
          printResult(result);
          if (result.command == COMMAND_RETURN_BLOCK) {
            x=result.ID;
          }
    }
  }else{
    Serial.println("Error!");
  }

  if ((isGoingLeft || isGoingRight) && ((millis() - startTime) > 5000)) {
    isGoingStraight = 0;
    isGoingRight = 0;
    isGoingLeft = 0;
    isSpeedBoost = 1; // VROOM. GAS GAS GAS
    detectTime = millis();
    led_off();
    // if (is180flipStatus == 1) {
    //   is180flipStatus = 2;
    // }
    // if (is180flipStatus > 1)
    // {
    //   digitalWrite(27, HIGH);
    //   digitalWrite(26, HIGH);
    // }
  }
  else if (isGoingStraight && ((millis() - startTime) > 3500))
  {
    isGoingStraight = 0;
    isGoingRight = 0;
    isGoingLeft = 0;
    is180ing = 0;
    isSpeedBoost = 0; // speedboost turns off with the 180 part regardless of any turns
    led_off();
  }
  else if (is180ing && ((millis() - startTime) > 3430)) {
    isGoingStraight = 0;
    isGoingRight = 0;
    isGoingLeft = 0;
    is180ing = 0;
    // is180flipStatus = 1;
    led_off();
  }
  // check for speedboost; turn it off after X seconds
  if (isSpeedBoost && ((millis() - detectTime) > 2000)) {
    isSpeedBoost = 0;
  }
  
  switch (x){
    case 1:
      red_on();
      break;
    case 2:
      green_on();
      break;
    case 3:
      blue_on();
      break;
    case 4:
      // LEFT
      led_off();
      digitalWrite(25, HIGH);
      digitalWrite(26, HIGH);
      isGoingLeft = 1;
      isGoingRight = 0;
      isGoingStraight = 0;
      is180ing = 0;
      startTime = millis();
      break;
    case 5:
      // FORWARD + BOOST
      led_off();
      digitalWrite(27, HIGH);
      digitalWrite(26, HIGH);
      isGoingStraight = 1;
      isSpeedBoost = 1; // FOR THE FORWARD PART near the 180 segment
      isGoingRight = 0;
      isGoingLeft = 0;
      is180ing = 0;
      startTime = millis();
      break;
    case 6:
      //RIGHT
      led_off();
      digitalWrite(27, HIGH);
      digitalWrite(25, HIGH);
      isGoingRight = 1;
      isGoingLeft = 0;
      isGoingStraight = 0;
      is180ing = 0;
      startTime = millis();
      break;
    case 7:
      // round and round we go 
      white_on();
      isGoingRight = 0;
      isGoingLeft = 0;
      isGoingStraight = 0;
      is180ing = 1;
      startTime = millis();
      detectTime = millis();
      break;
    case 8:
      // NOTHING 
      break;
    case 9:
      // NOTHING
      break;
    default:
      1==1;  //DUMMY COMMAND (CAN IGNORE)
  }
  sensor_initialisation();
}


void printResult(HUSKYLENSResult result){

  // DO NOT DELETE / COMMENT THESE LINES !!!!

  if (result.command == COMMAND_RETURN_BLOCK){
      // Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
      Serial.println(result.ID);
  }
  else if (result.command == COMMAND_RETURN_ARROW){
    Serial.println("Wrong mode");
      // Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.ID);
  }
  else{
      Serial.println("Object unknown!");
  }
}

void red_on(){
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}

void green_on(){
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);
}

void blue_on(){
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
}

void white_on(){
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
}

void led_off(){
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}
