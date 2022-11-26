#include <fmt/format.h>

#include "utils.hpp"
#include "Dict.hpp"
#include "Engine.hpp"

using std::cout;
using fmt::print;

int main()
{   
    // Build the dictionary of possible answers
    Dict answers("answers.txt");
    print("Size of answers dictionary is {:d} words.\n", answers.size());

    // Build the dictionary of legal guesses
    Dict guesses("guesses.txt");
    print("Size of guesses dictionary is {:d} words.\n", guesses.size());

    // Find an example word that is a valid guess
    string guess = "salet";
    int i = guesses.find(guess);
    print("Index of a valid guess: {:s} = {:d}.\n", guess, i);

    // Find an example word that is a valid answer
    string answer = "feast";
    int j = answers.find(answer);
    print("Index of a valid guess: {:s} = {:d}.\n", answer, j);

    // Find an example word that is missing
    string bogus_word = "blarg";
    int k = guesses.find(bogus_word);
    print("Index of word {:s} = {:d}.\n", bogus_word, k);

    // Build a Wordle engine
    Engine engine(answers, guesses);

    // Test scoring
    char answer_c[sz+1] = "feast";
    char guess_c[sz+1]  = "salet";
    Color score_colors[sz];

    print("Scoring answer={:s}, guess={:s}.\n", answer, guess);
    engine.score_array(score_colors, guess_c, answer_c);
    for (int i = 0; i < sz; ++i)
    {
        print("{:d}", static_cast<int>(score_colors[i]));
    }
    print("\n");
    int16_t score = engine.eval_score(i, j);
    print("Integer score = {:d}.\n", score);

    // Recover score array
    vector<Color> score_colors_rec = score2colors(score);
    for (int i = 0; i < sz; ++i)
    {
        print("{:d}", static_cast<int16_t>(score_colors_rec[i]));
    }
    print("\n");

}
