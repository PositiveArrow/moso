#pragma once

#include <cstdint>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "board_common.h"

/** This is a second implementation of board which improves two aspects:
 * - more encapsulation: PossibleMove is an internal class to Board2 and we hid as 
 * much as possible to the users. It should look abstract enough so we can
 * run generic MCTS code (not the goal of this version yet).
 * - representation more focused on possible moves. A move is now represented just 
 * as a possible line and the dot we play is implicit in the move. We still keep allowed
 * move so we can speed up the generation of possible moves.
 *
 **/ 

class Board2 {
public:
  // Constructor
  Board2();
  
    // Can we play a line in the given direction starting at the given location.
  bool IsPlayable(int32_t i, int32_t j, Direction dir) const {
    if ((would_overlap_[i][j] & dir) == 0) return true;
    else return false;
  }

  class PossibleMove {
  public:
    PossibleMove(int32_t i, int32_t j, Direction dir);
    PossibleMove(int32_t i, int32_t j, LineConf conf);
    PossibleMove() : code_(0) {}
    // We only use the low 12 bits
    uint32_t GetKey(void) const { return code_&0xFFF; }
    static uint32_t ToCode(int32_t i, int32_t j, Direction dir);
    // This is the origin of the possible line.
    int32_t Geti(void) const { return (code_&(0x01F<<7)) >> 7; }
    int32_t Getj(void) const { return (code_&(0x01F<<2)) >> 2; }
    // This is where we play the dot (implicit so we need the board as well).
    int32_t GetPlayi(const Board2& board) const;
    int32_t GetPlayj(const Board2& board) const;
    // We store where we played.
    void SetPlayed(int32_t i, int32_t j) {
      // We do not reset to zero beforehand, so it can only be called once.
      code_ |= ((i&0x1F)<<12 | (j&0x1F)<<17);
    }
    int32_t GetPlayedi(void) const { return (code_&(0x01F<<12)) >> 12; }
    int32_t GetPlayedj(void) const { return (code_&(0x01F<<17)) >> 17; }
    
    Direction GetDir(void) const {
      switch (code_&0x3) {
        case 0x0: return Direction::N ;
        case 0x1: return Direction::NE;
        case 0x2: return Direction::E;
        case 0x3: return Direction::SE;
      }
      return (Direction)-1;
    }
    int32_t GetDirKey(void) const {
      return code_&0x3;
    }
   
    // Transformations.
    void Rotate90(void);
    void Rotate180(void);
    void Rotate270(void);
    void MirrorD45(void);
    
  private:
    // Internal representation
    // low 5 bits: i
    // next 5 bits: j
    // Next 2: direction
    // Then, the played move when stored in History.
    // 5 bits: played i
    // 5 bits: played j
    uint32_t code_;
  };

  // Get list of possible moves at current board position.
  const std::vector<PossibleMove>& GetPossibleMoves(void) { return possible_moves_; }
  
  // Play a possible move.
  bool Play(PossibleMove move);
  // Rollback last move
  void Rollback(void);
  
    
  // This class records the moves we play on this board.
  class MoveHistory {
  public:
    // Constructor
    MoveHistory() {
      // Largest history we think we can achieve.
      moves_.reserve(200);
    }
    
    // Record a move we just played.
    void Record(PossibleMove played) { moves_.push_back(played); }
    
    // Get move by position in the game (start at 0).
    PossibleMove GetMove(int32_t move_id) const { return moves_[move_id]; }
    // Get number of moves.
    int32_t NumMoves(void) const { return moves_.size(); }
    PossibleMove PopLast(void) { 
      auto last_move = moves_.back(); moves_.pop_back(); return last_move;
    }
    
    // Transformations.
    void Rotate90(void);
    void Rotate180(void);
    void Rotate270(void);
    void MirrorD45(void);
  private:
    std::vector<PossibleMove> moves_;
  };
  
  const MoveHistory& GetHistory(void) const { return history_; }
  void Replay(const MoveHistory& history);
  
  // Dump  
  void Dump(void) const;

  
public:
  // Board size. The 177 record can fit on size_ 28 (if cross is centered.
  // So we use 32 for the time being. If we find too many games touching the border
  // we can extend.
  // At 32x32, we have 128 bytes for the cells, and 1024 bytes for the forbidden lines.
  static const int32_t size_ = 32;
  // Unique moves possible on this grid. 4 moves per cell (N, NE, E, SE).
  static const int32_t unique_moves = size_*size_*4;
  // Encode for NN training/prediction.
  // This version encodes size * size * (5 channels).
  void EncodeSS5(float new_data[size_][size_][5]) const;
  
private:
  // Update neighbors map.
  void UpdateNeighbors(int32_t i, int32_t j);
  void UnUpdateNeighbors(int32_t i, int32_t j);
  // Update possible moves after we played the given move.
  // Any external reference to possible_moves_ is invalid. So there should not be
  // any reference in scope when we call this function (easy to check in caller's code).
  void PlayCellAndUpdatePossible(int32_t played_i, int32_t played_j, bool un_play);  
  // Return possible lines at given unplayed cell.
  inline uint32_t PossibleLines(int32_t i, int32_t j) const;
  // Append possible lines to list of possible moves (ad hoc API).
  void AppendPossibleLines(int32_t i, int32_t j, uint32_t possibles);

  // Which moves can we make?
  void UpdateAllowed();
  
  // Block lines based on lines we played.
  void BlockLine(int32_t i, int32_t j, Direction dir);
  void UnBlockLine(int32_t i, int32_t j, Direction dir);
  
  // Cells.
  bool cells_[size_][size_];
  // Encode neighbors for each cell.
  // 0-7: horizontal neighbors from left to right.
  // 8-15: vertical neighbors from bottom to top.
  // 16-23: D45 neighbors from left to right.
  // 24-31: D135 neighbors from left to right.
  // We had a border of 4 to reduce the number of tests during update.
  // (we should actually test to see which solution is the fastest).
  uint32_t neighbors_[size_+8][size_+8];

  // Overlap constraints. For a given cell, indicates if a line can be started from
  // the cell and which directions are allowed.
  uint8_t would_overlap_[size_][size_];
  // Second one to see how many times we need to store this information for back tracking.
  uint8_t would_overlap2_[size_][size_];

  // Internal possible moves. Update by "Play" and "UnPlay".
  std::vector<PossibleMove> possible_moves_;
  
  // Game history.
  MoveHistory history_;
};

