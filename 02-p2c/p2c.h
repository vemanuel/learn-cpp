// Libraries
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

// Classes used
using std::cout, std::cin;
using std::string, std::stoi;
using std::vector;
using std::map;
using char_iter = std::istreambuf_iterator<char>;
using std::getline;
using boost::format, boost::split, boost::algorithm::trim_right;

// Function declarations
vector<string> read_pages();
// map<int, string> read_choices();
map<int, vector<string>> read_choices();
int get_next_page(int n);
int get_choice(int n);
void print_page(int n);
void test_read_page();
void test_read_pages();
int main();
