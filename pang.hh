#include <locale.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

char *set_utf8(
    void);

typedef std::vector<std::string> string_vec;

typedef struct ARGS
{
    std::string filename;
    std::string outname;
    string_vec  argv;
    bool        compiled;
    bool        to_cpp;
    bool        to_asm;
    bool        gdb;
    bool        keep_temp;
    uint16_t    optimisation_level;
} ARGS;

#define new_args { \
    "", "", {},    \
    false, false,  \
    false, false,  \
    false, 0       \
}

bool arg_equ(
    char *src,
    std::string comp
);

ARGS parse_args(
    int argc,
    char *argv[]
);

char *open_file(
    ARGS *args);
