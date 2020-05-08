//version 5: Added dictionary & tidied some code

#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include "boggle_funcs.hpp"

using namespace std;

int main(){

   //create dice arrays:
   char die[16][6]{{'R', 'I', 'F', 'O', 'B', 'X'}, {'I', 'F', 'E', 'H', 'E', 'Y'}, {'D', 'E', 'N', 'O', 'W', 'S'}, {'U', 'T', 'O', 'K', 'N', 'D'}, {'H', 'M', 'S', 'R', 'A', 'O'}, {'L', 'U', 'P', 'E', 'T', 'S'}, {'A', 'C', 'I', 'T', 'O', 'A'}, {'Y', 'L', 'G', 'K', 'U', 'E'}, {'Q', 'B', 'M', 'J', 'O', 'A'}, {'E', 'H', 'I', 'S', 'P', 'N'}, {'V', 'E', 'T', 'I', 'G', 'N'}, {'B', 'A', 'L', 'I', 'Y', 'T'}, {'E', 'Z', 'A', 'V', 'N', 'D'}, {'R', 'A', 'L', 'E', 'S', 'C'}, {'U', 'W', 'I', 'L', 'R', 'G'}, {'P', 'A', 'C', 'E', 'M', 'D'}};
   
   //import dictionary
   vector<string> dict = import_dict();

   //initialise loop condition
   int repeat = true;
   
   //main game loop
   greet();
   
   cout << " Ready to play? (y/n): ";
   repeat = yes_no();   
   
   while (repeat)
   {

      //initialise game variables
      string word;
      vector<string> words;
      vector<int> scores;

      //create game grid and initialise to _s
      vector<char> grid(16, '_');

      //randomise grid & print
      shake(grid, die);
      print_grid(grid);

      //Play loop here:
      
      time_t start_time = time(NULL);
      int timer = (time(NULL) - start_time);
      bool quit = false;

      while (timer < 180 && !quit)
      {
         cout << "Time remaining: " << (180 - timer) << "\n"; 
         cout << "Enter word: ";
         cin >> word;

         for (int i = 0; i < word.length(); i++)
         {
            word[i] = toupper(word[i]);
         }

         if (word == "0")
         {
            quit = true;
         } 
         else 
         {
            words.push_back(word);

            if(word_valid(grid, word, words, dict))
            {
               scores.push_back(wordscore(word.length()));
               cout << word.length() << " letters, scores " << scores.back() << "\n";
            }
            else
            {
               scores.push_back(0);
            }
           
 
            timer = (time(NULL) - start_time);
         }
      }
      
      int total_score = calculate_score(scores);
      cout << "Game Over\n";
      cout << words.size() << " words. Total score = " << total_score << "\n";
      
      cout << "\nShake again? (y/n): ";
      repeat = yes_no();

   }

   return 0;
}