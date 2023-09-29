#include "include/pang.hh"

std::ostream &operator<<(std::ostream &os, Token tok)
{
    os << "Token(typ=" << static_cast<int>(tok.type)
       << ", dat=\"" << unescape_string(tok.raw)
       << "\")\n";
    
    return os;
}

int main(int argc, char *argv[])
{
    if (!set_utf8())
    {
        std::cout << "Couldn't change the locale setting to utf-8.\n\n"
                  << "If this causes unexpected errors,\n"
                  << "try opening an issue on the github repo.\n";
    }

    ARGS args = parse_args(argc, argv);

    char *src = open_file(&args);

    if (!src) {
        std::cout << "couldn't read file.\n";
        exit(1);
    }

    Lexer lex(src, args.filename.c_str());

    lex.get_tokens();

    for (size_t index = 0; index < lex.toks.size(); index++)
    {
        std::cout << lex.toks[index];
    }

    delete[] src;

    return 0;
}
