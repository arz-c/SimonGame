// Defining all of the LEDs and pushbuttons as Global Variables.
int pb1  = 6;
int pb2  = 7;
int pb3  = 8;
int pb4  = 9;
#define PATTERN_SIZE 50 // This part is a macro. A macro isn't a variable, but rather something that contains something which can't be changed.
int currentPattern[PATTERN_SIZE]; // This is an array. An array holds multiple characters in multiple slots. 
                                   // For example, if currentPattern[0] were to be used, it would show whatever is in the first slot of the array.
int patternSize = 0; // This patternSize is used to track the length of currentPattern.
int ledPorts[] = {2, 3, 4, 5}; 

void doPattern(int lednum, int delayVal) { // This function will create a random number in between 1 and whatever was written in lednum,
		int A = random(0, lednum);                                                                  //and display whicher LED it corresponds to.
  		int i;
		currentPattern[patternSize] = A; // We are saving the random number in the array in order to go back to it later and redo the same pattern with 
		patternSize++;	// This is adding 1 to patternSize since we just increased currentPattern by 1 last command.	                   //something added to the end.
		for(i = 0; i < patternSize; i++) {
			int led = ledPorts[currentPattern[i]]; // Creating a new variable to use in order to turn on/off the LEDs.
			digitalWrite(led, HIGH);                                                  // The variable, led, is holding currentPatterns' 'i' (from the for loop)
			delay(delayVal);
			digitalWrite(led, LOW);
			delay(delayVal); // These four lines are blinking the LED with a delay of whatever delayVal is set to in the function.
  
		}
}

void doLED(int status) {
   for (int i = 0; i < sizeof(ledPorts); i++) {
    digitalWrite(ledPorts[i], status); 
  }
 }

void setup() {
  randomSeed(analogRead(0)); // This seed is very important. The seed will change where the random number generator will start at. Otherwise, it'll always start at the
                                                                                              // same number since making an actualy RANDOM is impossible, it rather
  for (int i = 0; i < sizeof(ledPorts); i++) {
    pinMode(ledPorts[i], OUTPUT);
  }
  
  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
  pinMode(pb3, INPUT);
  pinMode(pb4, INPUT);
  
 Serial.begin(9600);                              // Serial is used to monitor things. You can open another tab called Serial Monitor to view whatever this is showing.
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}



void loop() {
  doPattern(4, 500);                             // Calling the doPattern function with a startNum of 1, delay of 500 (half a second), and 4 leds (lednum).
  delay(2000);
  if (patternSize == PATTERN_SIZE) {               // This if statement is to stop the doPattern function at a specific time (in this case, whatever PATTERN_SIZE is [5])
    patternSize = 0;
    for (int x = 0; x <= 2; x++) {
	  doLED(HIGH);
      delay(400);
	  doLED(LOW);
      delay(400);                                 // These 10 lines are in a for loop to repeat 2 times. It will basically blink all 4 leds on/off 3 times.
  }
  delay(600);                                     // This delay is outside of the for loop, in order to delay more before starting the void loop again.
 } 
}
 
