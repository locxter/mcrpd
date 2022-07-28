#include <Keyboard.h>

// Look-ups for grid size (number of columns and rows) and pins
const int GRID_SIZE[] = {3, 3};
const int COLUMN_PINS[] = {5, 6, 7};
const int ROW_PINS[] = {2, 3, 4};

// Variables for reading the buttons
int buttonReadings[9];
unsigned long lastButtonPresses[9];

// Setup function
void setup() {
    // Define column pins as output and setting them to their default state
    for (int i = 0; i < GRID_SIZE[0]; i++) {
        pinMode(COLUMN_PINS[i], OUTPUT);
        digitalWrite(COLUMN_PINS[i], HIGH);
    }
    // Define row pins as inputs
    for (int i = 0; i < GRID_SIZE[1]; i++) {
        pinMode(ROW_PINS[i], INPUT_PULLUP);
    }
    // Initialize keyboard functionality
    Keyboard.begin();
}

// Main function
void loop() {
    // Read the buttons by switching a column at a time to non-default state and checking for connected rows
    for (int i = 0; i < GRID_SIZE[0]; i++) {
        digitalWrite(COLUMN_PINS[i], LOW);
        for (int j = 0; j < GRID_SIZE[1]; j++) {
            buttonReadings[i + (j * GRID_SIZE[0])] = digitalRead(ROW_PINS[j]);
        }
        digitalWrite(COLUMN_PINS[i], HIGH);
    }
    // Detecting button presses and reacting to them
    for (int i = 0; i < 9; i++) {
        if (buttonReadings[i] == LOW && millis() - lastButtonPresses[i] > 200) {
            switch (i) {
                case 0:
                    Keyboard.write('0');
                    break;
                case 1:
                    Keyboard.write('1');
                    break;
                case 2:
                    Keyboard.write('2');
                    break;
                case 3:
                    Keyboard.write('3');
                    break;
                case 4:
                    Keyboard.write('4');
                    break;
                case 5:
                    Keyboard.write('5');
                    break;
                case 6:
                    Keyboard.write('6');
                    break;
                case 7:
                    Keyboard.write('7');
                    break;
                case 8:
                    Keyboard.write('8');
                    break;
            }
            lastButtonPresses[i] = millis();
        }
    }
}
