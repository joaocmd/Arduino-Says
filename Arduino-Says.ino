#include "LinkedList.h"

#define N_LEDS 4
#define N_LIVES 3

int leds[N_LEDS] = {5, 4, 3, 2};
int buttons[N_LEDS] = {6, 7, 8, 9};
int lifeLeds[N_LIVES] = {10, 11, 12};

void setup() {
  //Initialize pin modes
  for (int i = 0; i < N_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
    pinMode(buttons[i], INPUT);
  }
  for (int i = 0; i < N_LIVES; i++) {
    pinMode(lifeLeds[i], OUTPUT);
    digitalWrite(lifeLeds[i], LOW);
  }

  Serial.begin(9600);
  gameSetup();
}

//This function serves as the main point of the game, where 
void gameSetup() {
   outputArray(leds, N_LEDS, LOW);
   outputArray(lifeLeds, N_LIVES, LOW);
   outputArraySequence(leds, N_LEDS, 2, 50);
   delay(150);
   waitForStart();
}

//Flashes leds and waits for any button's input
void waitForStart() { 
  const int onTime = 1000;
  const int offTime = 400;
  unsigned long currMillis;
  unsigned long previousMillis = millis();

  outputArray(leds, N_LEDS, HIGH);
  outputArray(lifeLeds, N_LIVES, HIGH);
  Serial.println("Press any button");
  //Flash leds and check for any button to be pressed.
  while (checkInputArray(buttons, N_LEDS) == -1) {
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
  }

  outputArray(leds, N_LEDS, LOW);
  Serial.println("Starting game!");
  playGame();
}

//Main game logic
void playGame() {
  int score = 0;
  int lives = N_LIVES;
  int choice;
  int onTime = 500, offTime = 300;
  int timeDecrease = 25;
  Node x;

  List gameSequence = newList();

  generateRandomSequence(gameSequence);
  while (lives > 0) {
    playSequence(gameSequence, onTime, offTime);
    x = getListHead(gameSequence);
    while (x != NULL) {
      //waits for input
      choice = -1;
      while (choice == -1) {
        choice = checkInputArray(buttons, N_LEDS);
      }
      choice = pinToIndex(buttons, N_LEDS, choice);
      playLED(leds[choice], onTime);
      if (choice == getNodeValue(x)) {
        x = getNextNode(x);
      } else {
        x = getListHead(gameSequence);
        lives--;
        displayWrongAnswer(lives);
        playSequence(gameSequence, onTime, offTime);
        continue;
      }
    }
    score++;
    displayRightAnswer(score);
    onTime -= timeDecrease;
    offTime -= timeDecrease;
    generateRandomSequence(gameSequence);
  }

  freeList(gameSequence);
  displayGameOver(score);
}

//Adds a new random value to the sequence. It's chosen a new value
//between 0 and N_LEDS. The new value is added to sequence.
void generateRandomSequence(List sequence) {
  int randomVal = rand() % N_LEDS;
  Node n = newNode(randomVal);
  addNodeToList(sequence, n);
}

//Plays a sequence from a list, LEDs are on for onTime and off for offTime.
void playSequence(List sequence, int onTime, int offTime) {
  for (Node x = getListHead(sequence); x != NULL; x = getNextNode(x)) {
    playLED(getNodeValue(x), onTime);
    delay(offTime);
  }
}

//Used during gameplay to light a single LED and the correspondant tone.
void playLED(int index, int onTime) {
  digitalWrite(leds[index], HIGH);
  //Play tone on Piezo Buzzer
  switch (index) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }
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

//Returns the index of the pin pinNumber in the inputs array.
int pinToIndex(int inputs[], int len, int pinNumber) {
  for (int i = 0; i < len; i++) {
    if (inputs[i] == pinNumber) {
      return i;
    }
  }
  return -1;
}

//Plays the animation for when the answer is wrong. Turns of one LED.
void displayWrongAnswer(int lives) {
  Serial.println("Wrong answer!");
  outputArray(leds, N_LEDS, HIGH);
  delay(300);
  outputArray(leds, N_LEDS, LOW);
  Serial.print("You have ");
  Serial.print(lives);
  Serial.println(" remaining.");
  digitalWrite(lifeLeds[lives], LOW);
}

//Plays the animation for when the answer is right.
void displayRightAnswer(int score) {
  outputArraySequence(leds, N_LEDS, 2, 50);
  Serial.print("Correct! You have now ");
  Serial.print(score);
  Serial.println(" points.");
}

//Plays the animation for when the game is over.
void displayGameOver(int score) {
  delay(500);
  outputArray(lifeLeds, N_LEDS, HIGH);
  outputArray(leds, N_LEDS, HIGH);
  Serial.print("Game over, your score was: ");
  Serial.print(score);
  Serial.println("Restarting...");
  gameSetup();
}

//Outputs value to all pins in the outputs array.
void outputArray(int outputs[], int len, int value) {
  for (int i = 0; i < len; i++) {
    digitalWrite(outputs[i], value);
  }
}

//Writes HIGH for each pin in sequence and then LOW (following the order of the array).
//Each steps lasts stepDelay ms.
void outputArraySequence(int sequence[], int len, float loops, int stepDelay) {
    for (int i = 0; i < len*loops; i++) {
        digitalWrite(sequence[i%len], HIGH);
        delay(stepDelay);
        digitalWrite(sequence[i%len], LOW);
        delay(stepDelay);    
    }
}

//Nothing here
void loop() {}
