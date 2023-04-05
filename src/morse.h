#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char  ascii;
    char *morse;
} morse_table_t;

const morse_table_t morse_table[] = { 
    { 'A', ".-"    },
    { 'B', "-..."  },
    { 'C', "-.-."  },
    { 'D', "-.."   },
    { 'E', "."     },
    { 'F', "..-."  },
    { 'G', "--."   },
    { 'H', "...."  },
    { 'I', ".."    },
    { 'J', ".---"  },
    { 'K', "-.-"   },
    { 'L', ".-.."  },
    { 'M', "--"    },
    { 'N', "-."    },
    { 'O', "---"   },
    { 'P', ".--."  },
    { 'Q', "--.-"  },
    { 'R', ".-."   },
    { 'S', "..."   },
    { 'T', "-"     },
    { 'U', "..-"   },
    { 'V', "...-"  },
    { 'W', ".--"   },
    { 'X', "-..-"  },
    { 'Y', "-.--"  },
    { 'Z', "--.."  },
    { '1', ".----" },
    { '2', "..---" },
    { '3', "...--" },
    { '4', "....-" },
    { '5', "....." },
    { '6', "-...." },
    { '7', "--..." },
    { '8', "---.." },
    { '9', "----." },
    { '0', "-----" }
};

char morse_to_ascii(char* morse);

char* binary_to_morse(uint8_t binary);

char binary_to_ascii(uint8_t binary);
