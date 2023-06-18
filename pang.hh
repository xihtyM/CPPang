#include <locale.h>
#include <string.h>

#include <iostream>
#include <string>

char *set_utf8(
    void
);

typedef struct ARGS
{
    std::string filename;
    std::string outname;
    bool        compiled;
    bool        to_cpp;
    bool        to_asm;
    bool        gdb;
    bool        keep_temp;
    int8_t      optimisation_level;
} ARGS;

#define new_args { \
    "", "",        \
    false, false,  \
    false, false,  \
    false, -1      \
}

bool arg_equ(
    char *src,
    std::string comp
);

ARGS parse_args(
    int argc,
    char *argv[]
);
