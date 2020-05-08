#include <iostream>
#include <array>
#include <cstdlib>
#include <time.h>

int main(){

   //create dice arrays:
/*
   char d1[] = {'R', 'I', 'F', 'O', 'B', 'X'};
   char d2[] = {'I', 'F', 'E', 'H', 'E', 'Y'};
   char d3[] = {'D', 'E', 'N', 'O', 'W', 'S'};
   char d4[] = {'U', 'T', 'O', 'K', 'N', 'D'};
   char d5[] = {'H', 'M', 'S', 'R', 'A', 'O'};
   char d6[] = {'L', 'U', 'P', 'E', 'T', 'S'};
   char d7[] = {'A', 'C', 'I', 'T', 'O', 'A'};
   char d8[] = {'Y', 'L', 'G', 'K', 'U', 'E'};
   char d9[] = {'Q', 'B', 'M', 'J', 'O', 'A'}; //'Q' in Boggle reads 'Qu'
   char d10[] = {'E', 'H', 'I', 'S', 'P', 'N'};
   char d11[] = {'V', 'E', 'T', 'I', 'G', 'N'};
   char d12[] = {'B', 'A', 'L', 'I', 'Y', 'T'};
   char d13[] = {'E', 'Z', 'A', 'V', 'N', 'D'};
   char d14[] = {'R', 'A', 'L', 'E', 'S', 'C'};
   char d15[] = {'U', 'W', 'I', 'L', 'R', 'G'};
   char d16[] = {'P', 'A', 'C', 'E', 'M', 'D'};
*/
   char die[16][6]{{'R', 'I', 'F', 'O', 'B', 'X'}, {'I', 'F', 'E', 'H', 'E', 'Y'}, {'D', 'E', 'N', 'O', 'W', 'S'}, {'U', 'T', 'O', 'K', 'N', 'D'}, {'H', 'M', 'S', 'R', 'A', 'O'}, {'L', 'U', 'P', 'E', 'T', 'S'}, {'A', 'C', 'I', 'T', 'O', 'A'}, {'Y', 'L', 'G', 'K', 'U', 'E'}, {'Q', 'B', 'M', 'J', 'O', 'A'}, {'E', 'H', 'I', 'S', 'P', 'N'}, {'V', 'E', 'T', 'I', 'G', 'N'}, {'B', 'A', 'L', 'I', 'Y', 'T'}, {'E', 'Z', 'A', 'V', 'N', 'D'}, {'R', 'A', 'L', 'E', 'S', 'C'}, {'U', 'W', 'I', 'L', 'R', 'G'}, {'P', 'A', 'C', 'E', 'M', 'D'}};
   //'Q' in Boggle reads 'Qu'

   //main game loop
   int repeat = true;
   char yesno;
   while (repeat){
   
      //create game grid and initialise to _s
      char grid[16];
      for(int i = 0; i < sizeof(grid); i++){
         grid[i] = '_';
      }
      int position = 0;
      
      //take random value from each dice & put in unique position in grid
      // seed rand
      srand(time(NULL));

      for (int dice_placed = 0; dice_placed < 16; dice_placed++) {
         bool done = false;
         while (!done){
            position = std::rand() % 16;  //selects random grid position
            
            //checks if position is empty and if so, places die
            if(grid[position] == '_'){    
               grid[position] = die[dice_placed][std::rand() % 6];
               done = true;
            }
         }
      }

      // Q message:
      bool q_mess = false;    
      
      //print grid:
      position = 0;
      for (int i = 0; i < 4; i++){
         std::cout << " ";
         for (int j = 0; j < 4; j++){
            if(grid[position] == 'Q'){
               q_mess = true;   
               //std::cout << "Qu";
               //position++; 
            } //else {
            std::cout << grid[position] << " ";
            position++;
            //}
         }
         std::cout << "\n";
      }

      if (q_mess){
         std::cout << "\n* for 'Q', read 'Qu'\n";
      }

      position = 0;
   

      std::cout << "\nShake again? (y/n): ";
      std::cin >> yesno;
      std::cout << "\n";
   
      if(toupper(yesno)=='Y'){
         repeat = true;
      } else {
         repeat = false;
      }
    
    
   }

}