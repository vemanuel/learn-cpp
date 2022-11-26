#include "Engine.hpp"

Engine::Engine(const Dict& answers, const Dict& guesses) :
    legal_answers(answers),
    legal_guesses(guesses)
{
    ;
}

void Engine::score_array(Color* score_colors, const char* guess, const char* answer) const
{
    // Initialize the score_colors to gray
    for (int i = 0; i < sz; ++i)
        {score_colors[i] = Color::gray;}

    // Keep track of which letters have been matched already
    vector<bool> is_matched(sz);

    // Determine any exact matches (green)
    for (int i = 0; i < sz; ++i)
    {
        if (guess[i] == answer[i])
        {
            score_colors[i] = Color::green;
            is_matched[i] = true;
        }
    }

    // Determine matches with the right letter in the wrong place
    for (int i = 0; i < sz; ++i)
    {
        for (int j=0; j < sz; ++j)
        {
            if ((guess[i] == answer[j]) && !is_matched[j])
            {
                score_colors[i] = Color::yellow;
                is_matched[j] = true;
            }
        }
    }

}

int16_t Engine::eval_score(int guess_i, int answer_j) const
{
    // Delegate to score_array
    score_array(score_colors, legal_guesses[guess_i], legal_answers[answer_j]);

    // Convert the array to an integer
    return colors2score(score_colors);
}
