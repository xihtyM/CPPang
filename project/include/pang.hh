#pragma once

#include "lexer.hh"
#include "unicode_escape.hh"

#include <locale.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/// @brief sets locale encoding to utf8.
/// @return setlocale return value.
char *set_utf8(
    void);

typedef std::vector<std::string> string_vec;

typedef struct ARGS
{
    std::string filename;
    std::string outname;
    bool        to_obj;
    bool        to_asm;
    bool        run_on_compile;
    string_vec  links;
} ARGS;

#define new_args { \
    "", "",        \
    false, false,  \
    false, {}      \
}

/// @brief Checks if src == "-c" or src == "--comp" (replace comp with argument).
/// @param src The source string.
/// @param comp To compare against.
/// @return If src == "-c" or src == "--comp".
bool arg_equ(
    char *src,
    std::string comp
);

/// @brief Parses the arguments into an ARGS structure for ease of use.
/// @param argc main()'s argc.
/// @param argv main()'s argv.
/// @return ARGS structure, containing parsed arguments.
ARGS parse_args(
    int argc,
    char *argv[]
);

/// @brief Opens file and reads contents.
/// @param args Pointer to args struct.
/// @return Returns contents of file in char *, if file not found, returns null.
char *open_file(
    ARGS *args);

bool is_whitespace(
    char c);

bool is_identifier(
    char c);

bool is_num(
    char c);
