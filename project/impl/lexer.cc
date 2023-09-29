#include "../include/lexer.hh"

void Lexer::skip_whitespace()
{
    while (is_whitespace(peek())) {
        inc();
        if (ended) return;
    }
}


void Lexer::identifier()
{
    const char *const start = (src + index);
    inc();
    while (is_identifier(peek())) {
        inc();
        if (ended) break;
    }
    
    std::string_view id(start, (src + index) - start);

    if (keywords.find(id) != keywords.end())
    {
        toks.push_back(Token(
            Token::TokenType::Keyword, id));
        return;
    }

    toks.push_back(Token(
        Token::TokenType::Identifier, id));
}


void Lexer::num()
{
    const char *const start = (src + index);

    inc(); // skip +, - or starting digit

    while (is_num(peek()))
    {
        inc();
        if (ended) break;
    }

    // if hex or octal
    switch (peek())
    {
        case 'x':
        case 'o':
        {
            inc(); // skip x or o
            while (is_num(peek()))
            {
                inc();
                if (ended) break;
            }
        }
    }

    toks.push_back(Token(
        Token::TokenType::Integer, 
        start,
        (src + index) - start
    ));
}

void Lexer::string()
{
    inc();
    const char *const start = (src + index);

    while (peek() != '\"') {
        inc();

        if (ended) {
            std::cout << "err\n";
            return;
        }

        if (peek() == '\"' && src[index - 1] == '\\' && src[index - 2] != '\\')
            inc();
    }

    std::string escaped_string = escape_string(
        std::string_view(start, (src + index) - start));

    //
    // copy into char array because when
    // it goes out of scope it causes
    // undefined behaivour
    //

    std::unique_ptr<char[]> dat(new char[escaped_string.length()]);
    char *save = dat.get();
    
    for (char ch: escaped_string)
    {
        *save = ch;
        save++;
    }
    
    toks.push_back(Token(
        Token::TokenType::String, 
            dat.get(),
            escaped_string.length()
        ));
    
    inc();
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

        switch (peek()) {
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
                identifier();
                break;
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
                num();
                break;
            case '\"':
                string();
                break;
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
