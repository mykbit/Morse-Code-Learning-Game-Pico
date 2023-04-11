#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define WIN_THRESHOLD 5 // Number of correct answers to clear the level

char selected_level;
int consequent_wins;
int life_counter;
int str_index;
int level_attempts;
int level_wins;
int total_attepmts;
int total_wins;


/**
 * @brief Get a seed based on a current timestamp
 * 
 * @return int  A seed
 */
int get_seed();


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
 */
void level_play(char* level);


/**
 * @brief Plays the game at level 3 and 4.
 *        The function is called when the selected level is 3 or 4. The function displays the task
 *        to the user, prompts the user to input a sequence of morse code using the GP21 button,
 *        converts the morse code into an ASCII character, and checks if the input is correct.
 *        If the input is correct, the function calls itself recursively to restart the level or
 *        proceed to the next level. If the input is incorrect, life count is decremented and the
 *        function calls itself recursively to restart the level. If the user has no more lives,
 *        the game is over.
 * @param task 
 */
void level3_and_4_play(char *task);


/**
 * @brief Displays the level statistics to the user.
 * 
 */
void level_stats();


/**
 * @brief Displays the game statistics to the user.
 * 
 */
void game_stats();


/**
 * @brief  Manages the life counter and the RGB LED.
 * 
 * @param correct  A boolean value indicating whether the user input is correct or not.
 */
void life_and_rgb_management(bool correct);


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
char* level_select();


/**
 * @brief level_restart
 *        Restarts the game at the specified level.
 * @param selected_level The level to restart the game at.
 * @return               The task for the next level of the game. 
 */
char* level_restart ();


/**
 * @brief level_next
 *        Starts the game at the next level.
 * @param selected_level The level to start the game at.
 * @return               The task for the next level of the game. 
 */
char* level_next();


/**
 * @brief Level 1
 *        Generates a random task for level 1 and displays it to the user.
 *        The function generates a random index between 0 and 35, selects a corresponding alphanumeric character and its Morse code
 *        from the pre-defined arrays, and displays them to the user as the task for level 1. The function returns a pointer to the
 *        selected alphanumeric character.
 *  @return A pointer to the selected alphanumeric character.
 */
char* level1();


/**
 * @brief Level 2
 *        Generates a random task for level 2 and displays it to the user.
 *         The function generates a random index between 0 and 35, selects a corresponding alphanumeric character from the pre-defined
 *         array, and displays it to the user as the task for level 2. The function returns a pointer to the selected alphanumeric
 *         character.
 * @return A pointer to the selected alphanumeric character.
*/
char* level2();


/**
 * @brief Level 3
 *        Generates a random task for level 3 and displays it to the user.
 *        The function generates a random index between 0 and 9, selects a corresponding word and its Morse code from the pre-defined
 *        arrays, and displays them to the user as the task for level 3. The function returns a pointer to the selected word.
 * @return A pointer to the selected word.
 */
char* level3();


/**
 * @brief Level 4
 *        Generates a random task for level 4 and displays it to the user.
 *        The function generates a random index between 0 and 9, selects a corresponding word from the pre-defined array, and displays
 *        it to the user as the task for level 4. The function returns a pointer to the selected word.
 * @return A pointer to the selected word.
*/
char* level4();