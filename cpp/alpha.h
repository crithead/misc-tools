#ifndef ALPHA_H
#define ALPHA_H

#include <string>

class A
{
public:
    A();
    ~A();
    std::string get_text(void) const;
    void set_text(const std::string &);
private:
    std::string m_text;
};

class B
{
public:
    B();
    ~B();
    int get_number(void) const;
    void set_number(int);
private:
    int m_number;
};

class C : public A, public B
{
public:
    C();
    ~C();
};

#endif //ALPHA_H

