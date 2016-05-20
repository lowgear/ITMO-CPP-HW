//
// Created by aydar on 15.03.16.
//

#include "format.h"

#define UL unsigned long
#define S std::string

//const UL UNDEF = (const unsigned long) -2;

void applyTokens(std::queue<Token> &tokens, std::ostringstream &res) {
    if (tokens.empty())
        return;
    Token &curToken = tokens.front();
    if (curToken.str.empty())
        throw std::out_of_range(NO_ARGS);
    res << curToken.str;
    tokens.pop();
    applyTokens(tokens, res);
}

#define T int

template<>
UL checkInt<T>(T arg) {
    return (UL) arg;
}

#undef T

#define T unsigned int

template<>
UL checkInt<T>(T arg) {
    return (UL) arg;
}

#undef T

#define T long

template<>
UL checkInt<T>(T arg) {
    return (UL) arg;
}

#undef T

#define T unsigned long int

template<>
UL checkInt<T>(T arg) {
    return (UL) arg;
}

#undef T

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



template<typename T>
S prePrint(Token &token, T &arg) {
    S tmp = print(token, arg);
    token.spec = s;
    token.length = none;
    return formatString(token, tmp);
}

//s
#define T std::string

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == s &&
        token.length == none) {
        S s;
        if (token.width > arg.length()) {
            UL lack = token.width - arg.length();
            if (token.left)
                s = arg + S(lack, token.fill);
            else
                s = S(lack, token.fill) + arg;
        } else
            s = arg;
        /*for (UL i = 0; i < lack; i++)
            if (token.left)
                s += token.fill;
            else
                s = token.fill + s;*/
        return s;
    }
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T char*

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == s &&
        token.length == none) {
        auto s = std::string(arg);
        return formatString(token, s);
    }
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T const char*

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == s &&
        token.length == none) {
        auto s = std::string(arg);
        return formatString(token, s);
    }
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

//d
#define T int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == d && token.length == none)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T signed char
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == d && token.length == hh)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T short int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == d && token.length == h)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T long int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == d && token.length == l)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T long long int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == d && token.length == ll)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

//uoxX
#define T unsigned int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == u ||
         token.spec == o ||
         token.spec == x ||
         token.spec == X) &&
        token.length == none)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T unsigned char
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == u ||
         token.spec == o ||
         token.spec == x ||
         token.spec == X) &&
        token.length == hh)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T unsigned short int
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == u ||
         token.spec == o ||
         token.spec == x ||
         token.spec == X) &&
        token.length == h)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

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

//fFeEgGaA
#define T float

//template S prePrint(Token &, T &);
template S printFloat(Token &, T);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == f ||
         token.spec == F ||
         token.spec == e ||
         token.spec == E ||
         token.spec == g ||
         token.spec == G ||
         token.spec == a ||
         token.spec == A) &&
        token.length == none)
        return printFloat(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T double

//template S prePrint(Token &, T &);
template S printFloat(Token &, T);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == f ||
         token.spec == F ||
         token.spec == e ||
         token.spec == E ||
         token.spec == g ||
         token.spec == G ||
         token.spec == a ||
         token.spec == A) &&
        token.length == none)
        return printFloat(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

#define T long double

//template S prePrint(Token &, T &);
template S printFloat(Token &, T);

template<>
std::string formatString<T>(Token &token, T arg) {
    if ((token.spec == f ||
         token.spec == F ||
         token.spec == e ||
         token.spec == E ||
         token.spec == g ||
         token.spec == G ||
         token.spec == a ||
         token.spec == A) &&
        token.length == L)
        return printFloat(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

//c
#define T char
template S print(Token &, T &arg);
template S prePrint(Token &, T &);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == c &&
        token.length == none)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

//p
#define T void*
template S print(Token &, T &arg);
template S prePrint(Token &, T&);

template<>
std::string formatString<T>(Token &token, T arg) {
    if (token.spec == p &&
        token.length == none)
        return prePrint(token, arg);
    throw std::invalid_argument(WRONG_ARG);
}

#undef T

bool isSpec(const char c) {
    switch (c) {
        case 'd':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A':
        case 'c':
        case 's':
        case 'p':
        case 'n':
        case '%':
            return true;
        default:
            return false;
    }
}

void parseTokens(const std::string &string, std::queue<Token> &queue) {
    UL pos = 0;
    while (pos < string.length()) {
        UL end = pos;
        while (end < string.length() && string[end] != '%')
            end++;
        if (pos != end)
            queue.push(Token(string, pos, end));
        if (end >= string.length())
            break;
        pos = end;
        end++;
        while (end < string.length() && !isSpec(string[end]))
            end++;
        if (end >= string.length())
            throw std::invalid_argument(WRONG_SPEC);
        end++;
        queue.push(Token(string, pos, end));
        pos = end;
    }
}

Token::Token(const S &string, const UL begin, const UL end) {
    if (string[begin] != '%') {
        str = string.substr(begin, end - begin);
        return;
    }
    if (string.substr(begin, end - begin) == "%%") {
        str = "%";
        return;
    }
    UL pos = begin;
    while (true) {
        pos++;
        switch (string[pos]) {
            case '-':
                left = true;
                continue;
            case '+':
                sign = true;
                continue;
            case ' ':
                no_sign_is_space = true;
                continue;
            case '#':
                oct_hex_format = true;
                continue;
            case '0':
                fill = '0';
                continue;
            default:
                goto FLAG_END;
        }
        FLAG_END:
        break;
    }

    if (string[pos] == '*') {
        width = NEED_READ;
        pos++;
    } else {
        width = 0;
        while (isdigit(string[pos]))
            width = width * 10 + (string[pos++] - '0');
    }

    if (string[pos] == '.') {
        pos++;
        if (string[pos] == '*') {
            precision = NEED_READ;
            pos++;
        } else {
            if (!isdigit(string[pos]))
                throw std::invalid_argument(WRONG_SPEC);
            precision = 0;
            if (string[pos] != '0')
                while (isdigit(string[pos]))
                    precision = precision * 10 + (string[pos++] - '0');
            else
                pos++;
        }
    }

    S _length = string.substr(pos, end - 1 - pos);
    if (_length == S(""))
        length = none;
    else if (_length == "hh")
        length = hh;
    else if (_length == "h")
        length = h;
    else if (_length == "l")
        length = l;
    else if (_length == "ll")
        length = ll;
    else if (_length == "L")
        length = L;
    else
        throw std::invalid_argument(WRONG_SPEC);
    switch (string[end - 1]) {
        case 'd':
        case 'i':
            spec = d;
            break;
        case 'u':
            spec = u;
            break;
        case 'o':
            spec = o;
            break;
        case 'x':
            spec = x;
            break;
        case 'X':
            spec = X;
            break;
        case 'f':
            spec = f;
            break;
        case 'F':
            spec = F;
            break;
        case 'e':
            spec = e;
            break;
        case 'E':
            spec = E;
            break;
        case 'g':
            spec = g;
            break;
        case 'G':
            spec = G;
            break;
        case 'a':
            spec = a;
            break;
        case 'A':
            spec = A;
            break;
        case 'c':
            spec = c;
            break;
        case 's':
            spec = s;
            break;
        case 'p':
            spec = p;
            break;
        case 'n':
            spec = n;
            break;
        default:
            throw std::invalid_argument(WRONG_SPEC);
    }

    origin = string.substr(begin, end - begin);
}



#undef UL
#undef S
