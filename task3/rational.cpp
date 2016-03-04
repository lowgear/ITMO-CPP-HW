//
// Created by aydar on 03.03.16.
//
#include "rational.h"

rational::rational(int v) {
    num = v;
    denom = 1;
}

rational::rational(int n, int d) {
    num = n;
    denom = d;
    cast();
}

rational rational::operator+(const rational &a) const {
    return rational(this->num * a.denom + a.num * this->denom, this->denom * a.denom);
}

rational rational::operator-(const rational &a) const {
    return rational(this->num * a.denom - a.num * this->denom, this->denom * a.denom);
}

rational rational::operator*(const rational &a) const {
    return rational(this->num * a.num, this->denom * a.denom);
}

rational rational::operator/(const rational &a) const {
    return rational(this->num * a.denom, this->denom * a.num);
}

int rational::getNum() const {
    return num;
}

int rational::getDenom() const {
    return denom;
}

void rational::cast() {
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
    int g = gcd((num > 0) ? num : -num, denom);
    num /= g;
    denom /= g;
}

int rational::gcd(int a, int b) {
    if (!a) {
        return b ? b : 1;
    }
    return gcd(b % a, a);
}