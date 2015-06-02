// Main source for Morpion Solitaire solver

#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <memory>

#include "player1.h"
#include "board2.h"

using namespace std;

int TestBoard(int argc, char** argv)
{
  cout << "Morpion Solitaire V2" << endl;
  
  // Let's play.
  int32_t max_score = 0;
  const int32_t max_loops = 1000000;
  int64_t sum_scores = 0;
  for (int i = 0; i < max_loops; ++i) {
    Board2 board;
    Player1 player(board);
    player.Play();
    sum_scores += player.GetScore();
    if (player.GetScore() > max_score) {     
      max_score = player.GetScore();
      cout << i << " New max_score: " << max_score << endl;
    } else {
//      cout << i << " Score: " << player.GetScore() << " max: " << max_score << endl;
    }
  }
  cout << "Max score found: " << max_score << endl;
  cout << "Average score: " << (double) sum_scores / (double) max_loops << endl;
  return 0;
}

int main(int argc, char** argv)
{
  TestBoard(argc, argv);
  return 0;
}
