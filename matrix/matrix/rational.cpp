#include <iostream>
#include "rational.h"

void func(long long& n, unsigned long long& d) {
    if (n == 0) d = 1;
    else {
        long long copy_n = abs(n), copy_d = d;
        while (copy_n != copy_d) {
            if (copy_n > copy_d) {
                copy_n = copy_n - copy_d;
            }
            else {
                copy_d = copy_d - copy_n;
            }
        }
        n /= copy_d;
        d /= copy_d;
    }
};

Rational& Rational :: reverse() {
    assert(n != 0);
    int k = abs(n) / n;
    long long temp = n;
    n = d * k;
    d = abs(temp);
    return *this;
}

Rational& Rational :: operator-() {
    n *= -1;
    return *this;
}

Rational& Rational :: operator++() {
    n += d;
    return *this;
}

Rational& Rational :: operator--() {
    n -= d;
    return *this;
}

Rational& Rational :: operator++(int) {
    Rational copy(*this);
    n += d;
    return copy;
}

Rational& Rational :: operator--(int) {
    Rational copy(*this);
    n -= d;
    return copy;
}

Rational&Rational ::  operator+=(const Rational& number) {
    n = n * number.d + number.n * d;
    d *= number.d;
    func(n, d);
    return *this;
};

Rational& Rational ::operator+(const Rational& number) {
    Rational copy(*this);
    return copy += number;
};

Rational& Rational:: operator-=(const Rational& number) {
    n = n * number.d - number.n * d;
    d *= number.d;
    func(n, d);
    return *this;
};

Rational& Rational :: operator-(const Rational& number) {
    Rational copy(*this);
    return copy -= number;
};

Rational& Rational:: operator*=(const Rational& number) {
    n *= number.n;
    d *= number.d;
    func(n, d);
    return *this;
};

Rational& Rational :: operator*(const Rational& number) {
    Rational copy(*this);
    return copy *= number;
};

Rational& Rational :: operator/=(const Rational& number) {
    Rational copy(number);
    copy.reverse();
    n *= copy.n;
    d *= copy.d;
    func(n, d);
    return *this;
};

Rational& Rational :: operator/(const Rational& number) {
    Rational copy(*this);
    return copy /= number;
};

bool Rational :: operator==(const Rational& number) {
    return (n == number.n) && (d == number.d);
};

bool Rational :: operator!=(const Rational& number) {
    return !((n == number.n) && (d == number.d));
};

bool Rational :: operator > (const Rational& number) {
    Rational copy(*this);
    copy -= number;
    return (copy.n > 0);
}

bool Rational :: operator >= (const Rational& number) {
    Rational copy(*this);
    return (copy > number) || (copy == number);
}

bool Rational :: operator < (const Rational& number) {
    Rational copy(*this);
    return !(copy >= number);
}

bool Rational :: operator <= (const Rational& number) {
    Rational copy(*this);
    return !(copy > number);
}