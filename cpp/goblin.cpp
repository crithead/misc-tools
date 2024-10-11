/// @ingroup cppexp
/// @{
/// Example of exporting a global instance of an object.
#include "goblin.hpp"

Goblin::Goblin(const std::string& name, int rank)
    : m_name(name), m_rank(rank)
{
}

const std::string& Goblin::Name() const 
{
    return m_name;
}

int Goblin::Rank() const 
{
    return m_rank;
}

/// @}

