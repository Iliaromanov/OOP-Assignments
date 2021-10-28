#include <iostream>
#include <sstream>
#include "polynomial.h"
#include "rational.h"
using std::cout;
using std::endl;

Polynomial::Polynomial() {
    coeffs = new Rational[1];
    coeffs[0] = Rational{0, 1};
    capacity = 1;
}     //creates the 0 polynomial

//Big five
Polynomial::~Polynomial() { // destructor
    delete [] coeffs;
    capacity = 0; 
}

Polynomial::Polynomial(const Polynomial &other) { // copy ctor
    coeffs = new Rational[other.capacity];
    capacity = other.capacity;

    for (int i = 0; i < other.capacity; ++i) { // copy coeffs arr contents
        coeffs[i] = other.coeffs[i];
    }
}

Polynomial::Polynomial(Polynomial &&other) 
    : coeffs{other.coeffs}, capacity{other.capacity} {
        other.coeffs = nullptr;
} // move ctor

Polynomial &Polynomial::operator=(const Polynomial &other) { // copy assignment operator
    if (this == &other) return *this; // check for self assignment
    Polynomial tmp{other};
    swap(tmp);
    return *this;
}

Polynomial &Polynomial::operator=(Polynomial &&other) { // move assignment operator
    swap(other);
    return *this;
}

// Arithmetic operations behave in the standard way 
Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    Polynomial result;
    result.capacity = this->degree() >= rhs.degree() ? this->degree() + 1 : rhs.degree() + 1;
    delete [] result.coeffs;
    result.coeffs = new Rational[result.capacity];

    for (int i = 0; i < result.capacity; ++ i) {
        Rational l = Rational{0,1};
        Rational r = Rational{0,1};
        if (i < this->capacity) l = this->coeffs[i];
        if (i < rhs.capacity) r = rhs.coeffs[i];
        result.coeffs[i] = l + r;
    }

    return result;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const {
    Polynomial result;
    result.capacity = this->degree() >= rhs.degree() ? this->degree() + 1 : rhs.degree() + 1;
    delete [] result.coeffs;
    result.coeffs = new Rational[result.capacity];

    for (int i = 0; i < result.capacity; ++ i) {
        Rational l = Rational{0,1};
        Rational r = Rational{0,1};
        if (i < this->capacity) l = this->coeffs[i];
        if (i < rhs.capacity) r = rhs.coeffs[i];
        result.coeffs[i] = l - r;
    }

    return result;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
    Polynomial result;
    int cap = this->degree() + rhs.degree() + 1;

    for (int i = this->degree(); i >= 0; --i) {
        Polynomial tmp;
        delete [] tmp.coeffs;
        tmp.coeffs = new Rational[cap];
        tmp.capacity = cap;
        for (int j = rhs.degree(); j >= 0; --j) {
            tmp.coeffs[i + j] = this->coeffs[i] * rhs.coeffs[j];
        }
        result = result + tmp;
    }

    return result;
}

//returns quotient after long division
Polynomial Polynomial::operator/(const Polynomial &rhs) const {
    Polynomial quotient;
    if (this->degree() == -1) return quotient; // 0 pol div by anything is 0
    Polynomial r = *this;

    while (r.degree() >= rhs.degree()) {
        Polynomial cur_quotient_term;
        delete [] cur_quotient_term.coeffs;
        cur_quotient_term.coeffs = new Rational[r.degree() - rhs.degree() + 1];
        cur_quotient_term.capacity = r.degree() - rhs.degree() + 1;
        cur_quotient_term.coeffs[r.degree() - rhs.degree()] = r.coeffs[r.degree()] / rhs.coeffs[rhs.degree()];

        Polynomial intermediate_product = cur_quotient_term * rhs;
        r = r - intermediate_product;

        quotient = quotient + cur_quotient_term;
    }

    return quotient;
}

//returns remainder after long division
Polynomial Polynomial::operator%(const Polynomial &rhs) const {
    return *this - (rhs * (*this / rhs));
}

// degree of the zero polynomial is -1
int Polynomial::degree() const {
    for (int i = capacity - 1; i >= 0; --i) {
        if (this->coeffs[i].num) return i;
    }
    return -1; // zero polynomial
}


// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly) {
    bool first_printed = false;
    for (int i = poly.capacity - 1; i >=0; --i) {
        if (poly.coeffs[i].num) { // if numerator != 0
            if (first_printed) out << " + ";
            first_printed = true;
            out << "(" << poly.coeffs[i] << ")";
            if (i > 1) {
                out << "x^" << i;
            } else if (i == 1) {
                out << "x";
            }
        }
    }
    if (!first_printed) out << 0;

    return out;
}

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly) {
    std::string poly_str;
    getline(in, poly_str); // read in input until newline
    std::istringstream poly_in{poly_str};  // convert to string stream

    Rational rat;
    int exp;

    poly_in >> rat;
    poly_in >> exp;

    delete [] poly.coeffs;

    poly.coeffs = new Rational[exp + 1]; // allocate a new coeffs arr based on the highest exp

    poly.capacity = exp + 1;
    poly.coeffs[exp] = rat;

    while (poly_in) { // read from string stream
        poly_in >> rat;
        poly_in >> exp;
        poly.coeffs[exp] = rat;
    }

    return in;
}