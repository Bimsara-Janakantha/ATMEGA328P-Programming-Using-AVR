/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - Part 1
2025/07/07
*/

#include <avr/io.h>

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
