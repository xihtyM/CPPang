#include "../include/pang.hh"

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

    for (int counter = 1; argv[counter]; counter++)
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
        else if (arg_equ(cur, "output"))
            output = true;
        else if (strcmp(cur, "-S") == 0)
            args.to_asm = true;
        else if (arg_equ(cur, "Object"))
            args.to_obj = true;
        else if (arg_equ(cur, "run"))
            args.run_on_compile = true;
        //else if (cur)
        else {
            if (!args.filename.empty())
            {
                // TODO: throw error
            }
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

bool is_whitespace(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            return true;
        default:
            return false;
    }
}

bool is_identifier(char c)
{
    switch (c)
    {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
            return true;
        default:
            return false;
    }
}

bool is_num(char c)
{
    switch (c)
    {
        case '+':
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

void Lexer::skip_whitespace()
{
    while (is_whitespace(peek())) {
        inc();
        if (ended) return;
    }
}


void Lexer::identifier()
{
    const char *start = (src + index);
    inc();
    while (is_identifier(peek())) {
        inc();
        if (ended) return;
    }
    toks.push_back(Token(
        Token::TokenType::Identifier, start, (src + index) - start));
}


void Lexer::num()
{

}
void Lexer::string()
{

}
void Lexer::raw_string()
{

}

void Lexer::get_tokens()
{
    while (!ended) {
        skip_whitespace();

        if (ended)
        {
            return;
        }

        if (is_identifier(peek())) {
            identifier();
            continue;
        }//} else if (is_num(peek())) {
        //    num();
        //    continue;
        //}

        switch (peek()) {
            case '(':
                atom(Token::TokenType::OpenBracket);
                break;
            case ')':
                atom(Token::TokenType::CloseBracket);
                break;
            case '<':
                atom(Token::TokenType::LessThan);
                break;
            case '>':
                atom(Token::TokenType::GreaterThan);
                break;
            case '=':
                atom(Token::TokenType::Equal);
                break;
            case '!':
                atom(Token::TokenType::NotEqual);
                break;
            default:
                inc();
                break;
        }
    }
}
