int pb1  = 6;
int pb2  = 7;
int pb3  = 8;
int pb4  = 9;
int led;
int A;

#define PATTERN_SIZE 5
#define LED_ON_DELAY 500

int pbPorts[] = {6, 7, 8, 9};
int currentPattern[PATTERN_SIZE];
int patternSize = 0; 
int ledPorts[] = {2, 3, 4, 5};

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
      led = ledPorts[currentPattern[i]];
      digitalWrite(led, HIGH);
      delay(delayVal);
      digitalWrite(led, LOW);
      delay(delayVal);
    }
}

void restart() {


}

bool anyButtonPressed() {
  for(int i = 0; i < sizeof(pbPorts); i++) {
    if (digitalRead(pbPorts[i]) == HIGH) {
      return true;
    }
  }
  return false;
}

int buttonPress() {
  while(anyButtonPressed() == false);
  for(int i = 0; i < sizeof(pbPorts); i++) {
     if(digitalRead(pbPorts[i]) == HIGH) {
       //Serial.println(i);
       return i;
    }
  }
}

void blinkLED(int ledNum, int blinkDelay, int blinkAmount, int delayOff) {
  for(int i = 0; i < blinkAmount; i++) {
    digitalWrite(ledPorts[ledNum], HIGH);
    delay(blinkDelay);
    digitalWrite(ledPorts[ledNum], LOW);
    if(delayOff != 0)
      delay(delayOff);
  }
} 

void doLED(int status) {
   for (int i = 0; i < sizeof(ledPorts); i++) {
    digitalWrite(ledPorts[i], status); 
  }
 }

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
  doPattern(4, LED_ON_DELAY);
  int userLED;
  for(int ledNo = 0; ledNo < patternSize; ledNo++) {
    //Serial.print("Looking for key: ");
    userLED = buttonPress();
    //Serial.println(userLED);
    blinkLED(userLED, LED_ON_DELAY, 1, 0);
    if(userLED != currentPattern[ledNo]) {
      restart();
      doLED(HIGH);
        delay(400);
      doLED(LOW);
      return;
    }
  }
  delay(LED_ON_DELAY);

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
