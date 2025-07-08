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
#define WAIT_DELAY 1000
#define KEY_ADDR 0

// External EEPROM functions
extern void EEPROMwrite(uint16_t addr, uint8_t data);
extern uint8_t EEPROMread(uint16_t addr);

// Display string to LCD (placeholder)
void lcdPrint(const char *msg)
{
    // Implement this using your LCD library (e.g., lcd_clear(); lcd_set_cursor(); lcd_print())
}

// Read character from keypad (placeholder)
char readKeypad()
{
    // Implement this using your keypad driver
    // Should block until key is pressed
    return '1';
}

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
    while (1)
    {
        lcdPrint("0:Set 1:Encrypt");
        _delay_ms(WAIT_DELAY);
        lcdPrint("Mode:");

        char mode = readKeypad();
        _delay_ms(WAIT_DELAY);

        // Set Key Mode
        if (mode == '0')
        {
            lcdPrint("New Key (0-9):");
            char keyChar = readKeypad();
            _delay_ms(WAIT_DELAY);

            if (keyChar >= '0' && keyChar <= '9')
            {
                uint8_t key = keyChar - '0';
                EEPROMwrite(KEY_ADDR, key);
                lcdPrint("Key Saved.");
            }
            else
            {
                lcdPrint("Invalid Key!");
            }

            _delay_ms(WAIT_DELAY);
        }

        // Encrypt Mode
        else if (mode == '1')
        {
            char buffer[BUFFER_SIZE];
            uint8_t i = 0;
            uint16_t dataAddr = 1; // EEPROM address 0 is for key

            lcdPrint("Enter Msg:");
            _delay_ms(WAIT_DELAY);

            while (1)
            {
                char c = readKeypad();
                _delay_ms(WAIT_DELAY);

                if (c == '*') // End of message
                {
                    buffer[i] = '\0';
                    lcdPrint("Encrypted:");

                    for (uint8_t j = 0; j < i; j++)
                    {
                        char enc = EEPROMread(j + 1); // Skip EEPROM[0]
                        char str[2] = {enc, '\0'};
                        lcdPrint(str);
                        _delay_ms(300);
                    }

                    break;
                }

                if (i < BUFFER_SIZE)
                {
                    buffer[i] = c;
                    char enc = encrypt(c);
                    EEPROMwrite(dataAddr++, enc);
                    i++;
                }
                else
                {
                    lcdPrint("Msg too long!");
                    break;
                }
            }

            _delay_ms(WAIT_DELAY);
        }

        // Invalid Mode
        else
        {
            lcdPrint("Invalid Mode!");
            _delay_ms(WAIT_DELAY);
        }
    }
}
