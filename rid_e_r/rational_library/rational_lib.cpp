#include <iostream>
#include "rational_lib.hpp"


Rational::Rational(int64_t num, int64_t den): num(num), den(den) {
    if (den == 0) {
        throw std::runtime_error("Zero division");
    }
    if (num * den < 0) {
        this->num = -std::abs(num);
        this->den = std::abs(den);
    }
    reduction();
}


int64_t gcd(int64_t a, int64_t b) {
    while (a) {
        auto t = b % a;
        b = a;
        a = t;
    }
    return b;
}


void Rational::reduction() {
    auto g = gcd(num < 0 ? -num : num, den);
    num /= g;
    den /= g;
}


Rational operator-(const Rational& r) {
    return {-r.GetNum(), r.GetDen()};
}


Rational& Rational::operator+=(const Rational& r) {
    int64_t lmc = den * r.GetDen() / gcd(den, r.GetDen());
    num *= lmc / den;
    den *= lmc / den;
    num += r.GetNum() * lmc / r.GetDen();
    reduction();
    return *this;
}


Rational operator+(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational += r;
    return rational;
}


Rational& Rational::operator-=(const Rational& r) {
    this->operator+=(-r);
    return *this;
}


Rational operator-(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational -= r;
    return rational;
}


Rational& Rational::operator*=(const Rational& r) {
    this->num *= r.GetNum();
    this->den *= r.GetDen();
    reduction();
    return *this;
}


Rational operator*(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational *= r;
    return rational;
}


Rational& Rational::operator/=(const Rational& r) {
    if (r.GetNum() == 0) {
        throw std::runtime_error("Zero division");
    }
    this->num *= r.GetDen();
    this->den *= r.GetNum();
    reduction();
    return *this;
}


Rational operator/(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational /= r;
    return rational;
}


Rational& Rational::operator++() {
    this->operator+=(Rational(1, 1));
    return *this;
}


Rational Rational::operator++(int) {
    Rational temp(*this);
    ++*this;
    return temp;
}


Rational& Rational::operator--() {
    this->operator-=(Rational(1, 1));
    return *this;
}


Rational Rational::operator--(int) {
    Rational temp(*this);
    --*this;
    return temp;
}


bool Rational::operator==(const Rational& r) {
    return this->GetNum() == r.GetNum() && this->GetDen() == r.GetDen();
}


bool Rational::operator!=(const Rational& r) {
    return !operator==(r);
}


bool Rational::operator>(const Rational& r) {
    return (this->GetNum() / (double) this->GetDen()) > (r.GetNum() / (double) r.GetDen());
}


bool Rational::operator<(const Rational& r) {
    return !(operator>(r) || operator==(r));
}


bool Rational::operator>=(const Rational& r) {
    return !operator<(r);
}


bool Rational::operator<=(const Rational& r) {
    return !operator>(r);
}


int64_t Rational::GetNum() const {
    return num;
}


int64_t Rational::GetDen() const {
    return den;
}


std::istream& Rational::ReadFrom(std::istream& istream) {
    int64_t numI = 0;
    int64_t denomI = 0;
    char separator = 0;
    istream >> numI >> separator >> denomI;
    if (istream.good()) {
        if (den == 0) {
            throw std::runtime_error("Zero division");
        }
        if (denomI < 0 || separator != '/') {
            istream.setstate(std::ios_base::failbit);
        } else {
            num = numI;
            den = denomI;
            reduction();
        }
    }
    return istream;
}


inline std::ostream& Rational::WriteTo(std::ostream& ostream) const {
    ostream << GetNum() << '/' << GetDen() << "\n";
    return ostream;
}


std::ostream& operator<<(std::ostream& ostream, const Rational& r) {
    r.WriteTo(ostream);
    return ostream;
}


std::istream& operator>>(std::istream& istream, Rational& r) {
    r.ReadFrom(istream);
    return istream;
}