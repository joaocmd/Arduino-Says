#include "LinkedList.h"

#define N_LEDS 4
#define N_LIFES 3

int leds[N_LEDS] = {5, 4, 3, 2};
int buttons[N_LEDS] = {6, 7, 8, 9};
int life_leds[N_LIFES] = {10, 11, 12};

void setup() {
  //Initialize pin modes
  for (int i = 0; i < N_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
    pinMode(buttons[i], INPUT);
  }
  for (int i = 0; i < N_LIFES; i++) {
    pinMode(life_leds[i], OUTPUT);
    digitalWrite(life_leds[i], LOW);
  }

  Serial.begin(9600);
  gameSetup();
}

//This function serves as the main point of the game, where 
void gameSetup() {
   outputArray(leds, N_LEDS, LOW);
   outputSequence(leds, N_LEDS, 1, 50);
   delay(150);
   waitForStart();
}

//Flashes leds and waits for any button's input
void waitForStart() {
  bool start = false;
  
  const int onTime = 1000;
  const int offTime = 400;
  unsigned long currMillis;
  unsigned long previousMillis = millis();
  
  
  outputArray(leds, N_LEDS, HIGH);
  outputArray(life_leds, N_LIFES, HIGH);
  Serial.println("Press any button");
  //Flash leds and check for input
  while (!start) {
    currMillis = millis();
    // if leds are on (only need to check 1).
    if (digitalRead(leds[0])) {
      if (currMillis - previousMillis >= onTime) {
         outputArray(leds, N_LEDS, LOW);
         previousMillis = currMillis;
      }
    } else {
      if (currMillis - previousMillis >= offTime) {
        outputArray(leds, N_LEDS, HIGH);
        previousMillis = currMillis;
      }
    } 
    start = checkInputArray(buttons, N_LEDS);
  }

  outputArray(leds, N_LEDS, LOW);
  playGame();
}

void playGame() {
  int lifes = N_LIFES;
  int turn = 0;
  List gameSequence = newList();

  while (lifes > 0) {
    generateRandomSequence(gameSequence);
  }
}

void generateRandomSequence(List sequence) {
  int randomVal;
  
  for (x = getListHead(sequence); x != NULL; x = getNextNode(x)) {
    randomVal = rand() % N_LEDS;
    setNodeValue(x, randomVal);
  }
  randomVal = rand() % N_LEDS;
  Node n = newNode(randomVal);
}

//Returns whether any input was set to HIGH in the inputs array.
bool checkInputArray(int inputs[], int len) {
  for (int i = 0; i < len; i++) {
    if (digitalRead(inputs[i]) == HIGH) {
      return true;
    }
  }
  return false;
}

// Outputs value to all pins in the outputs array.
void outputArray(int outputs[], int len, int value) {
  for (int i = 0; i < len; i++) {
    digitalWrite(leds[i], value);
  }
}

void outputSequence(int sequence[], int len, float loops, int stepDelay) {
    for (int i = 0; i < len*loops; i++) {
        digitalWrite(sequence[i%len], HIGH);
        delay(stepDelay);
        digitalWrite(sequence[i%len], LOW);
        delay(stepDelay);    
    }
}

void loop() {/*nothing to see here */}
