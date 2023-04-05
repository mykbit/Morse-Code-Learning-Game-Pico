#include "morse.h"

char morse_to_ascii(char* morse) {
    for(int i = 0; i < sizeof(morse_table) / sizeof(morse_table_t); i++)
        if(strcmp(morse, morse_table[i].morse) == 0)
            return morse_table[i].ascii;
            
    return '?';
}

char* binary_to_morse(uint8_t binary) {
    int size = 1;

    while(binary >> size != 1)
        size++;

    char *result = malloc(sizeof(char) * (size + 1));
    result[size] = '\0';

    for (int i = 0; i < size; i++)
        result[i] = (binary >> (size - 1 - i)) & 1 ? '.' : '-';

    return result;
}

char binary_to_ascii(uint8_t binary) {
    char* morse = binary_to_morse(binary);
    char result = morse_to_ascii(morse);
    free(morse);
    return result;
}
