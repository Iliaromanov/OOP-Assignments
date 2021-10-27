#include "rational.h"
#include <iostream>


// helper gcd func
int gcd(int n, int m) {
    int tmp;
    while (m != 0) {
        tmp = m;
        m = n % m;
        n = tmp;
    }
    return n;
}

void Rational::simplify() {
    int num = this->num;
    int den = this->den;

    int g = gcd(num, den);

    this->num /= g;
    this->den /= g;

    if (this->den < 0 && this->num >= 0) { // a/-b => -a/b
        this->num *= -1;
        this->den *= -1;
    }
}

Rational::Rational(int num, int den) {
    this->num = num;
    this->den = den;
    this->simplify();
}


Rational Rational::operator+(const Rational &rhs) const {
    Rational result{this->num*rhs.den + this->den*rhs.num, this->den*rhs.den};
    return result;
}
Rational Rational::operator-(const Rational &rhs) const {
    Rational result{this->num*rhs.den - this->den*rhs.num, this->den*rhs.den};
    return result;
}
Rational Rational::operator*(const Rational &rhs) const {
    Rational result{this->num*rhs.num, this->den*rhs.den};
    return result;
}
Rational Rational::operator/(const Rational &rhs) const {
    Rational result{this->num*rhs.den, this->den*rhs.num};
    return result;
}

Rational &Rational::operator+=(const Rational &rhs) {
    Rational result{this->num*rhs.den + this->den*rhs.num, this->den*rhs.den};
    *this = result;

    return *this;
}
Rational &Rational::operator-=(const Rational &rhs) {
    Rational result{this->num*rhs.den - this->den*rhs.num, this->den*rhs.den};
    *this = result;

    return *this;
}
Rational Rational::operator-() const {
    Rational result{this->num*-1, this->den};
    return result;
}

int Rational::getNumerator() const {
    return this->num;
}
int Rational::getDenominator() const {
    return this->den;
}


std::ostream &operator<<(std::ostream &out, const Rational &rat) {
    if (rat.den == 1) {
        out << rat.num;
    } else {
        out << rat.num << "/" << rat.den;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Rational &rat) {
    int numerator;
    int denomenator;
    
    in >> numerator;
    in >> denomenator;
    in.clear();
    in.ignore();
    in >> denomenator;

    rat.num = numerator;
    rat.den = denomenator;
    rat.simplify();

    return in;
}
