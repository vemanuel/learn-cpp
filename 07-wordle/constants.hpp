#pragma once

#include <cstdint>

// Size of words in Wordle
constexpr int sz {5};

// Number of rounds in wordle
constexpr int rounds {6};

// Number of scores
constexpr std::uint8_t n_score {3*3*3*3*3};

// Perfect score
constexpr std::uint8_t perfect_score {n_score-1};
