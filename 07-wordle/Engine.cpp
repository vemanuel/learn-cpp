#include "Engine.hpp"

// *********************************************************************************************************************
Engine::Engine(const Dict& answers, const Dict& guesses) :
    legal_answers(answers),
    legal_guesses(guesses),
    m(guesses.size()),
    n_ans(answers.size())
{
    // Reserve space for guesses_made and scores_received
    guesses_made.reserve(rounds);
    scores_received.reserve(rounds);

    // Initialize score_tbl and populate it (doesn't change)
    score_tbl.resize(m * n_ans, 0);
    build_score_tbl();

    // Initialize occupancy_tbl
    occupancy_tbl.resize(m * n_score, 0);

    // Resize is_feasible and initialize to true
    is_feasible.resize(n_ans, true);
    // Initialize n_feasible
    n_feasible = n_ans;

    // Initialize cost_tbl
    cost_tbl.resize(m, 0.0);
}

// *********************************************************************************************************************
void Engine::calc_score(Color* score_colors, const char* guess, const char* answer) const
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

// *********************************************************************************************************************
uint8_t Engine::calc_score(const string& guess, const string& answer) const
{
    // Delegate to array version of calc_score
    calc_score(score_colors, guess.c_str(), answer.c_str());

    // Convert the array to an integer
    return colors2score(score_colors);
}

// *********************************************************************************************************************
uint8_t Engine::calc_score(int guess_i, int answer_j) const
{
    // Delegate to array version of calc_score
    calc_score(score_colors, legal_guesses[guess_i], legal_answers[answer_j]);

    // Convert the array to an integer
    return colors2score(score_colors);
}

// *********************************************************************************************************************
uint16_t Engine::get_guess() const
{
    // The integer entry of the guess
    int i = -1;
    // string for user input
    // char word_[sz+1];
    string word;

    // Loop until we get a valid word
    while (i < 0)
    {
        // Get the guess as a string
        print("Enter guess. Enter 'h' to accept the hint.\n");
        cin >> word;

        // Did the user accept the hint?
        bool accept_hint = (word.length() == 1);

        // Look up the word the user provided, or use the best guess according to the engine
        i = accept_hint ? i_best : legal_guesses.find(word);

        // Prompt user if this word wasn't found
        if (i < 0)
            {print("Sorry, word {:s} is not in dictionary of legal guesses.  Please try again.\n", word);}
    }

    // Return the index of the guesses word as an uint16_t
    return static_cast<uint16_t>(i);
}

// *********************************************************************************************************************
uint8_t Engine::get_score() const
{
    // The integer entry of the guess
    int score;
    // Char array for user input
    string feedback;

    // Loop until we get a valid score
    while (true)
    {
        // Get the feedback as a string
        print("Enter feedback as ?????, with gray=0, yellow=1, green=2.\n");
        cin >> feedback;

        // Validate feedback string length
        if (feedback.length() != sz)
        {
            print("feedback must have length {:d}. {:s} has length {:d}.\n", sz, feedback, feedback.length());
            continue;
        }

        // Validate feedback characters and accumluate integer score
        score = 0;
        int place_value = 1;
        for (int k=sz-1; k>=0; --k)
        {
            // The k-th character of the feedback string
            char c = feedback[k];
            // Convert the character to an integer in {0, 1, 2}
            int x = c - '0';
            if ((x < 0) || (x > 2))
            {
                print("feedback must contain only 0,1,2.  character {:d} of feedback is {:c}.\n", k, c);
                score = -1;
                break;
            }
            // Accumulate score
            else
            {
                score += place_value * x;
                place_value *= 3;
            }
        }

        // Check if score is negative because we broke early
        if (score < 0)
            {continue;}
        // If we get here, we have a valid score
        else
            {break;}
    }

    // Return the index of the guesses word as an uint16_t
    return static_cast<uint16_t>(score);
}

// *********************************************************************************************************************
void Engine::build_score_tbl()
// Initialize the score table; only need to do this once
{
    #ifdef DEBUG
    print("Engine() - populating score_tbl...\n");
    #endif

    // Iterate over legal guesses
    for (int i = 0, k=0; i < m; ++i)
    {
        // Iterate over legal answers
        for (int j = 0; j < n_ans; ++j)
        {
            score_tbl[k++] = calc_score(i,j);
        }
    }

    #ifdef DEBUG
    print("Engine() - populating occupancy_tbl...\n");
    #endif
}

// *********************************************************************************************************************
void Engine::make_guess(uint16_t i, uint8_t score_received)
{
    // Save the guess in guesses_made
    guesses_made.push_back(i);
    // Save the score in scores received
    scores_received.push_back(score_received);

    // Update is_feasible so only the matching answers are good; also count n_feasible
    n_feasible = 0;
    for (int j = 0; j < n_ans; ++j)
    {
        is_feasible[j] = is_feasible[j] && (score(i,j) == score_received);
        n_feasible += static_cast<int>(is_feasible[j]);
    }
}

// *********************************************************************************************************************
void Engine::update_occupancy_tbl()
// Populate the occupancy table
{
    // Iterate over legal guesses
    for (int i = 0; i < m; ++i)
    {
        // The base row number
        int r_base = n_score * i;

        // Initialize entries to zero in row i
        for (int k = 0; k < n_score; ++k)
            {occupancy_tbl[r_base + k]=0;}

        // Iterate over legal answers
        for (int j = 0; j < n_ans; ++j)
        {
            // Only process this answer if it's feasible
            if ( is_feasible[j] )
            {
                // The row number in the occupancy table
                int r = r_base + score(i,j);
                // Increment the counter
                ++occupancy_tbl[r];
            }
        }
    }
}

// *********************************************************************************************************************
void Engine::update_cost()
// Populate the cost function
{
    // Initialize best_guess and best_cost
    i_best = 0;
    double cost_best = n_ans;

    // Iterate over legal guesses
    for (int i = 0; i < m; ++i)
    {
        // Initialize the total cost of this guess to zero
        double total_cost = 0.0;
        // Sum the cost of all states other than the perfect score; that has zero cost
        for (int k=0; k < n_score-1; ++k)
        {
            // The occupancy of this state (number of words consistent with this score)
            int16_t occ = occupancy(i,k);
            // Only sum over occupied states
            if (occ)
                {total_cost += log1p(occ) * occ;}
        }

        // Write the cost for this guess; divide by number of feasible words
        cost_tbl[i] = total_cost / n_feasible;

        // Is this the new best guess?
        if (cost_tbl[i] < cost_best)
        {
            i_best = i;
            cost_best = cost_tbl[i];
        }
    }
}

// *********************************************************************************************************************
uint8_t Engine::play_one_round_ext()
// Play one round of the game interactively with an external source
{
    // Build occupancy table
    update_occupancy_tbl();

    // Update cost function
    update_cost();

    // Report best guess according to the engine
    print("Best guess: {:s}\n", guess_best());
    print("Expected cost = {:6.4f}.\n", cost_best());

    // The index of the word played by the user this round
    uint16_t i = 0;
    // User response - whether to keep a word entered
    string user_response;
    // Give user multiple chances to try out guesses
    while (true)
    {
        // Prompt user for a guess
        i = get_guess();
        // Report expected cost of this guess and ask if user wants to play it.
        if (i != i_best)
        {
            print("Expected cost of {:s} = {:6.4f}. Do you want to play it? (y, n).\n", i2guess(i), cost_tbl[i]);
            // Get user response
            cin >> user_response;
            bool use_word = user_response[0] == 'y';
            // Quit this loop when user is satisfied
            if (use_word)
                {break;}
        }
        // If we took the default guess just use it without prompting
        else
            {break;}
    }

    // Prompt user for feedback
    uint8_t score_received = get_score();

    // Make this guess
    make_guess(i, score_received);

    // Report number of feasible words if the game is continuing
    if (score_received != perfect_score)
        {print("Feasible words left = {:d}.\n", get_n_feasible());}

    return score_received;
}

// *********************************************************************************************************************
void Engine::play_one_game_ext()
// Play one game interactively with an external source
{
    for (int r = 0; r <= rounds; ++r)
    {
        // Play one round
        uint8_t score = play_one_round_ext();
        // Stop playing if we won early
        if (score == perfect_score)
        {
            print("You won in {:d} rounds.\n", rounds_played());
            break;
        }
    }
}
