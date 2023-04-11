#include "morse.h"

/**
 * @brief Converts a Morse code string to its corresponding ASCII character.
 *        The function searches the pre-defined Morse code to ASCII table for a
 *        match to the input Morse code string. If a match is found, the
 *        corresponding ASCII character is returned. If no match is found, the
 *        function returns a question mark.
 *
 * @param morse A pointer to the Morse code string to be converted.
 *
 * @return The corresponding ASCII character or a question mark if no match is
 *         found.
 */

char morse_to_ascii(char *morse) {
  for (int i = 0; i < (sizeof(morse_table) / sizeof(morse_table_t)); i++)
    if (strcmp(morse, morse_table[i].morse) == 0) {
      return morse_table[i].ascii;
    }

  return '?';
}

/**
 * @brief Converts an 8-bit binary number to its corresponding Morse code
 *        string. The function converts an 8-bit binary number to its
 *        corresponding Morse code string. The binary number is treated as a
 *        sequence of dots and dashes where a 1 represents a dot and a 0
 *        represents a dash. The function dynamically allocates memory for the
 *        Morse code string and returns a pointer to the string.
 *
 * @param binary An 8-bit binary number to be converted to Morse code.
 *
 * @return A dynamically allocated pointer to the corresponding Morse code
 *         string.
 */
char *binary_to_morse(uint8_t binary) {
  int size = 1;

  while (binary >> size != 1) size++;

  char *result = malloc(sizeof(char) * (size + 1));
  result[size] = '\0';

  for (int i = 0; i < size; i++)
    result[i] = (binary >> (size - 1 - i)) & 1 ? '-' : '.';

  return result;
}

/**
 * @brief Converts an 8-bit binary number to its corresponding ASCII character.
 *        The function converts an 8-bit binary number to its corresponding
 *        Morse code string using the binary_to_morse() function. The Morse code
 *        string is then converted to its corresponding ASCII character using
 *        the morse_to_ascii() function. The function frees the dynamically
 *        allocated memory used for the Morse code string and returns the
 *        resulting ASCII character.
 *
 * @param binary An 8-bit binary number to be converted to ASCII.
 *
 * @return The corresponding ASCII character.
 */
char binary_to_ascii(uint8_t binary) {
  char *morse = binary_to_morse(binary);
  char result = morse_to_ascii(morse);
  free(morse);
  return result;
}
