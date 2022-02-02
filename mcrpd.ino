#include <Keyboard.h>

// Defining look-ups for grid size (number of columns and rows) and pins
const int GRID_SIZE[] = {3, 3};
const int COLUMN_PINS[] = {5, 6, 7};
const int ROW_PINS[] = {2, 3, 4};

// Defining variables for button readings and last button states
int buttonState[9];
int lastButtonState[9];

// Main setup function
void setup()
{
    // Defining column pins as output and setting them to their default state
    for (int i = 0; i < GRID_SIZE[0]; i++)
    {
        pinMode(COLUMN_PINS[i], OUTPUT);
        digitalWrite(COLUMN_PINS[i], HIGH);
    }
    // Defining row pins as inputs
    for (int i = 0; i < GRID_SIZE[1]; i++)
    {
        pinMode(ROW_PINS[i], INPUT_PULLUP);
    }
    // Initializing keyboard functionality
    Keyboard.begin();
}

// Main function
void loop()
{
    // Reading the buttons by switching a column at a time to non-default state and checking for connected rows
    for (int i = 0; i < GRID_SIZE[0]; i++)
    {
        digitalWrite(COLUMN_PINS[i], LOW);
        for (int j = 0; j < GRID_SIZE[1]; j++)
        {
            buttonState[i + (j * GRID_SIZE[0])] = digitalRead(ROW_PINS[j]);
        }
        digitalWrite(COLUMN_PINS[i], HIGH);
    }
    // Checking for state changes and detecting button presses
    for (int i = 0; i < 9; i++)
    {
        if (buttonState[i] != lastButtonState[i])
        {
            lastButtonState[i] = buttonState[i];
            if (buttonState[i] == 0)
            {
                switch (i)
                {
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
            }
        }
    }
    // Delay as a very basic way of debouncing
    delay(100);
}
