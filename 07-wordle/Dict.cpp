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

    // Size the words vector
    // words.reserve(word_count);
    words.resize(word_count);

    print("word_count = {:d}.\n", word_count);

    // Read the input file into the word list (vector)
    for (int i = 0; i < word_count; ++i)
    {
        // Read row i of the input file
        std::getline(file, words[i]);
    }

    // DEBUG
    #ifdef DEBUG
    print("words[0] = {:s}. len = {:d}.\n", words[0], words[0].length());
    print("words[1] = {:s}. len = {:d}.\n", words[1], words[1].length());
    print("words[2] = {:s}. len = {:d}.\n", words[2], words[2].length());
    if (words.size() > 9504)
    {
        print("words[9504] = {:s}. len = {:d}.\n", words[9504], words[9504].length());
    }
    #endif

    // Size the words_cat string big enough to hold required number of characters
    words_cat.reserve(word_count * sz);

    // Copy the words into the big string words_cat
    for (int i = 0; i < word_count; ++i)
        {words_cat.append(words[i], 0, sz);}

    // DEBUG
    #ifdef DEBUG
    print("First 20 characters of wordscat:\n");
    for (int i=0; i < 20; ++i)
    {
        print("{:c}", words_cat[i]);
    }
    print("\n");
    #endif
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