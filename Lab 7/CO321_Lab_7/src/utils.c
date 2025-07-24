/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - Part 1
2025/07/07
*/

#include <avr/io.h>
#include <stdlib.h>
#include <lcd.h>
#include <util/delay.h>

/* EEPROM Functionalities */

void EEPROMwrite(uint16_t addr, uint8_t data)
{
    // 1. Wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;

    // 2. Set up address
    EEAR = addr;

    // 3. Set up data
    EEDR = data;

    // 4. Master write enable
    EECR |= (1 << EEMPE);

    // 5. Start EEPROM write
    EECR |= (1 << EEPE);
}

uint8_t EEPROMread(uint16_t addr)
{
    // 1. Wait for completion of previous write
    while (EECR & (1 << EEPE))
        ;

    // 2. Set up address
    EEAR = addr;

    // 3. Start EEPROM read
    EECR |= (1 << EERE);

    // 4. Return data
    return EEDR;
}

/* LCD Display Functionalities */
void lcdInit(void)
{
    lcd_init(LCD_DISP_ON);
}

void printText(const char *msg, uint8_t clm, uint8_t row)
{
    // Clear display
    if (row == 0)
    {
        lcd_clrscr();
    }

    // Set cursor position
    lcd_gotoxy(clm, row);

    // Print string to LCD
    lcd_puts(msg);
}

void printChar(const char ch, uint8_t clm, uint8_t row)
{
    // convert char into string
    char buffer[2] = {ch, '\0'};

    // Print
    printText(buffer, clm, row);
}

void printNumber(int num, uint8_t clm, uint8_t row)
{
    char buffer[7];

    // convert interger into string
    itoa(num, buffer, 10);

    // Print
    printText(buffer, clm, row);
}

/* Keypad Display Functionalities */
char KEYS[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void keypadInit(void)
{
    // Row pins: D10, D11, D12, D13 (PB2, PB3, PB4, PB5)
    // Column pins: D6, D7 (PD6, PD7) and D8, D9 (PB0, PB1)

    // Set PB5–PB2 (Rows) as outputs, PB1–PB0 (Cols) as inputs
    DDRB = (DDRB & ~0x03) | 0x3C; // 0b00111100
    PORTB |= 0x03;                // Enable pull-up resistors for PB0–PB1

    // Set PD7–PD6 (Cols) as inputs
    DDRD &= ~((1 << PD7) | (1 << PD6));
    PORTD |= (1 << PD7) | (1 << PD6); // Enable pull-ups for PD6 and PD7
}

char readChar(void)
{
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            // Set all rows HIGH, then one LOW
            PORTB |= 0x3C;            // PB5–PB2 HIGH
            PORTB &= ~(1 << (5 - i)); // Set PB2–PB5 one LOW at a time

            _delay_ms(5); // Debounce delay

            // Check column PB1 (Col 0)
            if (!(PINB & (1 << PB1)))
            {
                while (!(PINB & (1 << PB1)))
                    ;
                return KEYS[i][0];
            }

            // Check column PB0 (Col 1)
            if (!(PINB & (1 << PB0)))
            {
                while (!(PINB & (1 << PB0)))
                    ;
                return KEYS[i][1];
            }

            // Check column PD7 (Col 2)
            if (!(PIND & (1 << PD7)))
            {
                while (!(PIND & (1 << PD7)))
                    ;
                return KEYS[i][2];
            }

            // Check column PD6 (Col 3)
            if (!(PIND & (1 << PD6)))
            {
                while (!(PIND & (1 << PD6)))
                    ;
                return KEYS[i][3];
            }
        }
    }
}

void readText(char *buffer)
{
    int i;

    for (i = 0; i < 15; i++)
    {
        // Read character
        char key = readChar();

        // Terminate
        if (key == '#')
        {
            buffer[i] = '\0';
            break;
        }

        // Save character
        buffer[i] = key;
    }

    // End word
    buffer[i] = '\0';
}