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
  int start = -1;
  
  const int onTime = 1000;
  const int offTime = 400;
  unsigned long currMillis;
  unsigned long previousMillis = millis();
  
  
  outputArray(leds, N_LEDS, HIGH);
  outputArray(life_leds, N_LIFES, HIGH);
  Serial.println("Press any button");
  //Flash leds and check for input
  while (start == -1) {
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

//Main game logic
void playGame() {
  int lifes = N_LIFES;
  int choice = -1;
  int onTime, offTime;
  int timeDecrease;

  List gameSequence = newList();

  while (lifes > 0) {
    generateRandomSequence(gameSequence);
    playSequence(gameSequence);
    Node x = getListHead(gameSequence);
    while (x != NULL) {
      //waits for input
      while (choice == -1) {
        checkInputArray(buttons, N_LEDS);
      }
      choice = getInputValue(buttons, N_LEDS, choice);
      playLED(leds[choice]);
      if (choice == getNodeValue(x)) {
        x = getNextNode();
      } else {
        (*lifes)--;
        continue;
      }
    }
  }
}

//Returns for the index of the pin pinNumber in the inputs array.
int getInputValue(int inputs[], int len, int pinNumber) {
  for (int i = 0; i < len; i++) {
    if (inputs[i] == value) {
      return i;
    }
  }
  return = -1;
}

//Generates a random sequence to be played. For each list node it's chosen a new value
//between 0 and N_LEDS. At the end a new node is appended.
void generateRandomSequence(List sequence) {
  int randomVal;

  for (x = getListHead(sequence); x != NULL; x = getNextNode(x)) {
    randomVal = rand() % N_LEDS;
    setNodeValue(x, randomVal);
  }
  randomVal = rand() % N_LEDS;
  Node n = newNode(randomVal);
  addNoteToList(sequence, n);
}

//Plays a sequence from a list, LEDs are on for onTime and off for offTime.
void playSequence(List sequence, int onTime, offTime) {
  for (x = getListHead(sequence); x != NULL; x = getNextNode(x)) {
    playLED(getNodeValue(x, onTime);
    delay(offTime);
  }
}

//Used during gameplay to light a single LED and the correspondant tone.
void playLED(int index, int onTime) {
  digitalWrite(leds[index], HIGH)
  //Play tone on Piezo Buzzer
  switch (index):
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  delay(onTime);
  digitalWrite(leds[index], LOW);
}

//Returns the pin number of an input that was set to HIGH in the inputs array.
//If all were set to LOW, returns -1.
int checkInputArray(int inputs[], int len) {
  for (int i = 0; i < len; i++) {
    if (digitalRead(inputs[i]) == HIGH) {
      return inputs[i];
    }
  }
  return -1;
}

//Outputs value to all pins in the outputs array.
void outputArray(int outputs[], int len, int value) {
  for (int i = 0; i < len; i++) {
    digitalWrite(leds[i], value);
  }
}

//Writes HIGH for each pin in sequence and then LOW (following the order of the array).
//Each steps lasts stepDelay ms.
void outputSequence(int sequence[], int len, float loops, int stepDelay) {
    for (int i = 0; i < len*loops; i++) {
        digitalWrite(sequence[i%len], HIGH);
        delay(stepDelay);
        digitalWrite(sequence[i%len], LOW);
        delay(stepDelay);    
    }
}

//Nothing here
void loop() {}
