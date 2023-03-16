#include<iostream>
//#include "stdexcept"
//#include "numeric"

class Rational {
    //int64_t num, den;
public:
    Rational() = default;

    Rational(const Rational& r) = default;

    Rational(int64_t num, int64_t den);

    ~Rational() = default;

    Rational& operator=(const Rational& r) = default;

    Rational& operator+=(const Rational& r);

    Rational& operator-=(const Rational& r);

    Rational& operator*=(const Rational& r);

    Rational& operator/=(const Rational& r);

    Rational& operator++();

    Rational operator++(int);

    Rational& operator--();

    Rational operator--(int);

    bool operator==(const Rational& r);

    bool operator!=(const Rational& r);

    bool operator>(const Rational& r);

    bool operator<(const Rational& r);

    bool operator>=(const Rational& r);

    bool operator<=(const Rational& r);

    std::istream& ReadFrom(std::istream& istream);

    inline std::ostream& WriteTo(std::ostream& ostream) const;

    int64_t GetNum() const;

    int64_t GetDen() const;

private:
    int64_t num = 1;
    int64_t den = 1;

    void reduction();
};

Rational operator-(const Rational& r);

Rational operator+(const Rational& l, const Rational& r);

Rational operator-(const Rational& l, const Rational& r);

Rational operator*(const Rational& l, const Rational& r);

Rational operator/(const Rational& l, const Rational& r);

std::ostream& operator<<(std::ostream& ostream, const Rational& r);

std::istream& operator>>(std::istream& istream, Rational& r);
