// Including the needed library
//#include <Keyboard.h>

// Defining look-up for pins (first columns, then rows)
const int PINS[] = 
{
    5, 
    6, 
    7, 
    2, 
    3, 
    4
};

// Defining variables for button readings
int buttonState[9];

// Defining variables for last button states
int lastButtonState[9];

void setup() {
    // Defining column pins as output and setting them to their default state
    for (int i = 0; i < 3; i++) {
        pinMode(PINS[i], OUTPUT);
        digitalWrite(PINS[i], 1);
    }
    // Defining row pins as inputs
    for (int i = 0; i < 3; i++) {
        pinMode(PINS[3 + i], INPUT_PULLUP);
    }
    // Initializing keyboard functionality
    Keyboard.begin();
}

void loop() {
    // Reading the buttons
    for (int i = 0; i < 3; i++) {
        digitalWrite(PINS[i], 0);
        for (int j = 0; j < 3; j++) {
            buttonState[i + (j * 3)] = digitalRead(PINS[3 + j]);
        }
        digitalWrite(PINS[i], 1);
    }
    // Checking for state changes and detecting button presses
    for (int i = 0; i < 9; i++) {
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
