/*version 7: 
   TO DO: update multiplayer
    Y - remove score display between inputs (and time display?)
    Y - (update playcount to reprint grid as necessary)
      - duplicated words from both players score zero
      - display adjacent player word lists and scores at end of each round
    Y - keep running total and round total (keep players for whole game)
      
   - check b5 test 2 path anomaly
       */

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
 
   //main game loop
   greet();

   //multiplayer: choose how many players (1-4) and initialise total scores
   int players = get_players();
   vector<int> total_score (players, 0);

   //initialise loop condition
   int repeat = true;   
   bool player_ready;
   while (repeat)
   {   

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
         player_ready = false;
         while(!player_ready){
            cout << "Player " << p + 1 << " ready to begin? (y/n) ";
            player_ready = yes_no();
         }

         print_grid(grid);

         //Play loop here:
         int playcount = 0;

         time_t start_time = time(NULL);
         int timer = (time(NULL) - start_time);
         bool quit = false;

         while (timer < 180 && !quit)
         {
            //reprint grid if it scrolls out of view
            if(playcount > 14)
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

                  //hide scores till end. but keep this line for testing
                  //cout << word.length() << " letters, scores " << scores[p].back() << "\n";
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
      
      //multiplayer: compare scores & declare winner:
      vector<int> round_score(players);

      for (int p = 0; p < players; p++)
      {
         round_score[p] = calculate_score(scores[p]);
         total_score[p] += round_score[p];

         cout << "Player " << p + 1 << ": ";
         cout << words[p].size() << " words. Round score = " << round_score[p] << "\n";
         cout << "Total score = " << total_score[p] << "\n";

      }

      int p_win = winner(players, round_score);
      if (p_win == -1)
      {
         cout << "\nIt's a draw!\n";
      }
      else
      {
         cout << "\nPlayer " << p_win + 1 << " wins the round!\n";
      }

      cout << "Round Over\n";
      
      cout << "Shake again? (y/n): ";
      repeat = yes_no();

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
   cout << "Game over\n";

   return 0;
}