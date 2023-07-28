// loopvars.cpp
// program to test scope of variables in a loop.
#include <iostream>

class A
{
public:
    A(int a_) : a(a_) {
        std::cout << " A(" << a << ")" << std::endl;
    }
    ~A() {
        std::cout << "~A(" << a << ")" << std::endl;
    }
    int getA() const {
        return a;
    }
    void setA(int a_) {
        a = a_;
    }
private:
    int a;
};

class Counter 
{
public:
    Counter(int start, int end) : 
            m_start(start), m_end(end), m_count(start)
    {
        std::cout << " Counter(" << m_count << "/" << m_end << ")" 
                << std::endl;
    }
    ~Counter() {
        std::cout << "~Counter(" << m_count << "/" << m_end << ")" 
                << std::endl;
    }
    int operator++() {
        return ++m_count;
    }
    bool done() const {
        return m_count >= m_end;
    }
    int count() const {
        return m_count;
    }
private:
    int m_start;
    int m_end;
    int m_count;
};


int main(int argc, char **argv)
{
    std::cout << "Before loop 1." << std::endl;
    for (int i = 0; i < 3; i++) {
        A a(i); // This instance of A is created at the beginning of
                // each iteration through the loop and destroyed at
                // the end of every loop.
        std::cout << "In loop 1 [i = "  << i << "]" << std::endl;
    }
    std::cout << "After loop 1.\n" << std::endl;

    std::cout << "Before loop 2." << std::endl;
    int j = 0;
    while (j < 3) {
        A a(j); // Same as the "for" loop.
        std::cout << "In loop 2 [i = "  << j << "]" << std::endl;
        j++;
    }
    std::cout << "After loop 2.\n" << std::endl;

    std::cout << "Before loop 3." << std::endl;
    // The Counter instance is created (one time) before the loop and
    // destroyed (one time) after the loop.
    for (Counter c(0, 3); !c.done(); ++c) {
        std::cout << "In loop 3 [i = "  << c.count() << "]" << std::endl;
    }
    std::cout << "After loop 3." << std::endl;
    // same as:
    // Counter c(0, 3);
    // while (!c.done()) {
    //     ...
    //     ++c;
    // }

    return 0;
}

/****************************************************************************
 **** Program output:

Before loop 1.
 A(0)
In loop 1 [i = 0]
~A(0)
 A(1)
In loop 1 [i = 1]
~A(1)
 A(2)
In loop 1 [i = 2]
~A(2)
After loop 1.

Before loop 2.
 A(0)
In loop 2 [i = 0]
~A(0)
 A(1)
In loop 2 [i = 1]
~A(1)
 A(2)
In loop 2 [i = 2]
~A(2)
After loop 2.

Before loop 3.
 Counter(0/3)
In loop 3 [i = 0]
In loop 3 [i = 1]
In loop 3 [i = 2]
~Counter(3/3)
After loop 3.

****************************************************************************/
