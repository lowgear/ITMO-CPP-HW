//
// Created by aydar on 20.05.16.
//

#include <string>
#include <istream>
#include <ostream>
#include <memory>

#ifndef TASK_LAZY_STRING_H
#define TASK_LAZY_STRING_H

class lazy_string {
private:
    std::shared_ptr<std::string> p;
    size_t begin;
    size_t ln;

    class ref {
        friend class lazy_string;
    private:
        lazy_string *const str;
        const size_t pos;
    public:
        ref(lazy_string *, size_t);

        operator char() const;

        ref &operator=(char);
        ref &operator=(const ref&);
    };

public:
    lazy_string();

    lazy_string(const std::string &);

    size_t size();

    size_t length();

    ref at(size_t);

    char at(size_t) const;

    ref operator[](size_t);

    const char &operator[](size_t) const;

    lazy_string substr(size_t pos = 0, size_t len = std::string::npos) const;

    size_t min(size_t a, size_t b) const;

    operator std::string() const;

    friend std::istream &operator>>(std::istream &, lazy_string &);

    friend std::ostream &operator<<(std::ostream &, const lazy_string &);
};

#endif //TASK_LAZY_STRING_H
