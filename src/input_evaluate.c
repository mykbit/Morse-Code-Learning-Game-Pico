#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "input_evaluate.h"


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
