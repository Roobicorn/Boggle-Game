#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

void greet(){
//start screen
   cout << "\n           ***************\n";
   cout << "           * B O G G L E *\n";
   cout << "           ***************\n\n";

   cout << " Make as many words as you can in 3 minutes\n";
   cout << " using connected letters on the grid.\n";
   cout << " (connected = adjacent or diagonal)\n\n";

   cout << " Enter '0' to end game.\n\n";
}

void shake(vector<char> &grid, char die[][6]){  
   int position = 0;

   //take random value from each dice & put in unique position in grid
   // seed rand
   srand(time(NULL));

   for (int dice_placed = 0; dice_placed < 16; dice_placed++) {
      bool done = false;
      while (!done){
         position = rand() % 16;  //selects random grid position
            
         //checks if position is empty and if so, places die
         if(grid[position] == '_'){    
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
   int position = 0;
   for (int i = 0; i < 4; i++){
      cout << " ";
      for (int j = 0; j < 4; j++){
         if(grid[position] == 'Q'){
            q_mess = true;   
         }
         cout << grid[position] << " ";
         position++;
            
      }
      cout << "\n";
   }

   if (q_mess){
      cout << "\n* for 'Q', read 'Qu'\n";
   }
   cout << "\n";
}

int wordscore(int length){
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

int calculate_score(vector<int> scores){
   int total = 0;
   for (int i = 0; i < scores.size(); i++){
      total += scores[i];
   }
   return total;
}


vector<int> connected_pos(vector<int> temp_path) //returns vector of adjacent grid positions to argument
{
   int mod_pos = temp_path.back() % 4;
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
   
   bool unique = true;

   for (int i = 0; i < conx.size(); i++)
   {
      for (int j = 0; j < temp_path.size(); j++)
      {
         if (temp_path.back() + conx[i] == temp_path[j])
         {
            unique = false;
         }
      }

      if (unique && temp_path.back() + conx[i] >= 0 && temp_path.back() + conx[i] <= 15)
      {
         connected.push_back(temp_path.back() + conx[i]);
      }  
      
      unique = true;
   }

   return connected;
}

bool word_path_valid(vector<char> &grid, string &word)
{
   vector< vector<int> > potential_pos(word.size(), vector<int>(0));
   vector<int> p_i(word.size(), 0); //potential pos iterators initialised to 0
   vector<int> temp_path;
   string temp_word = "";

/*   for (int i = 0; i < grid.size(); i++) //sets first search range to 0-15
   { 
      potential_pos[0].push_back(i);
   }  
*/

   potential_pos[0] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};  //less flexible but fewer calculations
  
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





bool word_unique(string word, vector<string> words){
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

bool word_in_dictionary(string word){
   return true;
}

bool word_valid(vector<char> grid, string word, vector<string> words){
   if (word_path_valid(grid, word) && word_unique(word, words) && word_in_dictionary(word)){
      return true;
   } else {
      return false;
   }
}

bool yes_no(){
   char yesno;
   cin >> yesno;
   cout << "\n";
   
   if(toupper(yesno)=='Y'){
      return true;
   } else {
      return false;
   }   
}


