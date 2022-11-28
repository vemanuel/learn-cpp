#pragma once

#include <vector>
#include "constants.hpp"
#include "enums.hpp"

using std::vector;

// Convert an array of feedback on each letter in a guess to a single integer for performance
uint8_t colors2score(const Color* colors);

// Convert a score to a vector of feedback colors
vector<Color> score2colors(uint8_t scores);
