#include "levels.h"

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

char selected_level;
int consequent_wins = 0;
int life_counter = 3;


/**
 * @brief Level 1
 *        Generates a random task for level 1 and displays it to the user.
 *        The function generates a random index between 0 and 35, selects a corresponding alphanumeric character and its Morse code
 *        from the pre-defined arrays, and displays them to the user as the task for level 1. The function returns a pointer to the
 *        selected alphanumeric character.
 *  @return A pointer to the selected alphanumeric character.
 */
char* level1() {
  srand(time(NULL));
  int index = random() % 36;
  char* task_letter = &alphanum_arr[index];
  char* task_morse = morse_alphanum_arr[index];
  printf("Level 1: %c or %s\n", *task_letter, task_morse);
  return task_letter;
}


/**
 * @brief Level 2
 *        Generates a random task for level 2 and displays it to the user.
 *         The function generates a random index between 0 and 35, selects a corresponding alphanumeric character from the pre-defined
 *         array, and displays it to the user as the task for level 2. The function returns a pointer to the selected alphanumeric
 *         character.
 * @return A pointer to the selected alphanumeric character.
*/
char* level2() {
  srand(time(NULL));
  int index = rand() % 36;
  char* task_letter = &alphanum_arr[index];
  printf("Level 2: %c\n", *task_letter);
  return task_letter;
}


/**
 * @brief Level 3
 *        Generates a random task for level 3 and displays it to the user.
 *        The function generates a random index between 0 and 9, selects a corresponding word and its Morse code from the pre-defined
 *        arrays, and displays them to the user as the task for level 3. The function returns a pointer to the selected word.
 * @return A pointer to the selected word.
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
 *        Generates a random task for level 4 and displays it to the user.
 *        The function generates a random index between 0 and 9, selects a corresponding word from the pre-defined array, and displays
 *        it to the user as the task for level 4. The function returns a pointer to the selected word.
 * @return A pointer to the selected word.
*/
char* level4() {
  int index = rand() % 10;
  char* task_word = word_arr[index];
  printf("Level 4: %s\n", task_word);
  return task_word;
}

/**
 * @brief select_Level
 *        Prompts the user to select a level and returns the corresponding level function 
 *        based on the user's input (morse code). The function displays the menu of four levels 
 *        to the user, prompts the user to input a sequence of morse code using the GP21 button,
 *        converts the morse code into an ASCII character, and selects the corresponding level 
 *        function based on the input. 
 *        If the input is invalid, the function prompts the user to try again.
 * @return A pointer to the selected level function.
*/
char* level_select() {
  printf("+---------------------------------------------------------------------+\n");
  printf("|                                                                     |\n");
  printf("|            --- USE GP21 TO INPUT A SEQUENCE TO BEGIN ---            |\n");
  printf("|                                                                     |\n");
  printf("|                  '-----' - LEVEL 01 - CHARS (EASY)                  |\n");
  printf("|                  '.----' - LEVEL 02 - CHARS (HARD)                  |\n");
  printf("|                  '..---' - LEVEL 03 - WORDS (EASY)                  |\n");
  printf("|                  '...--' - LEVEL 04 - WORDS (HARD)                  |\n");
  printf("|                                                                     |\n");
  printf("+---------------------------------------------------------------------+\n");

  unsigned int input = input_asm();
  selected_level = binary_to_ascii(input);
  printf("Selected level %c - %s\n", (int)selected_level+1, binary_to_morse(input));

  if (selected_level == '0')
  {
    life_and_rgb_management(true);
    return level1();
  }
  else if (selected_level == '1') {
    life_and_rgb_management(true);
    return level2();
  }
  else {
    printf("Invalid input. Try again.\n");
    return level_select();
  }
}


/**
 * @brief level_restart
 *        Restarts the game at the specified level.
 * @param selected_level The level to restart the game at.
 * @return               The task for the next level of the game. 
 */
char* level_restart () {
  printf("Restarting level %c...\n", (int)selected_level+1);
  if (selected_level == '0') {
    return level1();
  }
  else if (selected_level == '1') {
    return level2();
  }
  else {
    printf("Invalid input. Try again.\n");
    return level_select();
  }
}


/**
 * @brief level_next
 *        Starts the game at the next level.
 * @param selected_level The level to start the game at.
 * @return               The task for the next level of the game. 
 */
char* level_next() {
  printf("Get ready for the next level! %c...\n", (int)selected_level+1);
  if (selected_level == '0') {
    selected_level = '1';
    return level2();
  }
  else if (selected_level == '1') {
    selected_level = '2';
    return level3();
  }
  else if (selected_level == '2') {
    selected_level = '3';
    return level4();
  }
  else return (char*)'?';
}


/**
 * @brief  Manages the life counter and the RGB LED.
 * 
 * @param correct  A boolean value indicating whether the user input is correct or not.
 */
void life_and_rgb_management(bool correct) {
  if (correct) {
    if (life_counter < 3) {
      life_counter++;
    }
    if (life_counter == 3) {
      put_pixel(urgb_u32(0x00, 0x1F, 0x00));
    }
    else if (life_counter == 2) {
      put_pixel(urgb_u32(26, 11, 3));
    }
    else if (life_counter == 1) {
      put_pixel(urgb_u32(0x1F, 0x00, 0x00));
    }
  }

  else {
    life_counter--;
    if (life_counter == 2) {
      put_pixel(urgb_u32(26, 11, 3));
    }
    else if (life_counter == 1) {
      put_pixel(urgb_u32(0x1F, 0x00, 0x00));
    }
  }
}


/**
 * @brief level_play
 *        Plays the game at the specified level.
 *        The function takes in the task for the current level and the level number.
 *        It then prompts the user to input a sequence of morse code using the GP21 button,
 *        converts the morse code into an ASCII character, and compares it to the first character
 *        of the task. If the input is correct, the function calls itself recursively with the
 *        task and level number as parameters. If the input is incorrect, the function returns.
 * 
 * @param task             The task for the current level
 * @param selected_level   The level number
 */
void level_play (char* task) {
  unsigned int input = input_asm();
  char input_char = binary_to_ascii(input);

  if (input_char == task[0]) {
    printf("Correct!\n");
    life_and_rgb_management(true);
    consequent_wins++;
    if (consequent_wins < 3) {
      level_play(level_restart());
    }
    else {
      printf("Level cleared!\n");
      consequent_wins = 0;
      if (selected_level == '3') {
        printf("You won the game!\n");
        put_pixel(urgb_u32(0, 0, 0));
        return;
      }
      else {
        level_play(level_next());
      }
    }
  }
  else {
    printf("Incorrect!\n");
    life_and_rgb_management(false);
    consequent_wins = 0;
    if (life_counter > 0) {
      level_play(level_restart());
    }
    else if (life_counter == 0) {
      put_pixel(urgb_u32(0, 0, 0));
      printf("You lost the game!\n");
      return;
    }
  }
}


/**
 * @brief Evaluates the equivalence of a character to a character at a given point in a string.
 * 
 * @param char* task
 * @param char input
 * @param int index
 *
 * @return boolean Returns if current character is equivalent to character at index "index" in the string "task"  
 */

bool evaluate_input(char* task, char input, int index) {
    if (input == task[index]) {
        return true;
    } else {
        return false;
    }
}
