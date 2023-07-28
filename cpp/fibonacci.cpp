// Print the fibonacci sequence
// 0, 1, 1, 2, 3, 5, 8, 13, ...
// Xn+2 = Xn+1 + Xn

#include <iostream>
#include <limits>

using namespace std;

static unsigned int fib_max(void);
static unsigned int fib_n(unsigned int);
static unsigned int term(unsigned int, unsigned int);

int main(int argc, char **argv)
{
    if (argc < 2) {
        fib_max();
    }
    else {
        unsigned int n = atoi(argv[1]);
        fib_n(n);
    }
    return 0;
}

unsigned int fib_n(unsigned int n)
{
    unsigned int a0 = 0;
    unsigned int a1 = 1;
    unsigned int a2 = -1;
    cout << a0 << '\n';
    cout << a1 << '\n';

    if (n > 48)
        n = 48; // max number of terms that'll fit in a u32
    for (int i = 0; i < static_cast<int>(n) - 2; i++) {
        a2 = term(a1, a0);
        cout << a2 << '\n';
        a0 = a1;
        a1 = a2;
    }
    return a2;
}

unsigned int fib_max(void)
{
    unsigned int a0 = 0;
    unsigned int a1 = 1;
    unsigned int a2 = 0;
    cout << a0 << '\n';
    cout << a1 << '\n';
    while (a2 < std::numeric_limits<unsigned int>::max() / 2) {
        a2 = term(a1, a0);
        cout << a2 << '\n';
        a0 = a1;
        a1 = a2;
    }
    return a2;
}

unsigned int term(unsigned int x0, unsigned int x1)
{
    unsigned int x2 = x1 + x0;
    return x2;
}
