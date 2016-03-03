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