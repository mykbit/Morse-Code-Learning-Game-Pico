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

void level_play(char* level);

void level3_and_4_play(char *task);

void level_stats();

void game_stats();

void life_and_rgb_management(bool correct);

char* level_select();

char* level_restart ();

char* level_next();

char* level1();

char* level2();

char* level3();

char* level4();