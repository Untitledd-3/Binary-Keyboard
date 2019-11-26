#include <Keyboard.h>
// set pin numbers:
const int buttonPin0 = 2;    // the number of the pushbutton pin
const int buttonPin1 = 3;    // the number of the pushbutton pin
const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Variables will change:
int buttonState0;             // the current reading from the input pin
int lastButtonState0 = LOW;   // the previous reading from the input pin
int buttonState1;             // the current reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin

int character[8];
String x;
int i;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime0 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay0 = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay1 = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);

  Keyboard.begin();
  Serial.begin(9600);
  
  for ( int n = 0; n < 8; n++ ) {
    character[n] = 0;    
   }
}

int readBinaryString(char *s) {
  int result = 0;
    while(*s) {
      result <<= 1;
      if(*s++ == '1') result |= 1;
    }
  return result;
}
void loop() {
  for ( int n = 0; n < 8; n++ ) {
      character[n] = 0;
  }
  i = 0;
  x = "";
  while (i < 8) {
  // read the state of the switch into a local variable:
  int reading0 = digitalRead(buttonPin0);
  int reading1 = digitalRead(buttonPin1);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading0 != lastButtonState0) {
    // reset the debouncing timer
    lastDebounceTime0 = millis();
  }

  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }
  if ((millis() - lastDebounceTime0) > debounceDelay0) {
  if ((millis() - lastDebounceTime1) > debounceDelay1) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading0 != buttonState0) {
      buttonState0 = reading0;

      // only toggle the LED if the new button state is HIGH
      if (buttonState0 == LOW) {
        character[i] = 0;
        for ( int n = 0; n < 8; n++ ) {
          Serial.print(character[n]);   
        }
        Serial.print("\n");
        i++;
      }
    }
  }
      if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == LOW) {
        character[i] = 1;
        for ( int n = 0; n < 8; n++ ) {
          Serial.print(character[n]);
        }
        Serial.print("\n");
        i++;
      }
      }
    }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState0 = reading0;
  lastButtonState1 = reading1;
    }
    for ( int n = 0; n < 8; n++) {
      x += character[n];
    }
    char charBuf[50];
    x.toCharArray(charBuf, 50);
    int value = readBinaryString(charBuf);

    Keyboard.write(value);
  }
