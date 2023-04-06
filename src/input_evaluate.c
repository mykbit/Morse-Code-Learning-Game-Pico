#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "input_evaluate.h"

bool evaluate_input(char* task, char input, int index) {
    if (input == task[index]) {
        return true;
    } else {
        return false;
    }
}
