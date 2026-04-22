/// File and directory name generator.
#pragma once

#include <random>
#include <string>

/// @brief A source of random strings for file and directory names.
class Namer
{
public:
    /// @brief The set of characters to use in generated names.
    static const char ALPHABET[];
    /// @brief The size of the alphabet.
    static const size_t ALPHABET_SIZE;
    /// @brief The default length of generated names.
    static const size_t DEFAULT_LENGTH;

    /// @brief Construct a Namer object.
    /// @param default_length The default length of generated names.
    ///        If 0, use DEFAULT_LENGTH.
    Namer(size_t default_length = 0);

    /// @brief Destructor.
    ~Namer();

    /// @brief Get a random name.
    /// @param length The length of the name to generate.
    ///        If 0, use the default length specified in the constructor.
    std::string GetName(size_t length = 0);

private:
    int RandInt(int a, int b);

    size_t default_length;
    std::random_device generator;
};
