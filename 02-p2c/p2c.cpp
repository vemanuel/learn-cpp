#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <boost/format.hpp>

using std::cout;
using std::string;
using std::vector;
using char_iter = std::istreambuf_iterator<char>;
using boost::format;

// ****************************************************************************
// The number of pages in the book
constexpr int page_count = 72;

// ****************************************************************************
// read a file into a string given the file name.
string read_file(string fname)
{
    std::ifstream t(fname);
    string str((char_iter(t)), char_iter());
    return str;
}

// ****************************************************************************
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
    cout << "Welcome: Power to Choose.\n";
    test_read_pages();
}