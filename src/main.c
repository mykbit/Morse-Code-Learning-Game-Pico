#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void main_asm();

// Initialise a GPIO pin – see SDK for detail on gpio_init()
void asm_gpio_init(uint pin) {
    gpio_init(pin);
}

// Set direction of a GPIO pin – see SDK for detail on gpio_set_dir()
void asm_gpio_set_dir(uint pin, bool out) {
    gpio_set_dir(pin, out);
}

// Get the value of a GPIO pin – see SDK for detail on gpio_get()
bool asm_gpio_get(uint pin) {
    return gpio_get(pin);
}

// Set the value of a GPIO pin – see SDK for detail on gpio_put()
void asm_gpio_put(uint pin, bool value) {
    gpio_put(pin, value);
}

int select_level() {
    int input = input_asm();
    return parse_morse(input);
}

int main() {
    stdio_init_all();

    show_welcome_message();
    char level = select_level();

    switch(level) {
        case '1':
            start_first_level();
            break;
        case '2':
            start_second_level();
            break;
        case '3':
            start_third_level();
            break;
        case '4':
            start_fourth_level();
            break;
        default:
            printf("Invalid input");
    }

    return 0;
}
