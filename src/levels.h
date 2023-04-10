#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

char selected_level;
int consequent_wins;
int life_counter;

void level_play(char* level);

void life_and_rgb_management(bool correct);

char* level_select();

char* level_restart ();

char* level_next();

char* level1();

char* level2();

char* level3();

char* level4();

bool evaluate_input(char *task, char input, int index);