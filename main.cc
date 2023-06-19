#include "pang.hh"

int main(int argc, char *argv[])
{
    set_utf8();

    ARGS args = parse_args(argc, argv);

    char *src = open_file(&args);

    if (!src) {
        std::cout << "couldn't read file.\n";
        exit(1);
    }

    std::cout << src;

    return 0;
}
