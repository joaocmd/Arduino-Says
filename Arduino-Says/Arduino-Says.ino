#include "LinkedList.h"

#define DEFAULT_BAUD 9600
#define N_LEDS 4
#define N_LIVES 3
#define INPUT_DELAY 100
#define SCORE_DELAY 200
#define NO_INPUT -1

int leds[N_LEDS] = {5, 4, 3, 2};
int buttons[N_LEDS] = {6, 7, 8, 9};
int buzzer = 13;
int buzzerScale[N_LEDS] = {329, 440, 587, 784};
int lifeLeds[N_LIVES] = {10, 11, 12};

void setup() {
    //Initialize pin modes and set LEDs to off.
    for (int i = 0; i < N_LEDS; i++) {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], LOW);
        pinMode(buttons[i], INPUT);
    }
    for (int i = 0; i < N_LIVES; i++) {
        pinMode(lifeLeds[i], OUTPUT);
        digitalWrite(lifeLeds[i], LOW);
    }
    pinMode(buzzer, OUTPUT);
    noTone(buzzer);
    Serial.begin(DEFAULT_BAUD);
    randomSeed(analogRead(0));
    gameSetup();
}

//This function serves as the main point of the game, where 
void gameSetup() {
     outputArray(leds, N_LEDS, LOW);
     outputArray(lifeLeds, N_LIVES, LOW);
     outputArraySequenceAndBuzzer(leds, buzzer, buzzerScale, N_LEDS, 2, 50);
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
    tone(buzzer, buzzerScale[random(N_LEDS)]);
    Serial.println("Press any button.");
    //Flash leds and check for any button to be pressed.
    while (checkInputArray(buttons, N_LEDS) == NO_INPUT) {
        currMillis = millis();
        // if leds are on (only need to check 1).
        if (digitalRead(leds[0])) {
            if (currMillis - previousMillis >= onTime) {
                outputArray(leds, N_LEDS, LOW);
                noTone(buzzer);
                previousMillis = currMillis;
            }
        } else {
            if (currMillis - previousMillis >= offTime) {
                outputArray(leds, N_LEDS, HIGH);
                tone(buzzer, buzzerScale[random(N_LEDS)]);
                previousMillis = currMillis;
            }
        }
    }

    outputArray(leds, N_LEDS, LOW);
    noTone(buzzer);
    Serial.println("Starting game!");
    delay(500);
    playGame();
}

//Main game logic
void playGame() {
    int score = 0;
    int lives = N_LIVES;
    const int minDelay = 80;
    const int diffSteepness = 450;
    int startStepDelay = minDelay + diffSteepness;
    int stepDelay = startStepDelay;
    int choice;
    bool rightAnswer;

    Node x;
    List gameSequence = newList();
    generateRandomSequence(gameSequence);
    while (lives > 0) {
        rightAnswer = true;
        playSequence(gameSequence, stepDelay);
        x = getListHead(gameSequence);
        Serial.println("Repeat the sequence!");
        while (x != NULL && rightAnswer) {
            choice = pinToIndex(buttons, N_LEDS, waitForPlay());
            if (choice == getNodeValue(x)) {
                playLED(choice, stepDelay);
                x = getNextNode(x);
            } else {
                rightAnswer = false;
            }
            //Prevents repeated input
            delay(INPUT_DELAY);
        }
    
        if (rightAnswer) {
            score++;
            displayRightAnswer(score);
            stepDelay = diffSteepness/(score+1) + minDelay;
            generateRandomSequence(gameSequence);
        } else {
            lives--;
            displayWrongAnswer(lives);
        }
    }
    freeList(gameSequence);
    displayGameOver(score);
}

//Waits for player input and returns the pin of the clicked button.
int waitForPlay() {
    int choice = NO_INPUT;
    while (choice == NO_INPUT) {
        choice = checkInputArray(buttons, N_LEDS);
    }

    return choice;
}

//Adds a new random value to the sequence. It's chosen a new value
//between 0 and N_LEDS. The new value is added to sequence.
void generateRandomSequence(List sequence) {
    int randomVal = random(N_LEDS);
    Node n = newNode(randomVal);
    addNodeToList(sequence, n);
}

//Plays a sequence from a list, LEDs are on for onTime and off for offTime.
void playSequence(List sequence, int stepDelay) {
    for (Node x = getListHead(sequence); x != NULL; x = getNextNode(x)) {
        playLED(getNodeValue(x), stepDelay);
        delay(stepDelay);
    }
}

//Used during gameplay to light a single LED and the correspondant tone.
void playLED(int index, int onTime) {
    digitalWrite(leds[index], HIGH);
    tone(buzzer, buzzerScale[index]);
    delay(onTime);
    digitalWrite(leds[index], LOW);
    noTone(buzzer);
}

//Plays the animation for when the answer is wrong. Turns of one LED.
void displayWrongAnswer(int lives) {
    Serial.println("Wrong answer!");
    outputArray(leds, N_LEDS, HIGH);
    tone(buzzer, 130);
    delay(300);
    outputArray(leds, N_LEDS, LOW);
    noTone(buzzer);
    delay(500);
    Serial.print("You have ");
    Serial.print(lives);
    Serial.println(" tries remaining.");
    digitalWrite(lifeLeds[lives], LOW);
}

//Plays the animation for when the answer is right.
void displayRightAnswer(int score) {
    delay(300);
    outputArraySequenceAndBuzzer(leds, buzzer, buzzerScale, N_LEDS, 2, 50);
    Serial.print("Correct! You have now ");
    Serial.print(score);
    Serial.println(" points.");
    delay(300);
}

//Plays the animation for when the game is over.
void displayGameOver(int score) {
    delay(500);
    outputArray(lifeLeds, N_LEDS, HIGH);
    outputArray(leds, N_LEDS, HIGH);
    Serial.print("Game over, your score was: ");
    Serial.println(score);
    for (int points = 1; points <= score; points++) {
        outputArray(leds, N_LEDS, HIGH);
        tone(buzzer, buzzerScale[0]);
        delay(SCORE_DELAY);
        outputArray(leds, N_LEDS, LOW);
        noTone(buzzer);
        delay(SCORE_DELAY);
    }
    Serial.println("Restarting...");

    gameSetup();
}

//Nothing here
void loop() {}
