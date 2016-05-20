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
const UL MIN_C_STR_LEN = 400;

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

template <typename T>
S printFloat(Token &token, T arg) {
    S res;
    std::ostringstream _res;
    switch (token.spec) {
        case F:
            _res << std::uppercase;
        case f:
            _res << std::fixed;
            break;
        case E:
            _res << std::uppercase;
        case e:
            _res << std::scientific;
            break;
        case G:
            _res << std::uppercase;
        case g:
            //TODO: shortest rep
            break;
        case A:
        case a:
            return "";//TODO: hexFloat
    }

    if (arg < 0) {
        _res << "-";
        arg = -arg;
    }
    else if (token.sign)
        _res << "+";
    else if (token.no_sign_is_space)
        _res << " ";

    if (token.precision != DEFAULT_PREC)
        _res.precision(token.precision);

    _res << arg;
    res = _res.str();

    if (token.width > res.length()) {
        UL lack = token.width - res.length();
        if (token.left)
            res = res + S(lack, token.fill);
        else
            res = S(lack, token.fill) + res;
    }

    return res;
}

void applyTokens(std::queue<Token> &, S &);

template<typename T, typename ... Args>
void applyTokens(std::queue<Token> &tokens, S &res, const T curArg, const Args ... args) {
    if (tokens.empty()) {
        if (sizeof ... (args))
            throw std::out_of_range(NO_ARGS);
        else
            return;
    }
    Token &curToken = tokens.front();
    if (!curToken.str.empty()) {
        res += curToken.str;
        tokens.pop();
        applyTokens(tokens, res, curArg, args...);
        return;
    }
    if (curToken.width == NEED_READ) {
        curToken.width = checkInt(curArg);
    } else if (curToken.precision == NEED_READ) {
        curToken.precision = checkInt(curArg);
    } else {
        res += formatString(curToken, curArg);
        tokens.pop();
    }
    applyTokens(tokens, res, args...);
};

template<typename ... Args>
S format(S const format, Args ... args) {
    std::queue<Token> tokens;
    parseTokens(format, tokens);

    S res = "";
    applyTokens(tokens, res, args...);

    return res;
};

template<typename T>
S print(Token &token, T &arg) {
    UL wBeg = 0;
    S &spec = token.origin;
    const char *cSpec;
    while (wBeg < spec.length() && (spec[wBeg] == '0' || !isdigit(spec[wBeg])) && spec[wBeg] != '.' &&
           spec[wBeg] != '*')
        wBeg++;
    UL wEnd = wBeg;
    if (spec[wBeg] != '*') {
        while (wEnd < spec.length() && isdigit(spec[wEnd]))
            wEnd++;
    } else
        wEnd++;
    spec = spec.substr(0, wBeg) + spec.substr(wEnd);
    cSpec = spec.c_str();

    char *c_res = new char[MIN_C_STR_LEN];
    sprintf(c_res, cSpec, arg);
    S res = S(c_res);
    delete[] c_res;

    return res;
}

#undef UL
#undef S
#endif //FORMAT_FORMAT_H
