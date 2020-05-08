#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

void greet();

void shake(vector<char> &grid, char die[][6]);

void print_grid(vector<char> grid);

int wordscore(int length);

int calculate_score(vector<int> scores);

vector<int> connected_pos(vector<int> temp_path); 

bool word_path_valid(vector<char> &grid, string &word);

bool word_unique(string word, vector<string> words);

bool word_in_dictionary(string word);

bool word_valid(vector<char> grid, string word, vector<string> words);

bool yes_no();