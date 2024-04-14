#pragma once
#include <cassert>
#include <cmath>
#include <iostream>

void func(long long& n, unsigned long long& d);

class Rational
{
private:
    long long n;
    unsigned long long d;
    long long GetN() {
        return n;
    };
    unsigned long long GetD() {
        return d;
    }
public:
    Rational() : n(1), d(1)
    {};
    Rational(long n) : n(n), d(1)
    {};
    Rational(long long n, unsigned long long d) {
        assert(d != 0);
        func(n, d);
        this->n = n;
        this->d = d;
    }
    Rational(const Rational& number) : n(number.n), d(number.d)
    {};

    Rational& reverse();

    Rational& operator-();

    Rational& operator++();
    Rational& operator--();
    Rational& operator++(int);
    Rational& operator--(int);

    Rational& operator+=(const Rational& number);
    Rational& operator+(const Rational& number);
    Rational& operator-=(const Rational& number);
    Rational& operator-(const Rational& number);
    Rational& operator*=(const Rational& number);
    Rational& operator*(const Rational& number);
    Rational& operator/=(const Rational& number);
    Rational& operator/(const Rational& number);

    bool operator==(const Rational& number);
    bool operator!=(const Rational& number);
    bool operator > (const Rational& number);
    bool operator >= (const Rational& number);
    bool operator < (const Rational& number);
    bool operator <= (const Rational& number);

    friend std::ostream& operator<<(std::ostream& os, Rational& num) {
        os << num.GetN();
        if (num.GetD() != 1)
            os << '/' << num.GetD();
        return os;
    };
    friend std::istream& operator>>(std::istream& is, Rational& num) {
        long long a; long long b;
        std::cout << "n: ";
        is >> a;
        std::cout << "d: ";
        is >> b;
        assert(b > 0);
        num = Rational(a, b);
        return is;
    };
};