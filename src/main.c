#include <stdio.h>
#include <time.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

unsigned int input_asm();

// Initialise a GPIO pin – see SDK for detail on gpio_init()
void asm_gpio_init(uint pin) { gpio_init(pin); }

// Set direction of a GPIO pin – see SDK for detail on gpio_set_dir()
void asm_gpio_set_dir(uint pin, bool out) { gpio_set_dir(pin, out); }

// Get the value of a GPIO pin – see SDK for detail on gpio_get()
bool asm_gpio_get(uint pin) { return gpio_get(pin); }

// Set the value of a GPIO pin – see SDK for detail on gpio_put()
void asm_gpio_put(uint pin, bool value) { gpio_put(pin, value); }

// Enable falling-edge interrupt
void asm_gpio_set_irq_edge_fall(uint pin) {
  gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_FALL, true);
}

// Enable rising-edge interrupt
void asm_gpio_set_irq_edge_rise(uint pin) {
  gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_RISE, true);
}

uint32_t time_ms() {
  return (unsigned int)(time_us_64() / CLOCKS_PER_SEC / 10);
}

int main() {
  stdio_init_all();

  unsigned int test = input_asm();
  printf("%d", test);

  return 0;
}
