/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 07 - Part 2
2025/07/07
*/

#include <avr/io.h>

// Importing previously created EEPROM read/write libraries
extern void EEPROMwrite(uint16_t addr, uint8_t data);
extern uint8_t EEPROMread(uint16_t addr);

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

// Functions for the Serial Communication
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

char usart_receive(void)
{
    /* Wait for data to be recieved */
    while (!(UCSR0A & (1 << RXC0)))
        ;

    /* Get and return recieved data from buffer */
    return UDR0;
}

void usart_print(char *str)
{
    while (*str)
    {
        usart_send(*str++);
    }
}

// Main function
void serial_IO(void)
{
    // Initialize serial communication
    usart_init();

    char mode; // read - 0, write - 1

    while (1)
    {
        // Ckeck mode
        usart_print("\r\nEnter the mode (read - 0, write - 1):\r\n");
        mode = usart_receive();

        // Write Mode
        if (mode == '1')
        {
            usart_print("\r\nEnter sentence (\\r to end):\r\n");
            uint16_t addr = 0;

            while (1)
            {
                char character = usart_receive();

                if (character == '\r')
                {
                    usart_receive();
                    EEPROMwrite(addr++, '\0');
                    break;
                }
                else
                {
                    EEPROMwrite(addr++, character);
                }
            }

            usart_print("\r\nData written to EEPROM.\r\n");
        }

        // Read Mode
        else if (mode == '0')
        {
            usart_print("\r\nReading EEPROM:\r\n");
            for (uint16_t i = 0; i < 1024; i++)
            {
                char data = EEPROMread(i);
                if (data == '\0')
                    break;
                usart_send(data);
            }
            usart_print("\r\n");
        }

        // Invalid Mode
        else
        {
            usart_print("\r\nMode is invalid!\r\n");
        }
    }
}