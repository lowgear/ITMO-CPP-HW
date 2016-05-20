//
// Created by aydar on 15.03.16.
//

#ifndef FORMAT_FORMAT_H
#define FORMAT_FORMAT_H

#define UL unsigned long
#define S std::string

#include <string>
#include <stdexcept>
#include <cstdio>
#include <queue>
#include <sstream>

const UL NEED_READ = (const unsigned long) -1;
const UL DEFAULT_PREC = (const unsigned long) -2;
const UL MIN_C_STR_LEN = 30;

const S NO_ARGS = "Not enough arguments.";
const S NOT_INT = "Integer value expected.";
const S WRONG_ARG = "Argument's type mismatch.";
const S WRONG_SPEC = "Invalid specifier found.";

enum Spec {
    d, u, o, x, X, f, F, e, E, g, G, a, A, c, s, p, n
};
enum Length {
    none, hh, h, l, ll, L
};

struct Token {
    UL width = 0;
    UL precision = DEFAULT_PREC;
    S str;
    Spec spec;
    Length length;
    bool left = false;
    bool sign = false;
    bool oct_hex_format = false;
    bool no_sign_is_space = false;
    char fill = ' ';
    S origin;

    Token(const S &, UL, UL);
};

void parseTokens(S const &, std::queue<Token> &);

template<typename T>
UL checkInt(T) {
    throw std::invalid_argument(NOT_INT);
};

template<typename T>
S formatString(Token &token, T arg) {
    throw std::invalid_argument(WRONG_ARG);
};

void applyTokens(std::queue<Token> &, std::ostringstream &);

template<typename T, typename ... Args>
void applyTokens(std::queue<Token> &tokens, std::ostringstream &res, const T curArg, const Args ... args) {
    if (tokens.empty()) {
        if (sizeof ... (args))
            throw std::out_of_range(NO_ARGS);
        else
            return;
    }
    Token &curToken = tokens.front();
    if (!curToken.str.empty()) {
        res << curToken.str;
        tokens.pop();
        applyTokens(tokens, res, curArg, args...);
        return;
    }
    if (curToken.width == NEED_READ) {
        curToken.width = checkInt(curArg);
    } else if (curToken.precision == NEED_READ) {
        curToken.precision = checkInt(curArg);
    } else {
        res << formatString(curToken, curArg);
        tokens.pop();
    }
    applyTokens(tokens, res, args...);
};

template<typename ... Args>
S format(S const format, Args ... args) {
    std::queue<Token> tokens;
    parseTokens(format, tokens);

    std::ostringstream res;
    applyTokens(tokens, res, args...);

    return res.str();
};

#undef UL
#undef S
#endif //FORMAT_FORMAT_H
