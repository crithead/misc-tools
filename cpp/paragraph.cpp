/// Print a pre-formatted paragraph of text.

#include <iostream>

static const char *T1 = "\
Usage:\n\
    paragraph OPTIONS\n\
\n\
Options:\n\
    There are no options.\n\
";


static const char *T2 = R"(
Usage:
    paragraph OPTIONS

Options:
    There are still no options.
)";

static void print(const char *text)
{
    std::cout << text << '\n';
}

static void line(char c,  size_t n)
{
    for (size_t i = 0; i < n; i++) {
        std::cout << c;
    }
    std::cout << '\n';
}

auto main() -> int
{
    line('=', 80);
    print(T1);
    line('=', 80);
    print(T2);
    line('=', 80);

    return 0;
}

