/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 06 - Part 2
2025/07/05
*/

extern void usart_init(void);
extern void usart_send(char);

#include <avr/io.h>

void sendInfo(void)
{
    usart_init();
    char *message = "John Deer E/12/345, Keels Supper E/67/890";
    while (*message)
    {
        usart_send(*message++);
    }
}