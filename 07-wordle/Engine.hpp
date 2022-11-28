#pragma once

#include <iostream>
#include "constants.hpp"
#include "enums.hpp"
#include "utils.hpp"
#include "Dict.hpp"

using std::cin, std::uint8_t, std::uint16_t;

class Engine
{
public:
    // Constructor takes a pair of dictionaries
    Engine(const Dict& answers, const Dict& guesses);

    // Score a guess passed as arrays
    void calc_score(Color* score_colors, const char* guess, const char* answer) const;

    // Score a guess with string arguments
    uint8_t calc_score(const string& guess, const string& answer) const;

    // Score a guess with integer arguments; i is guess index, j is answer index
    uint8_t calc_score(int i, int j) const;

    // Look up a score on the score_tbl array
    inline uint8_t score(int i, int j) const
        {return score_tbl[n_ans*i + j];}

    // Look up an occupancy on the occupancy_tbl array
    inline uint16_t occupancy(int i, int k) const
        {return occupancy_tbl[n_score*i + k];}

    // Get a guess from the console, returning its row number
    uint16_t get_guess() const;

    // Get feedback on a guess from the console, converting it to an integer score
    uint8_t get_score() const;

    // Get the index of a guess
    inline uint16_t guess2i(const string& guess) const
        {return legal_guesses.find(guess);}

    // Get the index of an answer
    inline uint16_t answer2j(const string& answer) const
        {return legal_answers.find(answer);}

    // Report a guess from its index
    inline string i2guess(int i) const
        {return string(legal_guesses[i], sz);}

    // Report the best guess
    inline string guess_best() const
        {return i2guess(i_best);}

    // Report the best cost
    inline double cost_best() const
        {return cost_tbl[i_best];}

    // Tell the engine a guess was made and the score it received
    void make_guess(uint16_t i, uint8_t score_received);

    // Report the number of feasible guesses left
    inline int get_n_feasible() const
        {return static_cast<int>(n_feasible);}

    // Report the number of rounds played
    inline int rounds_played() const
        {return static_cast<int>(guesses_made.size());}

    // Build the score table
    void build_score_tbl();

    // Update the occupancy table
    void update_occupancy_tbl();

    // Update the cost vector
    void update_cost();

    // Play one round of the game interactively with an external source (e.g. NY Times)
    uint8_t play_one_round_ext();

    // Play one game interactively with an external source
    void play_one_game_ext();

private:
    // Dictionary of legal answers to the puzzle
    const Dict& legal_answers;

    // Dictionary of legal guesses in the game; superset of legal_answers
    const Dict& legal_guesses;

    // The number of legal guesses
    const int m;

    // The number of legal answers
    const int n_ans;

    // Temporary storage for the scores array of the current guess
    mutable Color score_colors[sz];

    // The guesses made so far in this game state; vector of integer 
    vector<uint16_t> guesses_made;

    // The scores received on these guesses
    vector<uint8_t> scores_received;

    // Which of the legal answers are feasible?
    vector<bool> is_feasible;

    // How many feasible words are left?
    int n_feasible;

    // Table to store an m x n_ans matrix of scores for each guess
    vector<uint8_t> score_tbl;

    // Table to store an m x n_score matrix of occupancy counts for each guess
    vector<uint16_t> occupancy_tbl;

    // Vector with the expected cost of each guess
    vector<double> cost_tbl;

    // Index of the best guess
    uint16_t i_best;

};
