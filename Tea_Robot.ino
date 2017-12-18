/* 
 Owen Mitchell 200311982
 December 4 2017
 Tea Making Device
 This project is a simple machine which senses air temperature,
 indicates to the user through a multicoloured LED and a tone from a piezo speaker whether the temperature is above a certain treshold,
 and if the threshold is exceeded a set of functions are called to move a servo which is attached to a tea bag in order to steep the tea.
 */
#include <Servo.h>          // public library which lets me program the servo
Servo teaservo;             // where I set which pins each component uses
const int ledPinRed = 5;
const int ledPinGreen = 6;
const int ledPinBlue = 7;
const int tempPin = 0;
const int buttonPin = 2;
const int piezoPin = 12;

float temp, reading, voltage; // here I declare the global variables this program will use
int buttonState = 0;
int pos = 100; 

void setup()
{
  Serial.begin(9600);         // here I let the arduino know what mode to set each of the pins I am using
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  teaservo.attach(9);
}



void loop()
{
  buttonState = digitalRead(buttonPin);   // here I set where these variables should get their inputs from
  reading = analogRead(tempPin);
  voltage = reading * 5.0;                // this is code to convert the reading from the temperature sensor into degrees celcius
  voltage /= 1024.0;                      // this was based off code I found online at https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
  temp = (voltage - 0.5) * 100;
  Serial.print("Temprature = ");          // here I am formatting output to the serial monitor to track the air temperature
  Serial.print(temp);
  Serial.print(" C");
  Serial.println();
  delay(1000);

  if (buttonState == LOW)                 // here I give conditions for the pull-down button in the system
    {
      if (temp <= 25.0)                   // if the air temperature is hot above 25.0 degrees celcius the LED shows red and a faster lower tone plays
      {
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinRed, HIGH);
        tone(piezoPin, 440, 250);
      }
      else if (temp > 25.0)               // if the air temperature is above 25.0 degrees celcius the LED shows green, a slower higher tone plays, and the servo begins moving
      {
        digitalWrite(ledPinBlue, LOW);
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinRed, LOW);
        tone(piezoPin, 880, 750);

        teaArmDown(100,160,20000);        // here are the function calls which move the servo arm up and down
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,130,1000);
        teaArmDown(131,160,10000);
        teaArmUp(159,100,1000);
              
      }
    }
  else if (buttonState == HIGH)           // this is the passive state of the system when no button is being pressed, just a blue light and no sounds
    {
      digitalWrite(ledPinBlue, HIGH);
      digitalWrite(ledPinGreen, LOW);
      digitalWrite(ledPinRed, LOW);
    }
}
void teaArmDown(int p1, int p2, int d)    // here is the function definition which lowers the servo arm
{                                         // the three parameters are starting position, ending position, and how long to delay
  for(pos = p1; pos < p2; pos += 1)   
    {                                   
     teaservo.write(pos);               
     delay(45);                        
    }
  delay(d); 
}
void teaArmUp(int p1, int p2, int d)      // here is the function definition which raises the servo arm
{                                         // the three parameters are starting position, ending position, and how long to delay
  for(pos = p1; pos >= p2; pos -= 1)   
    {                                   
     teaservo.write(pos);               
     delay(45);                        
    }
  delay(d); 
}

