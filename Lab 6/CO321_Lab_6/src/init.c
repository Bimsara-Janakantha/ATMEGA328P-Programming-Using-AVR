/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 06 - Part 1
2025/07/05
*/

#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void usart_init(void)
{
    /* Set baud rate */
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    /* Enable Tx and Rx */
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    /* 8 bit data, 1 stop bit, no parity */
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_send(char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    /* Put data into buffer, send the data */
    UDR0 = data;
}

char usart_recieve(void)
{
    /* Wait for data to be recieved */
    while (!(UCSR0A & (1 << RXC0)))
        ;

    /* Get and return recieved data from buffer */
    return UDR0;
}
