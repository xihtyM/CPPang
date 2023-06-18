#include "pang.hh"

int main(int argc, char *argv[])
{
    set_utf8();

    ARGS args = parse_args(argc, argv);

    std::cout << args.compiled << '\n'
              << args.filename << '\n'
              << args.outname << '\n'
              << args.to_cpp << '\n'
              << args.to_asm << '\n'
              << args.gdb << '\n'
              << args.keep_temp << '\n'
              << args.optimisation_level << '\n';

    return 0;
}
