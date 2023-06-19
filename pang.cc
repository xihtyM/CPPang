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
    bool st_args = false;

    for (int counter = 1; argv[counter]; counter++)
    {
        if (counter > 25)
            break;
        
        char *cur = argv[counter];

        if (st_args)
        {
            args.argv.push_back(cur);
            continue;
        }

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
        else if (arg_equ(cur, "gdb"))
            args.gdb = true;
        else if (arg_equ(cur, "temp"))
            args.keep_temp = true;
        else if (arg_equ(cur, "args"))
            st_args = true;
        else if (arg_equ(cur, "output"))
            output = true;
        else if (strcmp(cur, "-S") == 0)
            args.to_asm = true;
        else if (cur[0] == '-' && cur[1] == 'O')
            args.optimisation_level = (uint16_t) cur[2] - '0';
        else {
            args.filename = cur;
        }
    }

    return args;
}

char *open_file(ARGS *args)
{
    std::ifstream file(
        args->filename,
        std::ios::in | std::ios::ate);

    if (file.is_open())
    {
        // already at end of file because ios::ate, just tellg and move back
        std::streampos size = file.tellg();
        file.seekg(0, std::ios::beg);

        char *buf = new char[size];
        file.read(buf, size);

        file.close();

        return buf;
    }
    
    return NULL;
}
