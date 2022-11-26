#include "utils.hpp"
#include "Dict.hpp"

class Engine
{
public:
    // Constructor takes a pair of dictionaries
    Engine(const Dict& answers, const Dict& guesses);

    // Score a guess passed as arrays
    void score_array(Color* score_colors, const char* guess, const char* answer) const;

    // Score a guess with integer arguments
    int16_t eval_score(int guess_i, int answer_j) const;

private:
    // Dictionary of legal answers to the puzzle
    const Dict& legal_answers;

    // Dictionary of legal guesses in the game; superset of legal_answers
    const Dict& legal_guesses;

    // The guesses made so far in this game state; vector of integer 
    vector<int16_t> guesses_made;

    // The scores received on these guesses
    vector<int16_t> scores_received;

    // Which of the legal answers are feasible?
    vector<bool> is_feasible;

    // Temporary storage for the scores array of the current guess
    mutable Color score_colors[sz];

};
