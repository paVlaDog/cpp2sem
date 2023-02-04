#include "complex.h"

#include <cmath>
#include <iostream>
#include <string>

double Complex::abs() const
{
    return std::hypot(m_im, m_re);
}

double Complex::real() const
{
    return m_re;
}

double Complex::imag() const
{
    return m_im;
}

std::string Complex::str() const
{
    std::ostringstream temp;
    temp << *this;
    return temp.str();
}

Complex & Complex::operator+=(const Complex & other)
{
    return (*this = *this + other);
}

Complex & Complex::operator-=(const Complex & other)
{
    return (*this = *this - other);
}

Complex & Complex::operator*=(const Complex & other)
{
    return (*this = *this * other);
}

Complex & Complex::operator/=(const Complex & other)
{
    return (*this = *this / other);
}

Complex Complex::operator-() const
{
    return Complex(-m_re, -m_im);
}

Complex Complex::operator~() const
{
    return Complex(m_re, -m_im);
}

Complex operator+(const Complex & c1, const Complex & c2)
{
    return Complex(c1.m_re + c2.m_re, c1.m_im + c2.m_im);
}

Complex operator-(const Complex & c1, const Complex & c2)
{
    return Complex(c1.m_re - c2.m_re, c1.m_im - c2.m_im);
}

Complex operator*(const Complex & c1, const Complex & c2)
{
    return Complex(c1.m_re * c2.m_re - c1.m_im * c2.m_im, c1.m_re * c2.m_im + c1.m_im * c2.m_re);
}

Complex operator/(const Complex & c1, const Complex & c2)
{
    if (c2.m_re == 0 && c2.m_im == 0) {
        return Complex(c1.m_re / 0.0, c1.m_im / 0.0);
    }
    double r = c2.m_re * c2.m_re + c2.m_im * c2.m_im;
    return (c1 * (~c2)) * (1 / r);
}

std::ostream & operator<<(std::ostream & out, const Complex & c)
{
    out << "(" << c.m_re << "," << c.m_im << ")";
    return out;
}
