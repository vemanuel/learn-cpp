#include "utils.hpp"

// Convert an array of feedback on each letter in a guess to a single integer for performance
uint8_t colors2score(const Color* colors)
{
    uint8_t score = static_cast<uint8_t>(colors[0]);
    for (int i = 1; i < sz; ++i)
    {
        score *= 3;
        score += static_cast<uint8_t>(colors[i]);
    }
    return score;
}

// Convert a score to a vector of feedback colors
vector<Color> score2colors(uint8_t scores)
{
    vector<Color> colors(sz);
    for (int i = sz-1; i >= 0; --i)
    {
        uint8_t this_score = scores % 3;
        colors[i] = static_cast<Color>(this_score);
        scores = (scores - this_score) / 3;       
    }
    return colors;
}
