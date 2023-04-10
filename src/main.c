#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "ws2812.h"
#include "input_asm.h"
#include "morse.c"

void print_welcome_message() {
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
}

int main() {
  stdio_init_all();
  ws2812_init();

  print_welcome_message();

  while (true) {
    unsigned int test = input_asm();
    printf("%c - %s\n", binary_to_ascii(test), binary_to_morse(test));
  }

  return 0;
}
