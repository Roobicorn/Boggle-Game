#include <iostream>
#include <array>
#include <cstdlib>
#include <time.h>

int main(){

   //create dice arrays:
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

      int dice_placed = 0;
      while (dice_placed == 0){
         position = std::rand() % 16;
         if(grid[position] == '_'){
            grid[position] = d1[std::rand() % 6];
            dice_placed++;
         }
      }

      //repeat above block for each dice array... not efficient, try 2-d arrays for dice?
      
      
      //print grid:
      position = 0;
      for (int i = 0; i < 4; i++){
         for (int j = 0; j < 4; j++){
            std::cout << " " << grid[position];
            position++;
         }
         std::cout << "\n";
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