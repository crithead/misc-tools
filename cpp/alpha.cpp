/** @ingroup cppexp
 * @{
 */

#include "alpha.hpp"

A::A() : m_text("") {}

A::~A() {}

std::string A::get_text(void) const
{
    return m_text;
}

void A::set_text(const std::string &s)
{
    m_text = s;
}

B::B() : m_number(0) {}

B::~B() {}

int B::get_number(void) const
{
    return m_number;
}

void B::set_number(int n)
{
    m_number = n;
}

C::C() : A(), B() {}
C::~C() {}

/** @} */

