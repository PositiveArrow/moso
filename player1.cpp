#include "player1.h"
#include "board2.h"

#include <iostream>

using namespace std;
// Global seed
static int iseed = 191379573;

// Constructor
Player1a::Player1a(Board2& board)
  : board_(board),seed_(__sync_add_and_fetch(&iseed, 1)), gen_(seed_)
  {}
  
// Constructor with seed provided.
Player1a::Player1a(Board2& board, int32_t seed)
  : board_(board),seed_(seed), gen_(seed_)
  {}

// Play
void Player1a::Play(void) {
  score_ = 0;
  while (true) {
    if (!PlayOneStep()) break;
  }
}
bool Player1a::PlayOneStep(void) {
  auto moves = board_.GetPossibleMoves();
  if (moves.size() == 0) return false;
  score_++;
  // Pick a move at random.
  vector<int> weights;
//    cout << "Weights: ";
  const int32_t bv = 10;
  for (uint32_t i=0; i < moves.size(); ++i) {
    int32_t baseline = (max(bv, max(abs(moves[i].GetPlayi(board_)-last_i),
                                    abs(moves[i].GetPlayj(board_)-last_j))) - (bv - 1));
    weights.push_back(512/(baseline*baseline));
//      cout << weights.back() << " ";
  }
//    cout << endl;
  std::discrete_distribution<int> dis(weights.begin(), weights.end());
  auto next_move = moves[dis(gen_)];
  if (!board_.Play(next_move)) {
    cout << "Bad move... must stop now" << endl;
    return false;
  }
  return true;
}

// Global seed
static int iseed_2 = 191379573;

// Constructor
Player1::Player1(Board2& board)
  : board_(board),seed_(__sync_add_and_fetch(&iseed_2, 1)), gen_(seed_)
  {}
  
// Constructor with seed provided.
Player1::Player1(Board2& board, int32_t seed)
  : board_(board),seed_(seed), gen_(seed_)
  {}
  
// Play
void Player1::Play(void) {
  score_ = 0;
  while (true) {
    if (!PlayOneStep()) break;
  }
}

// Play only one step.
bool Player1::PlayOneStep(void) {
  auto moves = board_.GetPossibleMoves();
  if (moves.size() == 0) return false;
  score_++;
  // Pick a move at random.
  std::uniform_int_distribution<> dis(0, moves.size()-1);
  auto next_move = moves[dis(gen_)];
  if (!board_.Play(next_move)) {
    cout << "Debug info: " << next_move.Geti() << " "
         << next_move.Getj() << " " << next_move.GetDir() << endl;
    cout << "Bad move... must stop now" << endl;
    return false;
  }
//  board_.Dump();
  return true;
}
