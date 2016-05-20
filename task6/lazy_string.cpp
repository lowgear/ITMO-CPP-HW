//
// Created by aydar on 20.05.16.
//

#include <iostream>
#include <string>
#include "lazy_string.h"

lazy_string::lazy_string(const std::string &string) {
    p = std::shared_ptr<std::string>(new std::string(string));
    begin = 0;
    ln = string.length();
}

size_t lazy_string::size() {
    return p->size();
}

size_t lazy_string::length() {
    return ln;
}

lazy_string::ref lazy_string::at(size_t i) {
    if (i >= ln)
        throw std::out_of_range("Argument is too big.");
    return ref(this, i + begin);
}

char lazy_string::at(size_t i) const {
    if (i >= ln)
        throw std::out_of_range("Argument is too big.");
    return p->at(begin + i);
}

lazy_string::ref lazy_string::operator[](size_t i) {
    if (i >= ln)
        throw std::out_of_range("Argument is too big.");
    return ref(this, i + begin);
}

const char &lazy_string::operator[](size_t i) const {
    if (i >= ln)
        throw std::out_of_range("Argument is too big.");
    return (*p)[begin + i];
}

size_t min(size_t a, size_t b) {
    if (a < b)
        return a;
    return b;
}

lazy_string lazy_string::substr(size_t _begin, size_t _ln) const {
    if (_begin > ln)
        throw std::out_of_range("pos is out of range.");
    if (_ln == 0 || _begin == ln)
        return lazy_string();
    lazy_string res;
    res.p = p;
    res.begin = begin + _begin;
    res.ln = min(_ln, ln - _begin);
    return res;
}

lazy_string::lazy_string() {
    p = std::shared_ptr<std::string>();
    begin = ln = 0;
}

lazy_string::ref::ref(lazy_string *str, size_t pos) : str(str), pos(pos) { }

lazy_string::ref::operator char() const {
    return (*str->p)[pos];
}

lazy_string::ref &lazy_string::ref::operator=(const char c) {
    if (str->p.use_count() > 1) {
        str->p = std::make_shared<std::string>(str->p->substr(str->begin, str->ln));
        //str->p = std::shared_ptr<std::string>(new std::string(str->p->substr(str->begin, str->ln)));
        str->begin = 0;
    }
    (*str->p)[pos] = c;
    return *this;
}

std::istream &operator>>(std::istream &istream, lazy_string &string) {
    std::string tmp;
    istream >> tmp;
    string = lazy_string(tmp);
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const lazy_string &string) {
    ostream << std::string(string);
    return ostream;
}

lazy_string::operator std::string() const {
    return p->substr(begin, ln);
}

lazy_string::ref &lazy_string::ref::operator=(const lazy_string::ref &c) {
    char tmp = c;
    *this = tmp;
    return *this;
}
