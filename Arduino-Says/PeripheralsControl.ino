/* Useful functions to control electronic devices. */

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

//Writes HIGH for each pin in sequence and then LOW (following the order of the array).
//Each steps lasts stepDelay ms. Also tones the buzzer with the according buzzerSeq note.
//It's a modification of outputArraySequence.
void outputArraySequenceAndBuzzer(int sequence[], int buzzer, int buzzerSeq[], int len, float loops, int stepDelay) {
    for (int i = 0; i < len*loops; i++) {
        digitalWrite(sequence[i%len], HIGH);
        tone(buzzer, buzzerSeq[i%len]);
        delay(stepDelay);
        digitalWrite(sequence[i%len], LOW);
        noTone(buzzer);
        delay(stepDelay);
    }
}
