#pragma once

#include "pang.hh"
#include "unicode_escape.hh"
#include <iostream>
#include <unordered_set>
#include <vector>
#include <memory>
#include <string>

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
