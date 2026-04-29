/// Namer class implementation.

#include "namer.hpp"

const char Namer::ALPHABET[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

const size_t Namer::ALPHABET_SIZE = sizeof(Namer::ALPHABET) - 1;
const size_t Namer::DEFAULT_LENGTH = 16;

Namer::Namer(size_t len) :
    default_length(len),
    generator()
{
    if (default_length == 0) {
        default_length = DEFAULT_LENGTH;
    }
}

Namer::~Namer()
{
}

std::string Namer::GetName(size_t length)
{
    if (length == 0) {
        length = default_length;
    }

    std::string value;
    for (size_t i = 0; i < length; i++) {
        value += ALPHABET[RandInt(0, ALPHABET_SIZE - 1)];
    }

    return value;
}

int Namer::RandInt(int a, int b)
{
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}
