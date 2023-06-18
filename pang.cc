#include "pang.hh"

char *set_utf8(void)
{
    return setlocale(
        LC_ALL, ".utf-8");
}

bool arg_equ(char *src, std::string comp)
{
    std::string small = "-";
    small += comp[0];

    std::string large = "--" + comp;

    large[2] = tolower(large[2]);

    return small == src
        || large == src;
}

ARGS parse_args(int argc, char *argv[])
{
    ARGS args = new_args;
    bool output = false;

    for (int counter = 0; argv[counter]; counter++)
    {
        if (counter > 25)
            break;
        
        char *cur = argv[counter];

        if (output)
        {
            args.outname = cur;
            output = false;
            continue;
        }

        if (arg_equ(cur, "compiled"))
            args.compiled = true;
        else if (arg_equ(cur, "Cpp"))
            args.to_cpp = true;
        else if (arg_equ(cur, "output"))
            output = true;
        else if (strcmp(cur, "-S") == 0)
            args.to_asm = true;
    }

    return args;
}
