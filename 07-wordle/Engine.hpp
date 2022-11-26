#include "utils.hpp"
#include "Dict.hpp"

class Engine
{
public:
    Engine(const Dict& answers, const Dict& guesses);

private:
    // Dictionary of legal answers to the puzzle
    const Dict& legal_answers;
    // Dictionary of legal guesses in the game; superset of legal_answers
    const Dict& legal_guesses;
    // The guesses made so far in this game state; vector of integer 

};
