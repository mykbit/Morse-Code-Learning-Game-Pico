#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "string.h"

bool evaluate_input(char* task, char input) {
    for (int i = 0; i < strlen(task); i++) {
        if (input != task[i]) {
            return false;
        }
    }
    return true;
}
