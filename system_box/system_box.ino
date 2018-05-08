#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <Servo.h>
#include <TimedAction.h>


Servo myservo;  
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
// PIN FOR DETECTING SENSOR
int buzzer=6;
int box_status=A1;
static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 };

  void checkBall(){ 
  matrix.setRotation(0);
  int value=analogRead(box_status);
  Serial.println(value);
  if(value<500){
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, 64);
  digitalWrite(buzzer,HIGH);
  }
  else{
  matrix.clear();
  matrix.drawBitmap(8, 0, neutral_bmp, 8, 8, 64);
  digitalWrite(buzzer,LOW);
  
  }}
  
  void servoTurn(){
   myservo.write(10);
  delay(500);
  myservo.write(179);
  delay(500);
  
    }
 TimedAction servoThread = TimedAction(10,checkBall);



void setup() {

  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  
  
}


void loop() {
  servoTurn();
  servoThread.check();
  }

 

