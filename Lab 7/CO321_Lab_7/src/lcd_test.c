/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - LCD Test
2025/07/07
*/

#include <avr/io.h>
#include <util/delay.h>

extern void lcdInit(void);
extern void printText(const char *msg, uint8_t clm, uint8_t row);

void test_lcd(void)
{
    /* initialize display, cursor off */
    lcdInit();
    printText("Hello Word!", 0, 0);

    while (1)
    {

        for (uint8_t i = 0; i < 10; i++)
        {
            printNumber(i, 2, 1);
            _delay_ms(1000);
        }
    }
}
