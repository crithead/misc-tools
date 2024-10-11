#ifndef CPP_COMPLEX_H
#define CPP_COMPLEX_H

#include <iostream>
#include <string>

class Complex
{
public:
    Complex();
    Complex(double, double);
    Complex(const Complex&);
    ~Complex();

    double Re() const;
    double Im() const;
    void SetReal(double);
    void SetImaginary(double);

    Complex& operator=(const Complex&);

    Complex operator+(const Complex&);
    Complex operator-(const Complex&);
    Complex operator*(const Complex&);
    Complex& operator+=(const Complex&);
    Complex& operator-=(const Complex&);
    Complex& operator*=(const Complex&);

    std::string Str() const;

private:
    double re;
    double im;
};

std::ostream& operator<<(std::ostream&, const Complex&);

#endif // CPP_COMPLEX_H
