/// std::find_if example

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

static void Example1(void);
static void Print(const std::vector<int>&, const char *);

int main(int, const char **)
{
    Example1();

    return 0;
}


static void Example1(void)
{
    std::vector<int> v { 3, 6, 2, 1, 4, 7, 5 };
    Print(v, "Before");

    int n = 4;
    std::cout << "Remove: n = " << n << std::endl;
    auto it = std::find_if(v.begin(), v.end(), [n] (int i) { return i == n; });
    v.erase(it);

    Print(v, "After ");
}

static void Print(const std::vector<int>& v, const char *text)
{
    std::cout << text << ": ";
    std::for_each(v.begin(), v.end(), [](int i) { std::cout << std::setw(4) << i; });
    std::cout << std::endl;
}

