#pragma once

#include "unicode_escape.hh"

#include <locale.h>
#include <string.h>

#include <unordered_set>
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


class Token
{
    public:
        enum class TokenType
        {
            Integer,
            String,
            Character,
            Identifier,
            OpenBracket,
            CloseBracket,
            OpenSquare,
            CloseSquare,
            OpenCurly,
            CloseCurly,
            LessThan,
            GreaterThan,
            Equal,
            NotEqual,
            Keyword,
        };

        Token(TokenType tok_type) noexcept : type{tok_type} {}
        Token(TokenType tok_type, const char* beg, std::size_t len) noexcept 
            : type{tok_type}, raw(beg, len) {}
        Token(TokenType tok_type, std::string_view str) noexcept
            : type{tok_type}, raw{str} {}

        TokenType        type {};
        std::string_view raw  {};
};

extern std::unordered_set<std::string_view> keywords;

class Lexer
{
    public:
        Lexer(
            const char *source,
            const char *filename
        ) noexcept : src{source}, fn{filename},
                     index{0}, ended{false} {}
        
        inline void inc()
        {
            if (src[index] == '\n')
                line++;
            else if (src[index] == '\0')
                ended = true;

            index++;
        }

        inline char peek()
        {
            return src[index];
        }
        
        inline char get()
        {
            inc();
            return src[index - 1];
        }

        inline void atom(Token::TokenType typ)
        {
            toks.push_back(Token(typ, src + index, 1));
            inc();
        }

        void skip_whitespace();
        void identifier();
        void num();
        void string();
        void raw_string();
        void get_tokens();
        void print_tokens();

        const char         *src;
        const char         *fn;
        size_t              index;
        size_t              line;
        bool                ended;
        std::vector<Token>  toks;
};
