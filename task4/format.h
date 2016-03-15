//
// Created by aydar on 15.03.16.
//

#ifndef FORMAT_FORMAT_H
#define FORMAT_FORMAT_H
#include <string>
#include <stdexcept>

template <typename ... Args>
std::string format(std::string const &format, Args ... args);
#endif //FORMAT_FORMAT_H
