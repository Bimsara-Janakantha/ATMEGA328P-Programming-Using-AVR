/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - Keypad Test
2025/07/07
*/

#include <avr/io.h>
#include <util/delay.h>

extern void keypadInit(void);
extern void lcdInit(void);
extern void printText(const char *msg, uint8_t clm, uint8_t row);
extern char readChar(void);
extern void readText(char *buffer);

void keyTest(void)
{
    // Initialize Keypad
    keypadInit();

    // Initialize LCD
    lcdInit();

    char msg[17]; // Buffer to store key display message

    while (1)
    {
        // Welcome Message
        printText("Press any key", 0, 0);

        // Read key
        char key = readChar();

        // Clear previous message and print the key
        snprintf(msg, sizeof(msg), "Key: %c", key);
        printText(msg, 0, 1);

        _delay_ms(2000); // Delay before next prompt
    }
}

void keypadTest(void)
{
    // Initialize Keypad
    keypadInit();

    // Initialize LCD
    lcdInit();

    char message[16];

    while (1)
    {
        // Welcome Message
        printText("Type anything", 0, 0);

        // Read key
        readText(message);

        // Clear previous message and print the key
        printText(message, 0, 1);

        _delay_ms(2000); // Delay before next prompt
    }
}