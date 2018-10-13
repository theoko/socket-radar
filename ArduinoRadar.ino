// Includes the Servo library
#include <Servo.h>
// Defines Trig and Echo pins of the Ultrasonic Sensor
const int trigPin = 7;
const int echoPin = 8;
// Variables for the duration and the distance
long duration;
int distance;
char flag = 0;
Servo myServo; // Creates a servo object for controlling the servo motor


const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton st

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);       // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT);     // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  myServo.attach(2); // Defines on which pin is the servo motor attached
}
void loop() {

  buttonState = digitalRead(buttonPin);     // read the state of the pushbutton value:

  if (buttonState == HIGH) { // when button is pressed
        digitalWrite(ledPin, HIGH); // turn LED on
        myServo.write(90); // stop moving servo
        buttonState = LOW; 
        flag = 1; 
 
  }

  if (((buttonState == LOW) && (flag == 0)) || ((buttonState == HIGH) && (flag == 1))) {
    
      // rotates the servo motor from 15 to 165 degrees
      for(int i=0;i<=180;i++){  // 15 to 165
      myServo.write(i);
      delay(30);
      distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
      
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      Serial.print(distance); // Sends the distance value into the Serial Port
      Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      }
      // Repeats the previous lines from 165 to 15 degrees
      for(int i=180;i>0;i--){  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      Serial.print(i);
      Serial.print(", ");
      Serial.print(distance);
      Serial.print(".");
      }


  }
    
  
  

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
  return distance;
}
