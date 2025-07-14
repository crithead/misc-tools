/// @file A Library of useless math functions

#pragma once

/// @brief  A plus B
/// @param a An integer
/// @param b An integer
/// @return The sum of A and B.
extern int Plus(int a, int b) noexcept;

/// @brief  A minus B
/// @param a An integer
/// @param b An integer
/// @return The difference of A and B.
extern int Minus(int a, int b) noexcept;

/// @brief  A times B
/// @param a An integer
/// @param b An integer
/// @return The product of A and B.
extern int Times(int a, int b) noexcept;

/// @brief  A divided by B
/// @param a An integer
/// @param b An integer
/// @return The quotient of A and B.
/// @throws std::invalid_argument if B is zero.
extern int DividedBy(int a, int b);
