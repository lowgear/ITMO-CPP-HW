class rational {
private:
    int num;
    unsigned int denom;
    static unsigned int gcd(unsigned int, unsigned int);
    void cast();

public:
    rational(int);
    rational(int, int);
    rational operator+(const rational&) const;
    rational operator-(const rational&) const;
    rational operator*(const rational&) const;
    rational operator/(const rational&) const;
    int getNum() const;
    unsigned int getDenom() const;
};

rational::rational(int v) {
    num = v;
    denom = 1;
}

rational::rational(int n, int d) {
    num = n;
    denom = d;
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
    rational res(this->num * a.denom * twist, this->denom * (unsigned int)(a.num * twist));
    res.cast();
    return res;
}

int rational::getNum() const {
    return num;
}

unsigned int rational::getDenom() const {
    return denom;
}

void rational::cast() {
    unsigned int g = gcd((unsigned int)((num >= 0) ? num : -num), denom);
    num /= g;
    denom /= g;
}

unsigned int rational::gcd(unsigned int a, unsigned int b) {
    if (!a) {
        return b ? b : 1;
    }
    return gcd(b % a, a);
}