/*
Janakantha S.M.B.G.
E/20/157
CO321 - Embedded Systems
Lab 06 - Part 3
2025/07/05
*/

extern void usart_init(void);
extern void usart_send(char);
extern char usart_recieve(void);

#include <avr/io.h>

char caesar(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ((ch - 'a' + 3) % 26) + 'a';
    else if (ch >= 'A' && ch <= 'Z')
        return ((ch - 'A' + 3) % 26) + 'A';
    else
        return ch;
}

void encryptor(void)
{
    usart_init();
    char buffer[100];
    uint8_t i = 0;

    while (1)
    {
        char c = usart_recieve();

        // End of the sentence
        if (c == '\r')
        {
            buffer[i] = '\0';
            for (uint8_t j = 0; j < i; j++)
            {
                usart_send(caesar(buffer[j]));
            }
            usart_send('\r');
            usart_send('\n');

            /* Reset buffer */
            i = 0;
        }

        // Otherwise save to buffer
        else
        {
            buffer[i++] = c;
        }
    }
}