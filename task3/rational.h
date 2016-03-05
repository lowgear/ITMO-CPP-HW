#ifndef RATIONAL
class rational {
private:
    int num;
    int denom;
    static int gcd(int, int);
    void cast();

public:
    rational(int n, int d  = 1);
    rational operator+(const rational&) const;
    rational operator-(const rational&) const;
    rational operator*(const rational&) const;
    rational operator/(const rational&) const;
    int getNum() const;
    int getDenom() const;
};
#endif
#define RATIONAL