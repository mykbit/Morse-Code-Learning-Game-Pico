#include <stdio.h>
#include <stdlib.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "level_setup.h"

char alphanum_arr[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                         'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                         'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0',
                         '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char* morse_alphanum_arr[] = {
    ".-",    "-...",  "-.-.",  "-..",   ".",     "..-.",  "--.",   "....",
    "..",    ".---",  "-.-",   ".-..",  "--",    "-.",    "---",   ".--.",
    "--.-",  ".-.",   "...",   "-",     "..-",   "...-",  ".--",   "-..-",
    "-.--",  "--..",  "-----", ".----", "..---", "...--", "....-", ".....",
    "-....", "--...", "---..", "----."};

char* word_arr[] = {"HELLO",  "WORLD",  "PICO", "SCALA",  "C",
                    "PYTHON", "SUFFER", "RUST", "ENDURE", "JAVA"};

char* morse_word_arr[] = {".... . .-.. .-.. ---",
                          ".-- --- .-. .-.. -..",
                          ".--. .. -.-. ---",
                          "...- .-.-.- .-.. .-.. .",
                          "-.-. .",
                          ".--. -.-- --- -. -.--",
                          "...- ..-. --- .-. .- -..",
                          ".-. .. ... ...- .",
                          ". -.. .- -. -.. .",
                          ".--- .- ...- .-"};


/**
 * @brief Level 1
 * 
 * @return char*
 */
char* level1() {
  int index = rand() % 36;
  char* task_letter = &alphanum_arr[index];
  char* task_morse = morse_alphanum_arr[index];
  printf("Level 1: %s or &s\n", task_letter, task_morse);
  return task_letter;
}


/**
 * @brief Level 2
 *
 * @return char*  
 */
char* level2() {
  int index = rand() % 36;
  char* task_letter = &alphanum_arr[index];
  printf("Level 2: &s\n", task_letter);
  return task_letter;
}


/**
 * @brief Level 3
 * 
 * @return char*  
 */
char* level3() {
  int index = rand() % 10;
  char* task_word = word_arr[index];
  char* task_morse = morse_word_arr[index];
  printf("Level 3: %s or %s\n", task_word, task_morse);
  return task_word;
}


/**
 * @brief Level 4
 * 
 * @return char*  
 */
char* level4() {
  int index = rand() % 10;
  char* task_word = word_arr[index];
  printf("Level 4: %s\n", task_word);
  return task_word;
}
