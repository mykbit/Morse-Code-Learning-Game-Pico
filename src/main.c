#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "ws2812.h"
#include "input_asm.h"
#include "morse.c"
#include "level_setup.c"

char selected_level;
int consequent_wins = 0;
int life_counter = 3;

void life_and_rgb_management(bool correct);

char* select_level();

char* level_restart (char selected_level);

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
char* select_level() {
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
    return select_level();
  }
}


/**
 * @brief level_restart
 *        Restarts the game at the specified level.
 * @param selected_level The level to restart the game at.
 * @return               The task for the next level of the game. 
 */
char* level_restart (char selected_level) {
  printf("Restarting level %c...\n", (int)selected_level+1);
  if (selected_level == '0') {
    return level1();
  }
  else if (selected_level == '1') {
    return level2();
  }
  else {
    printf("Invalid input. Try again.\n");
    return select_level();
  }
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
void level_play (char* task, char selected_level) {
  unsigned int input = input_asm();
  char input_char = binary_to_ascii(input);

  if (input_char == task[0]) {
    printf("Correct!\n");
    life_and_rgb_management(true);
    consequent_wins++;
    if (consequent_wins < 5) {
      level_play(level_restart(selected_level), selected_level);
    }
    else {
      printf("You won the game!\n");
      consequent_wins = 0;
      level_play(select_level(), selected_level);
    }
  }
  else {
    printf("Incorrect!\n");
    life_and_rgb_management(false);
    consequent_wins = 0;
    if (life_counter > 0) {
      level_play(level_restart(selected_level), selected_level);
    }
    else if (life_counter == 0) {
      put_pixel(urgb_u32(0, 0, 0));
      printf("You lost the game!\n");
      return;
    }
  }
}

int main() {
  stdio_init_all();
  ws2812_init();

  put_pixel(urgb_u32(0x00, 0x00, 0x1F));

  // clang-format off
  printf("+---------------------------------------------------------------------+\n");
  printf("|                                                                     |\n");
  printf("|      #           #######        #         #######     #      #      |\n");
  printf("|      #           #            #   #       #      #    ##     #      |\n");
  printf("|      #           #           #     #      #      #    # #    #      |\n");
  printf("|      #           #####      # # # # #     #######     #  #   #      |\n");
  printf("|      #           #          #       #     #    #      #   #  #      |\n");
  printf("|      #           #          #       #     #     #     #    # #      |\n");
  printf("|      ########    #######    #       #     #      #    #     ##      |\n");
  printf("|                                                                     |\n");
  printf("|     #        #    ########    #######       #####      ########     |\n");
  printf("|     ##      ##    #      #    #      #     #      #    #            |\n");
  printf("|     # #    # #    #      #    #      #     #           #            |\n");
  printf("|     #  #  #  #    #      #    #######       #####      #####        |\n");
  printf("|     #   ##   #    #      #    #    #              #    #            |\n");
  printf("|     #        #    #      #    #     #      #      #    #            |\n");
  printf("|     #        #    ########    #      #      #####      ########     |\n");
  printf("|                                                                     |\n");
  printf("+---------------------------------------------------------------------+\n");
  // clang-format on


  level_play(select_level(), selected_level);

  return 0;
}
