//
// Created by aydar on 03.03.16.
//
#include "rational.h"

rational::rational(int v) {
    num = v;
    denom = 1;
}

rational::rational(int n, int d) {
    int twist = (d > 0) ? 1 : -1;
    num = n * twist;
    denom = d * twist;
    this->cast();
}

rational rational::operator+(const rational &a) const {
    rational res(this->num * a.denom + a.num * this->denom, this->denom * a.denom);
    res.cast();
    return res;
}

rational rational::operator-(const rational &a) const {
    rational res(this->num * a.denom - a.num * this->denom, this->denom * a.denom);
    res.cast();
    return res;
}

rational rational::operator*(const rational &a) const {
    rational res(this->num * a.num, this->denom * a.denom);
    res.cast();
    return res;
}

rational rational::operator/(const rational &a) const {
    int twist = (a.num > 0) ? 1 : -1;
    rational res(this->num * a.denom * twist, this->denom * a.num * twist);
    res.cast();
    return res;
}

int rational::getNum() const {
    return num;
}

int rational::getDenom() const {
    return denom;
}

void rational::cast() {
    int g = gcd(((num >= 0) ? num : -num), denom);
    num /= g;
    denom /= g;
}

int rational::gcd(int a, int b) {
    if (!a) {
        return b ? b : 1;
    }
    return gcd(b % a, a);
}