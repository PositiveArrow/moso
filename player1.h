#pragma once

#include <random>

class Board2;
class Player1 {
public:
  // Constructor
  Player1(Board2& board);
  Player1(Board2& board, int32_t seed);
  
  // Play
  void Play(void);
  
  bool PlayOneStep(void);
  
  int32_t GetSeed(void) { return seed_; }
  int32_t GetScore(void) { return score_; }
private:
  Board2& board_;
  int32_t seed_;
   std::minstd_rand gen_;
//  std::mt19937 gen_;
  // Final score
  int32_t score_;
};

// Player1a: just pick one playable location at "random" with a distribution centered
// at the last location played.
// We use the discrete distribution from C++11.
// We use max(abs(dx), abs(dy)) for distance.
// So, the maximum distance possible is 64 (Board::size_ * 2).
// So given the distance, the distribution weight is w = 256/(max(5, d) - 4);
class Player1a {
public:
  // Constructor
  Player1a(Board2& board);
  Player1a(Board2& board, int32_t seed);
  
  // Play
  void Play(void);
  
  bool PlayOneStep(void);
  
  int32_t GetSeed(void) { return seed_; }
  int32_t GetScore(void) { return score_; }
private:
  Board2& board_;
  int32_t seed_;
  std::minstd_rand gen_;
  // Last move
  int32_t last_i = 32;
  int32_t last_j = 32;
  // Final score
  int32_t score_;
};

