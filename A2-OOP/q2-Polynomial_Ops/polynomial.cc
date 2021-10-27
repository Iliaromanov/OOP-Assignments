#include <iostream>
#include "polynomial.h"
#include "rational.h"

Polynomial::Polynomial() {
    this->coeffs = new Rational[1];
    this->coeffs[0] = Rational{0, 1};
    this->capacity = 1;
}     //creates the 0 polynomial

//Big five
Polynomial::~Polynomial() { // destructor
    delete [] this->coeffs;
    this->capacity= 0; 
}
Polynomial::Polynomial(const Polynomial &other) { // copy ctor
    delete [] coeffs; // clear old coeffs arr
    coeffs = new Rational[other.capacity];
    capacity = other.capacity;

    for (int i = 0; i < other.capacity; ++i) { // copy coeffs arr contents
        coeffs[i] = other.coeffs[i];
    }
}

Polynomial::Polynomial(Polynomial &&other) 
    : coeffs{other.coeffs}, capacity{other.capacity} {} // move ctor

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

}
Polynomial Polynomial::operator-(const Polynomial &rhs) const {

}
Polynomial Polynomial::operator*(const Polynomial &rhs) const {

}

//returns quotient after long division
Polynomial Polynomial::operator/(const Polynomial &rhs) const {

}

//returns remainder after long division
Polynomial Polynomial::operator%(const Polynomial &rhs) const {

}

// degree of the zero polynomial is -1
int Polynomial::degree() const {                      // <-------------------------------Not sure if this is covered by harness, double check. if not, test yourself.
    if (capacity == 1 && coeffs[0].num == 0) return -1;
    return capacity - 1;
}

// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly) {
    for (int i = poly.capacity - 1; i >=0; --i) {
        if (poly.coeffs[i].num) { // if numerator != 0
            out << "(" << poly.coeffs[i] << ")";
            if (i > 1) {
                out << "x^" << i << std::endl;
            } else if (i == 1) {
                out << "x" << std::endl;
            } else {
                out << std::endl;
            }
        }
    }
    return out;
}

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly) {
    Rational rat;
    int exp;

    in >> rat;
    in >> exp;

    delete [] poly.coeffs; 

    poly.coeffs = new Rational[exp + 1]; // allocate a new coeffs arr based on the highest exp
    poly.coeffs[exp] = rat;

    while (in) {
        in >> rat;
        in >> exp;
        poly.coeffs[exp] = rat; // <------------------------------------i think skipped exps would just be init using the default ctor, so they should be 0, but not sure
    }

    return in;
}