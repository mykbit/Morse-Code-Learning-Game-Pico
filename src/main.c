#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "ws2812.h"
#include "input_asm.h"
#include "morse.c"
#include "levels.c"

int main() {
  stdio_init_all();
  ws2812_init();

  put_pixel(urgb_u32(0x00, 0x00, 0x1F));

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

  level_play(level_select());

  return 0;
}
