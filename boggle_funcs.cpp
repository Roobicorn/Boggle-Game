#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
#include <limits> // numeric_limits 

using namespace std;

void greet()
{
   //start screen
   cout << "\n           ***************\n";
   cout << "           * B O G G L E *\n";
   cout << "           ***************\n\n";

   cout << " Make as many words as you can in 3 minutes\n";
   cout << " using connected letters on the grid.\n";
   cout << " (connected = adjacent or diagonal)\n\n";

   cout << " Enter '0' to end game.\n\n";
}

int get_players()
{
   //multiplayer functionality
   //get players
   int players = 0;
   while (players < 1 || players > 4)
   {
      cout << " How many players? (1-4): ";
      cin >> players;

      if (cin.fail())
      {
         cout << " Enter number from 1 to 4.\n";
         players = 0;
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }      
   }

   return players;
}


void shake(vector<char> &grid, char die[][6])
{  
   //take random value from each dice & put in unique position in grid
   int position = 0;

   // seed rand
   srand(time(NULL));

   for (int dice_placed = 0; dice_placed < 16; dice_placed++) 
   {
      bool done = false;
      while (!done)
      {
         position = rand() % 16;  //selects random grid position
            
         //checks if position is empty and if so, places die
         if(grid[position] == '_')
         {    
            grid[position] = die[dice_placed][rand() % 6];
            done = true;
         }
      }
   }
}

void print_grid(vector<char> grid){
   // Q message:
   bool q_mess = false;    
   
   //print grid:
   cout << "\n";
   int position = 0;
   for (int i = 0; i < 4; i++)
   {
      cout << " ";
      for (int j = 0; j < 4; j++)
      {
         if(grid[position] == 'Q')
         {
            q_mess = true;   
         }
         cout << grid[position] << " ";
         position++;            
      }
      cout << "\n";
   }

   if (q_mess)
   {
      //If 'Q' exists on grid, prints following message:
      cout << "\n* for 'Q', read 'Qu'\n";
   }
   cout << "\n";
}

int wordscore(int length)
{
   //returns score based on word length
   if (length < 3)
      return 0;
   else if (length < 5)
      return 1;
   else if (length < 6)
      return 2;
   else if (length < 7)
      return 3;
   else if (length < 8)
      return 5;
   else
      return 11;
}

int calculate_score(vector<int> scores)
{
   //returns sum of scores vector
   int total = 0;
   for (int i = 0; i < scores.size(); i++)
   {
      total += scores[i];
   }
   return total;
}


vector<int> connected_pos(vector<int> temp_path)
{
   //returns vector of adjacent grid positions to argument
   /*
      in a 4x4 grid with positions numbered 0-15, adjacent grid positions relative to a given position
      follow a pattern depending on which column it's in (ie, position index mod 4).
      This saves writing 16 different cases for adjacent grid positions.
   */

   int current_pos = temp_path.back();
   int mod_pos = current_pos % 4;
   vector<int> connected(0);
   vector<int> conx;
   
   switch (mod_pos){
 
      case 0:
      {
         conx = {-4, -3, 1, 4, 5};
         break;
      }
      case 3:
      {
         conx = {-5, -4, -1, 3, 4};
         break;
      }
      default:
      {
         conx = {-5, -4, -3, -1, 1, 3, 4, 5};
         break;
      }
   }
   
   //Check if connected positions are 'unique' or have already been used in current path
   bool unique = true;

   for (int i = 0; i < conx.size(); i++)
   {
      for (int j = 0; j < temp_path.size(); j++)
      {
         if (current_pos + conx[i] == temp_path[j])
         {
            unique = false;
         }
      }
      
      //creates array of unique connected grid positions to argument
      if (unique && current_pos + conx[i] >= 0 && current_pos + conx[i] <= 15)
      {
         connected.push_back(current_pos + conx[i]);
      }  
      
      unique = true;
   }

   return connected;
}

bool word_path_valid(vector<char> &grid, string &word)
{
   // Checks if a given word exists on the grid, using unique connected letters.
   /*
      This function first checks the first letter of the word against the letter in each 
      position on the grid. If one matches, the position is added to a temp_path and the function 
      checks the next letter of the word against the letter in each unique connected position 
      to the previous position. This process repeats until either a valid path is found for the whole word,
      or all possibilities exhausted, and no valid path is found.
   */

   vector< vector<int> > potential_pos(word.size(), vector<int>(0));
   vector<int> p_i(word.size(), 0); //potential pos iterators initialised to 0
   vector<int> temp_path;
   string temp_word = "";

   for (int i = 0; i < grid.size(); i++) //sets first search range to 0-15
   { 
      potential_pos[0].push_back(i);
   }  
  
   int j = 0; // current index of word
   int temp_pos;

   while (j >= 0 && p_i[j] + 1 <= potential_pos[j].size()) //cycle through potential positions
   {
 /*    //print temp path & word for testing
      for(int i = 0; i < temp_path.size(); i++){
            cout << temp_path[i];
      }
      cout << "\n";

      for(int i = 0; i < temp_word.size(); i++){
            cout << temp_word[i];
      }
      cout << "\n";
*/     

      temp_pos = potential_pos[j][p_i[j]];

      // if current grid letter DOESN'T MATCH current word letter, +1 to grid position
      if (grid[temp_pos] != word[j])
      {

         if (p_i[j] + 1 < potential_pos[j].size())
         {
            p_i[j]+= 1; 
         } 
      // if potential grid positions exhausted, step back to previous letter (j-1)
         else
         {
            p_i[j] = 0; //reset iterator
            j--;

            if (j < 0) //no more potential matches for first letter
            {
               return false;
            } 
            else 
            {
               temp_word.pop_back(); 
               temp_path.pop_back();
               p_i[j] += 1; //increase iterator for previous letter
            }

         }

      }
      else //if current grid letter MATCHES current word letter, 
      {

         temp_path.push_back(temp_pos); //plot current path
         temp_word.push_back(grid[temp_pos]); //plot current word

         if (word == temp_word)
         {
            return true;
         }
         else
         {     
            j++; //move on to next letter of word
            potential_pos[j] = connected_pos(temp_path); //create potential range for next letter of word.             
         }
      }  
   }

   return false;
}


bool word_unique(string word, vector<string> words)
{
   bool unique = true;

   for (int i = 0; i < words.size() -1; i++)
   {
      if (word == words[i])
      {
         unique = false;
      }
   }
   return unique;
}

bool word_in_dict(string &word, vector<string> &dict)
{
   bool in_dict = false;
   for (int i = 0; i < dict.size(); i++)
   {
      if (word == dict[i])
      {
         in_dict = true;         
      }
   }
   return in_dict;
}

vector<string> import_dict()
{
   ifstream collins("Collins.txt");
   string line;
   vector<string> dict;

   while(getline(collins, line))
   {
      dict.push_back(line);
   }

   collins.close();
   return dict;
}

bool word_valid(vector<char> grid, string word, vector<string> words, vector<string> dict)
{
   bool valid = false;
               
   if (word_path_valid(grid, word))
   {
 
      if (word_in_dict(word, dict))
      {
 
         if (word_unique(word, words))
         {
            valid = true;
         }
         else
         {
            cout << "Repeated word, 0 points\n";
         }

      }
      else
      {
         cout << "Word not in dictionary, 0 points\n";
      }
   }
   else
   {
      cout << "Not on grid, 0 points\n";
   } 

   return valid;
}

bool yes_no()
{
   char yesno;

   cin >> yesno;     
   
   if(toupper(yesno)=='Y')
   {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return true;
   } 
   else 
   {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return false;
   }   
}

void print_word_lists(int players, vector<vector<string>> &words, vector<vector<int>> &scores)
{
   //End of round - display all accepted words in columns

   int list_length = 0;
   for(int p = 0; p < players; p++)
   {
      if (words[p].size() > list_length)
      {
         list_length = words[p].size();
      }
   }

   for (int p = 0; p < players; p++)
   {
      cout << left << setw(20) << "Player " + to_string(p+1);
   }
   cout << "\n";

   for(int i= 0; i < list_length; i++)
   {
      for (int p = 0; p < players; p++)
      {
         if(i < words[p].size()){
            cout << left << setw(17) << words[p][i]
               << setw(3) << scores[p][i];
         } 
         else 
         {
            cout << left << setw(20) << " ";
         }
      }
      cout << "\n";
   }

   for (int p = 0; p < players; p++)
   {
      cout << left << setw(20) << "Round Total: " + to_string(calculate_score(scores[p]));
   }
   cout << "\n\n";

}

void print_total_scores(int &players, vector<int> &total_score)
{
   for (int p = 0; p < players; p++)
   {
      cout << left << setw(20) << "Player " + to_string(p+1);
   }
   cout << "\n";

   for (int p = 0; p < players; p++)
   {
      cout << left << setw(20) << "Total Score: " + to_string(total_score[p]);
   }
   cout << "\n";
}

int winner(int players, vector<int> score) //returns winning player index, or -1 in case of draw.
{
   int highest_score = 0;
   int winner = -1;
   for (int p = 0; p < players; p++)
   {
      if (score[p] > highest_score)
      {
         highest_score = score[p];
         winner = p;
      }
   }

   //check for tie:
   for (int p = 0; p < players; p++)
   {
      if (p != winner && score[p] == highest_score)
      {
         winner = -1;
      }
   }

   return winner;
}
