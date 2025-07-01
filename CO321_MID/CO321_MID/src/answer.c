/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
MID EXAMINATION - Main
2025/07/02
*/

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
  // Define PIN B5 as OUTPUT
  DDRB = DDRB | (1 << PB5);

  // Set PIN B5 to LOW
  PORTB = 0x00;

  while (1)
  {
    PORTB = PORTB ^ (1 << PB5);
    _delay_ms(BLINK_DELAY_MS);
  }

  return 0;
}
