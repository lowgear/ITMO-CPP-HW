//
// Created by aydar on 20.05.16.
//

#include <string>
#include <istream>
#include <ostream>
#include <memory>

#ifndef TASK_LAZY_STRING_H
#define TASK_LAZY_STRING_H
/*
 *Class implementing copy-on-write strings.
*/
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
    /*
     * @return Empty string.
     *
     * */
    lazy_string();

    /*
     * @_str String to construct lazy_string from.
     *
     * @return String equivalent to _str.
     *
     * */
    lazy_string(const std::string & _str);

    /*
     * @return Size of internal storage of string.
     */
    size_t size();

    /*
     * @return Amount of characters in string.
     */
    size_t length();

    /*
     * @pos Index of char in string wanted.
     *
     * @return "Smart" reference to the char at pos which provides mutability.
     */
    ref at(size_t pos);

    /*
     * @pos Index of char in string wanted.
     *
     * @return Char code of char at pos.
     */
    char at(size_t pos) const;

    /*
     * @pos Index of char in string wanted.
     *
     * @return "Smart" reference to the char at pos which provides mutability.
     */
    ref operator[](size_t pos);

    /*
     * @pos Index of char in string wanted.
     *
     * @return Char code of char at pos.
     */
    const char &operator[](size_t pos) const;

    /*
     * @pos Index from which wanted substring starts. By default substring matches string and pos is 0.
     *
     * @len Length of wanted substring. By default is so that all chars till the end are taken.
     *
     * @return Lasy_string from pos of length min of len and chars after pos.
     */
    lazy_string substr(size_t pos = 0, size_t len = std::string::npos) const;

    /*
     * @return std::string object equivalent to this.
     */
    operator std::string() const;

    /*
     * @in Stream to read from.
     *
     * @tar Lazy_string to read to.
     */
    friend std::istream &operator>>(std::istream &in, lazy_string &tar);

    /*
     * @out Stream to write to.
     *
     * @tar Lazy_string to write.
     */
    friend std::ostream &operator<<(std::ostream &out, const lazy_string &tar);
};

#endif //TASK_LAZY_STRING_H
