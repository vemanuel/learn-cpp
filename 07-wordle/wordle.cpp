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

    // Find an example word that is valid
    string word = "salet";
    int i = guesses.find(word);
    print("Index of word {:s} = {:d}.\n", word, i);

    // Find an example word that is missing
    word = "blarg";
    i = guesses.find(word);
    print("Index of word {:s} = {:d}.\n", word, i);

    // Build a Wordle engine
    Engine engine(answers, guesses);

}
