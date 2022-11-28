#pragma once

#include <cstdint>

// Enumeration to hold feedback about one letter in a guess
enum class Color : std::uint8_t
{
    // A white tile means a letter has not been guessed yet
    white = 255,
    // A gray tile means a letter is not in the answer (wrong letter)
    gray = 0,
    // A yellow tile means the letter is in the answer, but in the wrong position (right letter, wrong position)
    yellow = 1,
    // A green tile means the letter in the guess matches the answer (right letter, right position)
    green = 2
};
