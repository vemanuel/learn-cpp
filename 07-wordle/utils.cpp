#include "utils.hpp"

// Convert an array of feedback on each letter in a guess to a single integer for performance
int16_t colors2score(const Color* colors)
{
    int16_t score = static_cast<int32_t>(colors[0]);
    for (int i = 1; i < sz; ++i)
    {
        score *= 8;
        score += static_cast<int16_t>(colors[i]);
    }
    return score;
}

// Convert a score to a vector of feedback colors
vector<Color> score2colors(int16_t scores)
{
    vector<Color> colors(sz);
    for (int i = sz-1; i >= 0; --i)
    {
        int8_t this_score = scores % 8;
        colors[i] = static_cast<Color>(this_score);
        scores = (scores - this_score) / 8;       
    }
    return colors;
}
