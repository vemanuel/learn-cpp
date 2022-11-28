#include "Dict.hpp"

Dict::Dict(const string fname)
{
    // Open the input file
    ifstream file(fname, std::ifstream::in);

    // Count number of words from the number of characters in the file
    file.seekg(0, std::ios::end);
    int word_count = file.tellg() / (sz+1);
    file.seekg(0, std::ios::beg);
    #ifdef DEBUG
    print("fname = {:s}. word_count = {:d}.\n", fname, word_count);
    #endif

    // Resize the words vector
    words.resize(word_count);

    // Read the input file into the word list (vector)
    for (int i = 0; i < word_count; ++i)
    {
        // Read row i of the input file
        std::getline(file, words[i]);
    }

    // Size the words_cat string big enough to hold required number of characters
    words_cat.reserve(word_count * sz);

    // Copy the words into the big string words_cat
    for (int i = 0; i < word_count; ++i)
        {words_cat.append(words[i], 0, sz);}
}

const char* Dict::operator[] (int i) const
{
    return words_cat.data() + sz*i;
}

int Dict::find(string word) const
{
    // Get the lower bound
    const auto lb = std::lower_bound(words.begin(), words.end(), word);
    int i = (lb - words.begin());

    // If the word wasn't in the dictionary, set i to -1
    if (words[i] != word)
        {i = -1;}

    return i;
}