int pb1  = 6;
int pb2  = 7;
int pb3  = 8;
int pb4  = 9;
int led;
int A;
int buzzer = 10;

#define PATTERN_SIZE 5
#define LED_ON_DELAY 500

int pbPorts[] = {6, 7, 8, 9};
int currentPattern[PATTERN_SIZE];
int patternSize = 0; 
int ledPorts[] = {2, 3, 4, 5};
int buzFreq[] = {55, 65, 82, 98};

/*
  The following function adds one LED to the pattern, then displays whatever is in the entire pattern.
  The pattern is saved in a global array named currentPattern.
  The pattern size is saved in global variable called patternSize.
*/
void doPattern(int lednum, int delayVal) {
    A = random(0, lednum);
    int i;
    currentPattern[patternSize] = A;
    patternSize++;
    for(i = 0; i < patternSize; i++) {
      blinkAndBeep(currentPattern[i], delayVal, delayVal);
    }
}

void restart() {


}

// Check if any button is pressed.
// Returns true or false.
bool anyButtonPressed() {
  for(int i = 0; i < sizeof(pbPorts); i++) {
    if (digitalRead(pbPorts[i]) == HIGH) {
      return true;
    }
  }
  return false;
}

// Wait for user's input, then return the input.
int buttonPress() {
  // Wait for user's input.
  while(anyButtonPressed() == false);
  for(int i = 0; i < sizeof(pbPorts); i++) {
     if(digitalRead(pbPorts[i]) == HIGH) {
       //Serial.println(i);
       return i;
    }
  }
}

// Blinks the led with specified perimeters.
void blinkLED(int ledNum, int blinkDelay, int blinkAmount, int delayOff) {
  for(int i = 0; i < blinkAmount; i++) {
    digitalWrite(ledPorts[ledNum], HIGH);
    delay(blinkDelay);
    digitalWrite(ledPorts[ledNum], LOW);
    if(delayOff != 0) {
      delay(delayOff);
    }
  }
} 

void blinkAndBeep(int ledNum, int delayOff, int delayOn) {
  int toneFreq;

  digitalWrite(ledPorts[ledNum], HIGH);
  toneFreq = buzFreq[ledNum];
  tone(buzzer, toneFreq, delayOn);
  delay(delayOn);
  digitalWrite(ledPorts[ledNum], LOW);
  if(delayOff != 0) {
    delay(delayOff);
  }
}

// Turn all LEDs on/off.
void doLED(int status) {
   for (int i = 0; i < sizeof(ledPorts); i++) {
    digitalWrite(ledPorts[i], status); 
  }
 }

// Sets up the hardware.
void setup() {
  randomSeed(analogRead(0));
  for (int i = 0; i < sizeof(ledPorts); i++) {
    pinMode(ledPorts[i], OUTPUT);
  }
  
  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
  pinMode(pb3, INPUT);
  pinMode(pb4, INPUT);
  
 Serial.begin(9600);
 while (!Serial) {
    ;
  }
}



void loop() {
  // Add a new LED to the pattern, and then display it.
  doPattern(4, LED_ON_DELAY);
  int userLED;
  // Loop through complete pattern.
  for(int ledNo = 0; ledNo < patternSize; ledNo++) {
    // Get user's input.
    userLED = buttonPress();
    // Blink it.
    blinkAndBeep(userLED, 0, LED_ON_DELAY);
    // Check if it's correct.
    if(userLED != currentPattern[ledNo]) {
      // Wrong - Restart the pattern.
      restart();
      doLED(HIGH);
        delay(400);
      doLED(LOW);
      return;
    }
  }
  delay(LED_ON_DELAY);

  // Check if PATTERN_SIZE exeeds the pattern size.
  // If yes, then blink all LEDs to indicate it, and restart the pattern.
  if (patternSize == PATTERN_SIZE) {
    patternSize = 0;
    for (int x = 0; x <= 2; x++) {
      doLED(HIGH);
      delay(400);
      doLED(LOW);
      delay(400);
    }
    delay(600);
  }
} 
