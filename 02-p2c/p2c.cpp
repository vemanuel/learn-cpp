#include "p2c.h"

// ****************************************************************************
// The number of pages in the book
constexpr int page_count = 72;

// The pages where the story ends
const map<int, string> end_pages {
    {29, "End #5\n"},
    {35, "End #3\n"},
    {49, "End #6\n"},
    {59, "End #1\n"},
    {63, "End #2\n"},
    {67, "End #4\n"},
    {69, "End #7\n"},
    {71, "End #8\n"},
};

// The pages where Danny has a choice
const vector<int> choice_page_nums {9, 13, 19, 27, 31, 39, 45, 53,};

// The table of page jumps for Danny's choices
const map<int, vector<int>> jump_table {
    {9,  {20, 36}},
    {13, {28, 46}},
    {19, {32, 40}},
    {27, {30, 10}},
    {31, {70, 50}},
    {39, {72, 14}},
    {45, {54, 64}},
    {53, {68, 60}},
};

// Load pages into memory once
vector<string> pages = read_pages();

// Load choices into memory once
map<int, vector<string>> choices = read_choices();

// ****************************************************************************
// read a file into a string given the file name.
string read_file(string fname)
{
    std::ifstream fs(fname);
    string str((char_iter(fs)), char_iter());
    return str;
}

// ****************************************************************************
// Load all of the pages of text into a vector of strings called pages.
// Text does *not* include choices that Danny makes.
vector<string> read_pages()
{
    vector<string> pages(page_count);
    for (int n=1; n <= page_count; ++n)
    {
        string fname = str(format("pages/%03d.txt") % n);
        pages[n-1] = read_file(fname);
    }
    return pages;
}

// ****************************************************************************
map<int, vector<string>> read_choices()
{
    map<int, vector<string>> choices {};
    for (int n : choice_page_nums)
    {
        string fname = str(format("choices/%03d.txt") % n);
        string str = read_file(fname);
        trim_right(str);
        // Split str into lines separated by newlines
        vector<string> lines;
        split(lines, str, boost::is_any_of("\n"));
        choices[n] = lines;
    }
    return choices;
}

// ****************************************************************************
// Calculate the next page number given the current page number, n.
// Use a page number of 0 to signify that the story is over.
// Delegate a call to get_choice on pages where Danny needs to make a choice.
int get_next_page(int n)
{
    // Check if n is an ending page
    if (end_pages.count(n) > 0)
    {
        const string ending = end_pages.at(n);
        cout << ending;
        return 0;
    }
    // Check if n is one of Danny's choices
    else if (choices.count(n) > 0)
    {
        int m = get_choice(n);
        // cout << format("you chose %d\n") % m;
        const vector<int> nn = jump_table.at(n);
        return nn[m-1];
    }
    // If we get here, return the next page
    else
    {
        return n+1;
    }
}

// ****************************************************************************
int get_choice(int n)
{
    vector<string> msgs = choices[n];    
    string response;
    int choice_count = msgs.size()-1;
    // First line is always "What Should Danny Do?"
    cout << format("%s\n") % msgs[0];
    // Output the remaining choices with the number prepended
    for (int i=1; i<= choice_count; ++i)
    {
        cout << format("(%d) %s\n") % i % msgs[i];
    }
    // Get the user's response and convert to an integer
    getline(cin, response);
    int choice=0;
    try
    {
        choice = stoi(response);
    }
    catch (std::invalid_argument) {;}
    // Keep trying until user gives a valid response
    while (choice < 1 || choice > choice_count)
    {
        cout << format("Choice must be between 1 and %d.  Please try again.\n") % choice_count;
        choice = get_choice(n);
    }
    return choice;
}

// ****************************************************************************
// Print page n to screen
void print_page(int n)
{
    string page = pages[n-1];
    cout << page;
}

// ****************************************************************************
void test_read_page()
{
    cout << "Test: read and print page 2.\n";
    string page = read_file("pages/002.txt");
    cout << page;
}

// ****************************************************************************
void test_read_pages()
{
    cout << "Test: read_pages.\n";
    vector<string> pages = read_pages();
    for (string page : pages)
    {
        cout << page << "\n";
    }
}

// ****************************************************************************
int main()
{
    int n=1;
    do 
    {
        print_page(n);
        n = get_next_page(n);
    }
    while (n>0);
}