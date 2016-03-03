class rational {
private:
    int num;
    int denom;
    static int gcd(int, int);
    void cast();

public:
    rational(int);
    rational(int, int);
    rational operator+(const rational&) const;
    rational operator-(const rational&) const;
    rational operator*(const rational&) const;
    rational operator/(const rational&) const;
    int getNum() const;
    int getDenom() const;
};