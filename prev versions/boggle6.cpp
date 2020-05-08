//version 6: multiplayer added

#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <limits> // numeric_limits 
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
      
   while (repeat)
   {
      //multiplayer functionality
      //get players
      int players = 0;
      while (players < 1 || players > 4)
      {
         cout << "How many players? (1-4): ";
         cin >> players;

         if (cin.fail())
         {
            cout << "Enter number from 1 to 4.\n";
            players = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }      
      }   

      //initialise game variables
      string word;
      vector< vector<string> > words(players, vector<string>(0));
      vector< vector<int> > scores(players, vector<int>(0));

      //create game grid and initialise to _s
      vector<char> grid(16, '_');

      //randomise grid
      shake(grid, die);

      //multiplayer functionality - cycle through play loop for each player
      for (int p = 0; p < players; p++)
      {
         bool temp;
         cout << "Player " << p + 1 << " ready to begin? (y/n) ";
         temp = yes_no();

         print_grid(grid);

         //Play loop here:
         int playcount = 0;

         time_t start_time = time(NULL);
         int timer = (time(NULL) - start_time);
         bool quit = false;

         while (timer < 180 && !quit)
         {
            if(playcount > 9)
            {
               print_grid(grid);
               playcount = 0;
            }

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
               words[p].push_back(word);

               if(word_valid(grid, word, words[p], dict))
               {
                  scores[p].push_back(wordscore(word.length()));
                  cout << word.length() << " letters, scores " << scores[p].back() << "\n";
               }
               else
               {
                  scores[p].push_back(0);
               }
    
               timer = (time(NULL) - start_time);
            }

            playcount++;
         }

         cout << "\n";
      }
      


      //multiplayer functionality, compare scores & declare winner:
      vector<int> total_score(players);

      for (int p = 0; p < players; p++)
      {
         total_score[p] = calculate_score(scores[p]);

         cout << "Player " << p + 1 << ": ";
         cout << words[p].size() << " words. Total score = " << total_score[p] << "\n";

      }

      int p_win = winner(players, total_score);
      if (p_win == -1)
      {
         cout << "\nIt's a draw!\n";
      }
      else
      {
         cout << "\nPlayer " << p_win + 1 << " wins!\n";
      }

      cout << "Game Over\n";
      
      cout << "Shake again? (y/n): ";
      repeat = yes_no();

   }

   return 0;
}