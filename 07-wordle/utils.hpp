#pragma once

#include <cstdint>
#include <vector>

using std::vector;

// Size of words in Wordle
constexpr int sz {5};

// Enumeration to hold feedback about one letter in a guess
enum class Color : std::int8_t
{
    // A white tile means a letter has not been guessed yet
    white = 0,
    // A gray tile means a letter is not in the answer (wrong letter)
    gray = 1,
    // A yellow tile means the letter is in the answer, but in the wrong position (right letter, wrong position)
    yellow = 2,
    // A green tile means the letter in the guess matches the answer (right letter, right position)
    green = 4
};

// Convert an array of feedback on each letter in a guess to a single integer for performance
int16_t colors2score(const Color* colors);

// Convert a score to a vector of feedback colors
vector<Color> score2colors(int16_t scores);
