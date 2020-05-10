#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

void greet();

int get_players();

void shake(vector<char> &grid, char die[][6]);

void print_grid(vector<char> grid);

int wordscore(int length);

int calculate_score(vector<int> scores);

vector<int> connected_pos(vector<int> temp_path); 

bool word_path_valid(vector<char> &grid, string &word);

bool word_unique(string word, vector<string> words);

bool word_in_dict(string &word, vector<string> &dict);

vector<string> import_dict();

bool word_valid(vector<char> grid, string word, vector<string> words, vector<string> dict);

bool yes_no();

void print_word_lists(int players, vector<vector<string>> &words, vector<vector<int>> &scores);

void print_total_scores(int &players, vector<int> &total_score);

int winner(int players, vector<int> score);