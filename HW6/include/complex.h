#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

struct Complex
{
private:
    double m_re = 0;
    double m_im = 0;

public:
    Complex(double re = 0, double im = 0)
        : m_re(re)
        , m_im(im)
    {
    }

    double abs() const;
    double real() const;
    double imag() const;
    std::string str() const;

    Complex & operator+=(const Complex & other);
    Complex & operator-=(const Complex & other);
    Complex & operator*=(const Complex & other);
    Complex & operator/=(const Complex & other);
    Complex operator-() const;
    Complex operator~() const;

    friend Complex operator+(const Complex & c1, const Complex & c2);
    friend Complex operator-(const Complex & c1, const Complex & c2);
    friend Complex operator*(const Complex & c1, const Complex & c2);
    friend Complex operator/(const Complex & c1, const Complex & c2);

    friend bool operator==(const Complex & c1, const Complex & c2) = default;
    friend std::ostream & operator<<(std::ostream &, const Complex &);
};
