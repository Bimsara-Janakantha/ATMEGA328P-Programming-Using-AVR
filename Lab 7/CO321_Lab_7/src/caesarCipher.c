/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - Part 3
2025/07/07
*/

#include <avr/io.h>
#include <util/delay.h>

#define BUFFER_SIZE 10
#define WRITE_DELAY 1000
#define READ_DELAY 3000
#define PULSE_DELAY 5
#define KEY_ADDR 0

// External EEPROM functions
extern void EEPROMwrite(uint16_t addr, uint8_t data);
extern uint8_t EEPROMread(uint16_t addr);

// External LCD Functions
extern void lcdInit(void);
extern void printText(const char *msg, uint8_t clm, uint8_t row);
extern void printChar(const char ch, uint8_t clm, uint8_t row);

// External Keypad functions
extern void keypadInit(void);
extern char readChar(void);

// Caesar cipher encryption
char encrypt(char ch)
{
    uint8_t key = EEPROMread(KEY_ADDR);

    if (ch >= 'a' && ch <= 'z')
        return ((ch - 'a' + key) % 26) + 'a';
    else if (ch >= 'A' && ch <= 'Z')
        return ((ch - 'A' + key) % 26) + 'A';
    else
        return ch;
}

void caesarCipher(void)
{
    /* initialize display and keypad */
    lcdInit();
    keypadInit();

    while (1)
    {
        printText("0:Set 1:Encrypt", 0, 0);
        printText("Mode:", 0, 1);

        char mode = readChar();
        printChar(mode, 6, 1);
        _delay_ms(WRITE_DELAY);

        // Set Key Mode
        if (mode == '0')
        {
            printText("New Key (0-9):", 0, 0);
            char keyChar = readChar();
            printChar(keyChar, 0, 1);
            _delay_ms(WRITE_DELAY);

            if (keyChar >= '0' && keyChar <= '9')
            {
                uint8_t key = keyChar - '0';
                EEPROMwrite(KEY_ADDR, key);
                printText("Key Saved.", 0, 0);
            }
            else
            {
                printText("Invalid Key!", 0, 0);
            }

            _delay_ms(READ_DELAY);
        }

        // Encrypt Mode
        else if (mode == '1')
        {
            uint8_t i = 0;
            uint16_t dataAddr = 1; // EEPROM address 0 is for key

            printText("Enter Msg:", 0, 0);
            _delay_ms(PULSE_DELAY);

            while (1)
            {
                char c = readChar();
                _delay_ms(PULSE_DELAY);

                if (c == '#') // End of message
                {
                    printText("Encrypted:", 0, 0);

                    for (uint8_t j = 0; j < i; j++)
                    {
                        char enc = EEPROMread(j + 1); // Skip EEPROM[0]
                        printChar(enc, j, 1);
                        _delay_ms(PULSE_DELAY);
                    }

                    break;
                }

                else if (i < BUFFER_SIZE)
                {
                    printChar(c, i, 1);
                    char enc = encrypt(c);
                    EEPROMwrite(dataAddr++, enc);
                    i++;
                }
                else
                {
                    printText("Msg too long!", 0, 0);
                    break;
                }
            }

            _delay_ms(READ_DELAY);
        }

        // Invalid Mode
        else
        {
            printText("Invalid Mode!", 0, 0);
            _delay_ms(READ_DELAY);
        }
    }
}
