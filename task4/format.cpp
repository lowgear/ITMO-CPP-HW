//
// Created by aydar on 15.03.16.
//

#include "format.h"

template<typename ... Args>
std::string formatRealizationRequireArgument(FormatSpecifier &,
                                             std::string const &,
                                             unsigned long,
                                             unsigned long,
                                             Args ...);

template<typename ... Args>
std::string formatRealization(FormatSpecifier &,
                              std::string const &,
                              unsigned long,
                              Args ...);

template<typename T, typename ... Args>
std::string formatRealizationRequireValue(FormatSpecifier &,
                                          std::string const &,
                                          T,
                                          Args ...);

bool isFormatSpecifierBegin(char c) {
    return c == '%';
}

bool isSpecifier(char c) {
    return (c == 'd' ||
            c == 'i' ||
            c == 'u' ||
            c == 'o' ||
            c == 'x' ||
            c == 'X' ||
            c == 'f' ||
            c == 'F' ||
            c == 'e' ||
            c == 'E' ||
            c == 'g' ||
            c == 'G' ||
            c == 'a' ||
            c == 'A' ||
            c == 'c' ||
            c == 's' ||
            c == 'p' ||
            c == 'n' ||
            c == '%');
}

bool isFlag(char c) {
    return (c == '-' ||
            c == '+' ||
            c == ' ' ||
            c == '#' ||
            c == '0');
}

struct FormatSpecifier {
    std::string flags;
    char specifier;
    int width;
    int precision;

    FormatSpecifier() {
        specifier = 0;
        width = -1;
        precision = -1;
    }

    FormatSpecifier(std::string const &format) {

    }

    bool requireArgument() {
    }

    bool requireValue() {
        return (specifier == 'd' ||
                specifier == 'i' ||
                specifier == 'u' ||
                specifier == 'o' ||
                specifier == 'x' ||
                specifier == 'X' ||
                specifier == 'f' ||
                specifier == 'F' ||
                specifier == 'e' ||
                specifier == 'E' ||
                specifier == 'g' ||
                specifier == 'G' ||
                specifier == 'a' ||
                specifier == 'A' ||
                specifier == 'c' ||
                specifier == 's' ||
                specifier == 'p' ||
                specifier == 'n');
    }

    std::string print() {

    }

    template<typename T>
    std::string print(T arg) {

    }

    void getArgument(unsigned long arg) {

    }
};

template<typename ... Args>
std::string format(std::string const &format, Args ... args) {
    FormatSpecifier formatSpecifier;
    return formatRealization(formatSpecifier, format, 0, args);
}

template<typename ... Args>
std::string formatRealization(FormatSpecifier &formatSpecifier, std::string const &format, unsigned long begin,
                              Args ... args) {
    //Find where first format specifier begins
    unsigned long noSpecifierPrefixLength;
    for (noSpecifierPrefixLength = 0;
         begin + noSpecifierPrefixLength < format.length() &&
         !isFormatSpecifierBegin(format[begin + noSpecifierPrefixLength]);
         noSpecifierPrefixLength++);

    //No format specifiers found
    if (begin + noSpecifierPrefixLength == format.length())
        return format.substr(begin);

    //Find first format specifier's length
    unsigned long specifierLength;
    for (specifierLength = 1;
         begin + noSpecifierPrefixLength + specifierLength < format.length() &&
         !isSpecifier(format[begin + noSpecifierPrefixLength + specifierLength]);
         specifierLength++);

    formatSpecifier.FormatSpecifier(format.substr(begin + noSpecifierPrefixLength, specifierLength));

    if (formatSpecifier.requireArgument() || formatSpecifier.requireValue())
        return format.substr(begin, noSpecifierPrefixLength) +
               formatRealizationRequireArgument(formatSpecifier,
                                                format,
                                                begin + noSpecifierPrefixLength + specifierLength,
                                                args);

    return format.substr(begin, noSpecifierPrefixLength) +
           formatSpecifier.print() +
           formatRealization(formatSpecifier,
                             format,
                             begin + noSpecifierPrefixLength + specifierLength,
                             args);
}

template<typename ... Args>
std::string formatRealizationRequireArgument(FormatSpecifier &formatSpecifier,
                                             std::string const &format,
                                             unsigned long begin,
                                             unsigned long arg,
                                             Args ... args) {
    formatSpecifier.getArgument(arg);
    if (formatSpecifier.requireArgument())
        return formatRealizationRequireArgument(formatSpecifier,
                                                format,
                                                begin,
                                                args);
    if (formatSpecifier.requireValue())
        return formatRealizationRequireValue(formatSpecifier,
                                             format,
                                             begin,
                                             args);
    return formatSpecifier.print() +
           formatRealization(formatSpecifier,
                             format,
                             begin,
                             args);
}

template<typename T, typename ... Args>
std::string formatRealizationRequireValue(FormatSpecifier &formatSpecifier,
                                          std::string const &format,
                                          unsigned long begin,
                                          T arg,
                                          Args ... args) {
    return formatSpecifier.print(arg) +
           formatRealization(formatSpecifier,
                             format,
                             begin,
                             args);
}