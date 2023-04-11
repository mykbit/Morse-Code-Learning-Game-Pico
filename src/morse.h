#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  char ascii;
  char *morse;
} morse_table_t;

const morse_table_t morse_table[] = {
    {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
    {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
    {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
    {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
    {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
    {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
    {'Y', "-.--"},  {'Z', "--.."},  {'1', ".----"}, {'2', "..---"},
    {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."},
    {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'0', "-----"}};

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
char morse_to_ascii(char *morse);

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
char *binary_to_morse(uint8_t binary);

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
char binary_to_ascii(uint8_t binary);
