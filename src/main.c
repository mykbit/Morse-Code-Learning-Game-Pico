#include <stdio.h>
#include <stdlib.h>

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "level_setup.h"
#include "input_evaluate.h"
#include "morse.h"

#define IS_RGBW true   // Will use RGBW format
#define NUM_PIXELS 1   // There is 1 WS2812 device in the chain
#define WS2812_PIN 28  // The GPIO pin that the WS2812 connected to

char level;
int consequent_wins;

void main_asm();

// Initialise a GPIO pin – see SDK for detail on gpio_init()
void asm_gpio_init(uint pin) { gpio_init(pin); }

// Set direction of a GPIO pin – see SDK for detail on gpio_set_dir()
void asm_gpio_set_dir(uint pin, bool out) { gpio_set_dir(pin, out); }

// Get the value of a GPIO pin – see SDK for detail on gpio_get()
bool asm_gpio_get(uint pin) { return gpio_get(pin); }

// Set the value of a GPIO pin – see SDK for detail on gpio_put()
void asm_gpio_put(uint pin, bool value) { gpio_put(pin, value); }

// Enable falling-edge interrupt – see SDK for detail on gpio_set_irq_enabled()
void asm_gpio_set_irq_fall(uint pin) {
  gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_FALL, true);
}

// Enable falling-edge interrupt – see SDK for detail on gpio_set_irq_enabled()
void asm_gpio_set_irq_rise(uint pin) {
  gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_RISE, true);
}

/**
 * @brief Wrapper function used to call the underlying PIO
 *        function that pushes the 32-bit RGB colour value
 *        out to the LED serially using the PIO0 block. The
 *        function does not return until all of the data has
 *        been written out.
 *
 * @param pixel_grb The 32-bit colour value generated by urgb_u32()
 */
static inline void put_pixel(uint32_t pixel_grb) {
  pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

/**
 * @brief Function to generate an unsigned 32-bit composit GRB
 *        value by combining the individual 8-bit paramaters for
 *        red, green and blue together in the right order.
 *
 * @param r     The 8-bit intensity value for the red component
 * @param g     The 8-bit intensity value for the green component
 * @param b     The 8-bit intensity value for the blue component
 * @return uint32_t Returns the resulting composit 32-bit RGB value
 */
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}


/**
 * @brief Select Level
 *
 * @return char*  
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

  uint8_t input = input_asm();
  char selected_level = binary_to_ascii(input);

  if (selected_level == '1')
  {
    level = selected_level;
    return level1();
  }
  else if (selected_level == '2') {
    level = selected_level;
    return level2();
  }
  else if (selected_level == '3') {
    level = selected_level;
    return level3();
  }
  else if (selected_level == '4') {
    level = selected_level;
    return level4();
  }
  else {
    printf("Invalid input. Try again.\n");
    return select_level();
  }
}



/**
 * @brief 
 * 
 * @param char current_level
 * @param char* task
 * @param int index
 * @param int consequent_wins
 *
 * @return char*  
 */
char* level_play (char current_level, char* task, int index, int consequent_wins) {
  char input_char = binary_to_ascii(input_asm());
  if (input_char == '?') {
    consequent_wins++;
    if (consequent_wins >= 5)
    {
      printf("You won the game!\n");
      level_play(current_level, select_level(), 0, 0);
    }
    return select_level();
  }
  if (evaluate_input(task, input_char, index)) {
    printf("Correct!\n");
    level_play(current_level, task, ++index, consequent_wins);
  }
  else {
    printf("Incorrect!\n");
    consequent_wins = 0;
    index = 0;
    if (current_level == '1') {
      task = level1();
    }
    else if (current_level == '2') {
      task = level2();
    }
    else if (current_level == '3') {
      task = level3();
    }
    else if (current_level == '4') {
      task = level4();
    }
    else {
      current_level = select_level();
    }
    level_play(current_level, task, index, consequent_wins);
  }

}


/**
 * @brief Main
 * 
 * @param 
 *
 * @return int  Application return code (zero for success).
 */
int main() {
  // Initialise all STDIO as we will be using the GPIOs
  stdio_init_all();

  // Initialise the PIO interface with the WS2812 code
  PIO pio = pio0;
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, 0, offset, WS2812_PIN, 800000, IS_RGBW);

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

  return 0;
}
