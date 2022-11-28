#include <fmt/format.h>
#include "utils.hpp"
// #include "Dict.hpp"
#include "Engine.hpp"

using std::cout;
using fmt::print;

// *********************************************************************************************************************
bool test_dict(const Dict& guesses, const Dict& answers)
{
    // Is this test passing?
    bool is_ok = true;

    // Report dictionary sizes
    print("Size of guesses dictionary is {:d} words.\n", guesses.size());
    print("Size of answers dictionary is {:d} words.\n", answers.size());

    // Find an example word that is a valid guess
    string guess = "salet";
    int i = guesses.find(guess);

    // The correct index of salet is 9504
    is_ok = is_ok && (i==9504);

    // Find an example word that is a valid answer
    string answer = "feast";
    int j = answers.find(answer);
    // The correct index of feast is 709
    is_ok = is_ok && (j==709);

    // Find an example word that is missing
    string bogus_word = "blarg";
    int k = guesses.find(bogus_word);
    // The correct index of blarg is -1
    is_ok = is_ok && (k==-1);

    // Report detailed results
    #ifdef DEBUG
    print("Index of a valid guess: {:s} = {:d}.\n", guess, i);
    print("Index of a valid guess: {:s} = {:d}.\n", answer, j);
    print("Index of word {:s} = {:d}.\n", bogus_word, k);
    #endif

    return is_ok;
}

// *********************************************************************************************************************
bool test_scoring(const Engine& engine)
{
    // Is this test passing?
    bool is_ok = true;

    // Some example words
    string guess = "salet";
    string answer = "feast";
    string bogus_word = "blarg";

    // Test scoring with arrays
    const char guess_c[sz+1]  = "salet";
    const char answer_c[sz+1] = "feast";
    Color score_colors[sz];
    engine.calc_score(score_colors, guess_c, answer_c);

    // Look up index positions of the two words
    int i = engine.guess2i(guess);
    int j = engine.answer2j(answer);

    // Test integer score function
    int16_t score = engine.calc_score(i, j);
    // The expected score array is 11012 
    int16_t score_correct = 81*1 + 27*1 + 9*0 + 3*1 + 1*2;
    is_ok = is_ok && (score == score_correct);

    // Recover score array
    vector<Color> score_colors_rec = score2colors(score);
    // Check that the recovered array matches the original one
    for (int i=0; i< sz; ++i)
        {is_ok = is_ok && (score_colors[i] == score_colors_rec[i]);}

    // Test that a perfect score is 242
    int perfect_score = engine.calc_score(answer, answer);
    is_ok = is_ok && (perfect_score == 242);

    // Report detailed results
    #ifdef DEBUG
    print("Integer score = {:d}.\n", score);
    print("correct score = {:d}.\n", score_correct);
    // The array results
    for (int i = 0; i < sz; ++i)
    {
        print("{:d}", static_cast<int>(score_colors_rec[i]));
    }
    print("\n");
    // The perfect score
    print("guess={:s}, answer={:s}, score={:d}.\n", answer, answer, perfect_score);
    #endif

    return is_ok;
}
// *********************************************************************************************************************
void test_io(const Engine& engine)
{
    // Prompt user for a guess
    int i_guess = engine.get_guess();
    print("Index of guess in dictionary is i_guess={:d}.\n", i_guess);

    // Prompt user for feedback
    int score_received = engine.get_score();
    print("Score received = {:d}\n", score_received);
}    

// *********************************************************************************************************************
bool test_all(const Dict& guesses, const Dict& answers, const Engine& engine)
{
    // Test results
    bool is_ok, all_is_ok = true;
    string test_result;

    // Test the dictionaries
    is_ok = test_dict(guesses, answers);
    test_result = is_ok ? "PASS" : "FAIL";
    print("****** dict  : {:s} ******\n", test_result);
    all_is_ok = all_is_ok && is_ok;

    // Test scoring
    is_ok = test_scoring(engine);
    test_result = is_ok ? "PASS" : "FAIL";
    print("****** scoring: {:s} ******\n", test_result);
    all_is_ok = all_is_ok && is_ok;

    // Test IO
    // test_io(engine);

    // Return overall test result
    return all_is_ok;
}

// *********************************************************************************************************************
int main()
{   
    // Build the dictionary of possible answers
    Dict answers("answers.txt");

    // Build the dictionary of legal guesses
    Dict guesses("guesses.txt");

    // Build a Wordle engine
    Engine engine(answers, guesses);

    // Play one game
    engine.play_one_game_ext();

}
