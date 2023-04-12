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

char* word_arr[] = {"HELLO",  "WORLD",  "PICO", "SCALA",  "CLARITY",
                    "PYTHON", "SUFFER", "RUST", "ENDURE", "JAVA"};

char* morse_word_arr[] = {".... . .-.. .-.. ---",
                          ".-- --- .-. .-.. -..",
                          ".--. .. -.-. ---",
                          "... -.-. .- .-.. .-",
                          "-.-. .-.. .- .-. .. - -.--",
                          ".--. -.-- - .... --- -.",
                          "... ..- ..-. ..-. . .-.",
                          ".-. ..- ... -",
                          ". -. -.. ..- .-. .",
                          ".--- .- ...- .-"};

char selected_level;
int consequent_wins = 0;
int life_counter = 3;
int str_index = 0;
int level_attempts = 0;
int level_wins = 0;
int total_attempts = 0;

int get_seed() { 
  time_t t; 
  srand((unsigned) time(&t));
  return rand();
}


char* level1() {
  srand(get_seed());
  int index = rand() % 36;
  char* task_letter = &alphanum_arr[index];
  char* task_morse = morse_alphanum_arr[index];
  printf("Level 1: %c or %s\n", *task_letter, task_morse);
  return task_letter;
}


char* level2() {
  srand(get_seed());
  int index = rand() % 36;
  char* task_letter = &alphanum_arr[index];
  printf("Level 2: %c\n", *task_letter);
  return task_letter;
}


char* level3() {
  srand(get_seed());
  int index = rand() % 10;
  char* task_word = word_arr[index];
  char* task_morse = morse_word_arr[index];
  printf("Level 3: %s or %s\n", task_word, task_morse);
  return task_word;
}


char* level4() {
  srand(get_seed());
  int index = rand() % 10;
  char* task_word = word_arr[index];
  printf("Level 4: %s\n", task_word);
  return task_word;
}


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
  printf("Selected level %c\n", (int)selected_level+1);

  if (selected_level == '0')
  {
    life_and_rgb_management(true);
    return level1();
  }
  else if (selected_level == '1') {
    life_and_rgb_management(true);
    return level2();
  }
  else if (selected_level == '2') {
    life_and_rgb_management(true);
    return level3();
  }
  else if (selected_level == '3') {
    life_and_rgb_management(true);
    return level4();
  }
  else {
    printf("Invalid input. Try again.\n");
    return level_select();
  }
}


char* level_restart () {
  printf("Restarting level %c...\n", (int)selected_level+1);
  str_index = 0;
  if (selected_level == '0') {
    return level1();
  }
  else if (selected_level == '1') {
    return level2();
  }
  else if (selected_level == '2') {
    return level3();
  }
  else if (selected_level == '3') {
    return level4();
  }
  else {
    printf("Something went wrong. Try selecting the level again.\n");
    return level_select();
  }
}


char* level_next() {
  printf("Get ready for the next level!\n");
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


void life_and_rgb_management(bool correct) {
  if (correct) {
    if (life_counter < 3) {
      life_counter++;
    }
    if (life_counter == 3) {
      put_pixel(urgb_u32(0x00, 0x1F, 0x00));
    }
    else if (life_counter == 2) {
      put_pixel(urgb_u32(0x1F, 0x1F, 0x00));
    }
    else if (life_counter == 1) {
      put_pixel(urgb_u32(26, 11, 3));
    }
  }

  else {
    life_counter--;
    if (life_counter == 2) {
      put_pixel(urgb_u32(0x1F, 0x1F, 0x00));
    } else if (life_counter == 1) {
      put_pixel(urgb_u32(26, 11, 3));
    }
  }
}


void game_stats() {
  printf("Game stats: %d/%d correct.\n", total_wins, total_attempts);
  total_wins = 0;
  total_attempts = 0;
}


void level_stats() {
  printf("Level stats: %d/%d correct.\n", level_wins, level_attempts);
  level_wins = 0;
  level_attempts = 0;
}


void level3_and_4_play(char* task) {
  
  unsigned int input = input_asm();
  char input_char = binary_to_ascii(input);
  printf("User input: %c - '%s'\n", input_char, binary_to_morse(input));
  if (task[str_index] == input_char) {
    if (str_index == strlen(task)-1) {
      level_attempts++;
      total_attempts++;
      printf("Correct!\n");
      life_and_rgb_management(true);
      consequent_wins++;
      level_wins++;
      total_wins++;
      str_index = 0;
      
      if (consequent_wins >= WIN_THRESHOLD) {
        if (selected_level == '3') {
          printf("Congratulations! You have completed the game!\n");
          put_pixel(urgb_u32(0x1F, 0x1F, 0x1F));
          level_stats();
          game_stats();
          return;
        }
        consequent_wins = 0;
        printf("Level clear!\n");
        level_stats();

        level3_and_4_play(level_next());
      }
      else {
        level3_and_4_play(level_restart());
      }

    }
    else {
      str_index++;
      level3_and_4_play(task);
    }
  }
  else {
    level_attempts++;
    total_attempts++;
    printf("Incorrect!\n");
    life_and_rgb_management(false);
    consequent_wins = 0;
    if (life_counter == 0) {
      printf("Game Over!\n");
      level_stats();
      game_stats();
      put_pixel(urgb_u32(0x1F, 0x00, 0x00));
      return;
    }
    else {
      level3_and_4_play(level_restart());
    }
  }
}


void level_play (char* task) {

  if (selected_level != '0' && selected_level != '1') {
    level3_and_4_play(task);
  }
  else {
    level_attempts++;
    total_attempts++;
    unsigned int input = input_asm();
    char input_char = binary_to_ascii(input);
    printf("User input: %c - '%s'\n", input_char, binary_to_morse(input));

    if (input_char == task[0]) {
      printf("Correct!\n");
      life_and_rgb_management(true);
      consequent_wins++;
      level_wins++;
      total_wins++;

      if (consequent_wins < WIN_THRESHOLD) {
        level_play(level_restart());
      }
      else {
        printf("Level clear!\n");
        consequent_wins = 0;
        level_stats();
        level_play(level_next());
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
        put_pixel(urgb_u32(0x1F, 0, 0));
        printf("Game Over!\n");
        level_stats();
        game_stats();
        return;
      }
    }
  }
}
