// E

#include <iostream>
#include <string>

#include "complex.h"

//using namespace std;

Complex::Complex() : re(0.0), im(0.0) {}
Complex::Complex(double r, double i) : re(r), im(i) {}

Complex::Complex(const Complex& other)
{
    this->re = other.re;
    this->im = other.im;
}

Complex::~Complex()
{
    // nothing here
}

double Complex::Re() const
{
    return this->re;
}

double Complex::Im() const
{
    return this->im;
}

void Complex::SetReal(double r)
{
    this->re = r;
}

void Complex::SetImaginary(double i)
{
    this->im = i;
}

// Assignment
Complex& Complex::operator=(const Complex& other)
{
    if (this == &other)
        return *this;

    this->re = other.re;
    this->im = other.im;

    return *this;
}

Complex Complex::operator+(const Complex& other)
{
    Complex value;
    value.re = this->re + other.re;
    value.im = this->im + other.im;
    return value;
}

Complex Complex::operator-(const Complex& other)
{
    Complex value;
    value.re = this->re - other.re;
    value.im = this->im - other.im;
    return value;
}

Complex Complex::operator*(const Complex& other)
{
    Complex value;
    value.re = (this->re * other.re) - (this->im * other.im);
    value.im = (this->re * other.im) + (this->im * other.re);
    return value;
}

Complex& Complex::operator+=(const Complex& other)
{
    this->re += other.re;
    this->im += other.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
    this->re -= other.re;
    this->im -= other.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& other)
{
    this->re = (this->re * other.re) - (this->im * other.im);
    this->im = (this->re * other.im) + (this->im * other.re);
    return *this;
}

std::string Complex::Str() const
{
    return std::string("A + Bi");
}

std::ostream& operator<<(std::ostream& os, const Complex& z)
{
    if (z.Im() == 0.0)
        os << z.Re();
    else if (z.Re() == 0.0)
        os << z.Im() << 'i';
    else
        os << z.Re() << '+' << z.Im() << 'i';
    return os;
}

#ifdef TEST

#include <cassert>

int main(int argc, char **argv)
{
    Complex a;
    assert(a.Re() == 0.0);
    assert(a.Im() == 0.0);
    std::cout << "a = " << a << std::endl;

    Complex b(4.0, 5.0);
    assert(b.Re() == 4.0);
    assert(b.Im() == 5.0);
    std::cout << "b = " << b << std::endl;

    Complex c = b;
    assert(c.Re() == b.Re());
    assert(c.Im() == b.Im());
    std::cout << "c = b: c = " << c << std::endl;

    Complex d = b + c;
    assert(d.Re() == 8.0);
    assert(d.Im() == 10.0);
    std::cout << "d = b + c: d = " << d << std::endl;

    Complex e = d - c;
    assert(e.Re() == 4.0);
    assert(e.Im() == 5.0);
    std::cout << "e = d - c: e = " << e << std::endl;

    Complex f = d * e;
    assert(f.Re() == -18.0);
    assert(f.Im() == 80.0);
    std::cout << "f = d * e: f = " << f << std::endl;

    Complex g = Complex(3.0, 2.0) * Complex(3.0,-2.0);
    assert(g.Re() == 13.0);
    assert(g.Im() == 0.0);
    std::cout << "g = 3+2i * 3-2i: g = " << g << std::endl;

    g += Complex(-1.0, -1.0);
    assert(g.Re() == 12.0);
    assert(g.Im() == -1.0);
    std::cout << "g += -1-1i: g = " << g << std::endl;

    g -= Complex(6.0, -7.0);
    assert(g.Re() == 6.0);
    assert(g.Im() == 6.0);
    std::cout << "g -= 6-7i: g = " << g << std::endl;

    g *= Complex(3.0, 2.0);
    assert(g.Re() == 6.0);
    assert(g.Im() == 30.0);
    std::cout << "g *= 2+2i: g = " << g << std::endl;

    g *= Complex();
    assert(g.Re() == 0.0);
    assert(g.Im() == 0.0);
    std::cout << "g *= 0: g = " << g << std::endl;
}

#endif // TEST
