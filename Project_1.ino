//https://docs.arduino.cc/built-in-examples/digital/toneMelody


#include "pitches.h"

#define slider A0 //varable for slider pin
const int buttonPin = 2;// variable for button pin
const int buzzer = 5; // variable for buzzer pin
int buttonState = 0; // varaible for the current button state
int startTime, currentTime; //variable for time

int success; //variable for detecting if it fails or successful picks up the object

int success_melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int fail_melody[]={
  NOTE_GS3, NOTE_FS3, NOTE_DS3, NOTE_CS3
};

int success_noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int fail_noteDurations[] = {
  2, 2, 2, 1
};


void setup() {
  Serial.begin(9600); //opens up the serial monitor for communication to unity
  pinMode(slider, INPUT ); //define slider as a input
  pinMode(buttonPin, INPUT); //define button as a input
  pinMode(buzzer, OUTPUT); //define buzzer as a output


    //buzzer functions for when it sucessfully picks up the object or not
//    if success == true {
      successGrab(); 
//    } else {
      delay(3000);
      failGrab();
//    }
}

void loop() {
//  int slider_value = analogRead(slider); //variable to store the current slider value
  unsigned char i; // creates the variable i for loops
  
  clawDrop(); //button function to control to claw upward and downward movement
  slider_function(); //slider function to control to claws movement from side to side
};

void clawDrop() {
  buttonState = digitalRead(buttonPin); // assigning the buttonstate to the current button state

  //if the button is pressed send a 0 if not pressed send a 1
  if (buttonState == HIGH) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }
};

//i'll comment how this works later
void successGrab(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / success_noteDurations[thisNote];
    tone(5, success_melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(5);
  }
};



//i'll comment how this works later
void failGrab(){
    for (int thisNote = 0; thisNote < 4; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / fail_noteDurations[thisNote];
    tone(5, fail_melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(5);
  }
};



void slider_function() {
  int slider_value = analogRead(slider); //variable to store the current slider value
  Serial.println(slider_value); //send slider values to serial
};
