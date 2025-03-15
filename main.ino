
// Includes the Servo library
#include <Servo.h>. 
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
int xPin = A0;
int yPin = A1;
int switchPin = 2;
int xVal; // variable for storing joystick x values
int yVal; // variable for storing joystick y values
int switchState; // variable for storing joystick switch state
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(7, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP);

}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  if(digitalRead(switchPin) == 1){
  for(int i=15;i<=165;i++){  
    if(digitalRead(switchPin) == 0){
      break;
    }
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
    if(digitalRead(switchPin) == 0){
      break;
    }
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
 // Serial.print(i);
 // Serial.print(",");
 // Serial.print(distance);
  //Serial.print(".");
  }}
  else{
    myServo.write(analogRead(yPin)/6);
  }

   // read the x, y and joystick switch values
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  switchState = digitalRead(switchPin);
 
  // print readings to the serial monitor
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.print(yVal);
  Serial.print(" | Switch: ");
  Serial.println(switchState);
 
  delay(100);
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  if(distance < 50){
    tone(3, 1000);
    digitalWrite(7, HIGH);
  }else{
    noTone(3);
    digitalWrite(7, LOW);
  }
  return distance;
}
