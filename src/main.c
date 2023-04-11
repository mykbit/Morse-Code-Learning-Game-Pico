#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "ws2812.h"
#include "input_asm.h"
#include "morse.c"
#include "levels.c"

// TODO: Add a group number to the title screen.
int main() {
  stdio_init_all();
  watchdog_init(19000);
  ws2812_init();

  put_pixel(urgb_u32(0x00, 0x00, 0x1F));

  // clang-format off
  printf("|----------------------------- GROUP #16 -----------------------------|\n");
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
