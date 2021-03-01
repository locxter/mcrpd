// Including the needed library
//#include <Keyboard.h>

// Defining look-ups for grid size (number of rows and columns) and pins (first columns, then rows)
const int GRID_SIZE[2] = {3, 3};
const int BUTTON_NUMBER = GRID_SIZE[0] * GRID_SIZE[1];
const int PINS[] = {5, 6, 7, 2, 3, 4};

// Defining variables for button readings
int buttonState[BUTTON_NUMBER];

// Defining variables for last button states
int lastButtonState[BUTTON_NUMBER];

void setup() {
    // Defining column pins as output and setting them to their default state
    for (int i = 0; i < GRID_SIZE[0]; i++) {
        pinMode(PINS[i], OUTPUT);
        digitalWrite(PINS[i], 1);
    }
    // Defining row pins as inputs
    for (int i = 0; i < GRID_SIZE[1]; i++) {
        pinMode(PINS[GRID_SIZE[0] + i], INPUT_PULLUP);
    }
    // Initializing keyboard functionality
    Keyboard.begin();
}

void loop() {
    // Reading the buttons
    for (int i = 0; i < GRID_SIZE[0]; i++) {
        digitalWrite(PINS[i], 0);
        for (int j = 0; j < GRID_SIZE[1]; j++) {
            buttonState[i + (j * GRID_SIZE[0])] = digitalRead(PINS[GRID_SIZE[0] + j]);
        }
        digitalWrite(PINS[i], 1);
    }
    // Checking for state changes and detecting button presses
    for (int i = 0; i < BUTTON_NUMBER; i++) {
        if (buttonState[i] != lastButtonState[i]) {
            lastButtonState[i] = buttonState[i];
            if (buttonState[i] == 0) {
                switch (i) {
                    case 0:
                        Keyboard.write(KEY_DOWN_ARROW);
                        break;
                    case 1:
                        Keyboard.write(KEY_UP_ARROW);
                        break;
                    case 2:
                        Keyboard.write(KEY_RETURN);
                        break;
                    case 3:
                        Keyboard.write(KEY_DELETE);
                        break;
                    case 4:
                        Keyboard.write(KEY_END);
                        break;
                    case 5:
                        Keyboard.write(KEY_PAGE_DOWN);
                        break;
                    case 6:
                        Keyboard.write(KEY_INSERT);
                        break;
                    case 7:
                        Keyboard.write(KEY_HOME);
                        break;
                    case 8:
                        Keyboard.write(KEY_PAGE_UP);
                        break;
                }
            }
        }
    }
    // Delay as very basic way to debounce
    delay(100);
}
