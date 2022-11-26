#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <fmt/format.h>

#include "utils.hpp"

using std::string, std::ifstream, fmt::print;

// Dictionary of words allowed for either guesses or answers in Wordle
class Dict
{
public:
    // Construct a Dict from the name of a file containing the word list
    Dict(const string fname);

    // Return the ith word in the dictionary as a const char*
    // Note: This is NOT null terminated for performance reasons!
    const char* operator[] (int i) const;

    // Number of words in this dictionary
    inline int size() const
        {return words.size();}

    // Find a word in the dictionary
    int find(string word) const;

private:
    // Store all the words in the dictionary as one gigantic string for performance
    string words_cat;

    // Vector of standard strings for convenient input / output
    vector<string> words;
};
