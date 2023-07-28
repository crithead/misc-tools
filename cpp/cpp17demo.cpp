// Demonstrate C++17 Features

#include <iostream>
#include <string_view>


static void demo_clamp()
{
    std::cout << "---" << __func__ << std::endl;

}

static void demo_if_else_initializer()
{
    std::cout << "---" << __func__ << std::endl;
}

/**
 * The class template basic_string_view describes an object that can refer to
 * a constant contiguous sequence of CharT with the first element of the
 * sequence at position zero.
 */
static void demo_string_view(void)
{
    std::cout << "---" << __func__ << std::endl;

    std::string s0 = "Cyan Magenta Yellow Black";
    std::string s1{s0};
    std::string_view s2{s1.substr(s1.find('M'), 7)};
    std::string_view s3(s1.substr(s1.find('Y'), 6));

    std::cout << s1 << '\n'
              << s2 << '\n'
              << s3 << '\n'
              << std::endl;
}

int main(int argc, char **argv)
{
    demo_string_view();
    demo_clamp();
    demo_if_else_initializer();
}
