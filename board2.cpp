#include "board2.h"

#include <iostream>
#include <algorithm>

using namespace std;

Board2::PossibleMove::PossibleMove(int32_t i, int32_t j, Direction dir):
  code_(ToCode(i,j,dir))
  {
  }

Board2::PossibleMove::PossibleMove(int32_t i, int32_t j, LineConf conf):
  code_(ToALine(i,j,conf))
  {
  }
 
uint32_t Board2::PossibleMove::ToCode(int32_t i, int32_t j, Direction dir)
{
  switch(dir) {
    case Direction::N : return (i<<7)+(j<<2) ;
    case Direction::NE: return (i<<7)+(j<<2)+1;
    case Direction::E : return (i<<7)+(j<<2)+2;
    case Direction::SE: return (i<<7)+(j<<2)+3;
    default:
      return -1;
  }
}

int32_t Board2::PossibleMove::GetPlayi(const Board2& board) const
{
  int32_t i = Geti();
  int32_t j = Getj();
  switch(code_&0x3) {
    case 0: { // North line.
      return i;
    }
    case 1: { // North East.
           if (!board.cells_[i  ][j  ]) return i  ;
      else if (!board.cells_[i+1][j+1]) return i+1;
      else if (!board.cells_[i+2][j+2]) return i+2;
      else if (!board.cells_[i+3][j+3]) return i+3;
      else if (!board.cells_[i+4][j+4]) return i+4;
      else return -1; // Problem.
    }
    case 2: { // East.
           if (!board.cells_[i  ][j  ]) return i  ;
      else if (!board.cells_[i+1][j  ]) return i+1;
      else if (!board.cells_[i+2][j  ]) return i+2;
      else if (!board.cells_[i+3][j  ]) return i+3;
      else if (!board.cells_[i+4][j  ]) return i+4;
      else return -1; // Problem.
    }
    case 3: { // North East.
           if (!board.cells_[i  ][j  ]) return i  ;
      else if (!board.cells_[i+1][j-1]) return i+1;
      else if (!board.cells_[i+2][j-2]) return i+2;
      else if (!board.cells_[i+3][j-3]) return i+3;
      else if (!board.cells_[i+4][j-4]) return i+4;
      else return -1; // Problem.
    }
    default:
      break;
  }
  return -1;
}

int32_t Board2::PossibleMove::GetPlayj(const Board2& board) const
{
  int32_t i = Geti();
  int32_t j = Getj();
  switch(code_&0x3) {
    case 0: { // North line.
           if (!board.cells_[i  ][j])   return j  ;
      else if (!board.cells_[i  ][j+1]) return j+1;
      else if (!board.cells_[i  ][j+2]) return j+2;
      else if (!board.cells_[i  ][j+3]) return j+3;
      else if (!board.cells_[i  ][j+4]) return j+4;
      else return -1; // Problem.
    }
    case 1: { // North East.
           if (!board.cells_[i  ][j  ]) return j  ;
      else if (!board.cells_[i+1][j+1]) return j+1;
      else if (!board.cells_[i+2][j+2]) return j+2;
      else if (!board.cells_[i+3][j+3]) return j+3;
      else if (!board.cells_[i+4][j+4]) return j+4;
      else return -1; // Problem.
    }
    case 2: { // East.
      return j;
    }
    case 3: { // North East.
           if (!board.cells_[i  ][j  ]) return j;
      else if (!board.cells_[i+1][j-1]) return j-1;
      else if (!board.cells_[i+2][j-2]) return j-2;
      else if (!board.cells_[i+3][j-3]) return j-3;
      else if (!board.cells_[i+4][j-4]) return j-4;
      else return -1; // Problem.
    }
    default:
      break;
  }
  return -1;
}

// Constructor
Board2::Board2()
{
  for (int32_t i = 0; i < size_; ++i) {
    for (int32_t j = 0; j < size_; ++j) {
      cells_[i][j] = false;
      neighbors_[i+4][j+4] = 0;
      would_overlap_[i][j] = 0; // All lines possibles initially.
      would_overlap2_[i][j] = 0; // All lines possibles initially.      
    }
  }
  // Draw cross to start with
  int32_t i = size_/2;
  int32_t j = size_/2;
  cells_[i+1][j+1] = true;
  cells_[i+2][j+1] = true;
  cells_[i+3][j+1] = true;
  
  cells_[i+4][j+1] = true;
  cells_[i+4][j  ] = true;
  cells_[i+4][j-1] = true;
  
  cells_[i+4][j-2] = true;
  cells_[i+3][j-2] = true;
  cells_[i+2][j-2] = true;
  
  cells_[i+1][j-2] = true;
  cells_[i+1][j-3] = true;
  cells_[i+1][j-4] = true;
  
  cells_[i+1][j-5] = true;
  cells_[i  ][j-5] = true;
  cells_[i-1][j-5] = true;
  
  cells_[i-2][j-5] = true;
  cells_[i-2][j-4] = true;
  cells_[i-2][j-3] = true;

  cells_[i-2][j-2] = true;
  cells_[i-3][j-2] = true;
  cells_[i-4][j-2] = true;
  
  cells_[i-5][j-2] = true;
  cells_[i-5][j-1] = true;
  cells_[i-5][j  ] = true;
  
  cells_[i-5][j+1] = true;
  cells_[i-4][j+1] = true;
  cells_[i-3][j+1] = true;
  
  cells_[i-2][j+1] = true;
  cells_[i-2][j+2] = true;
  cells_[i-2][j+3] = true;
  
  cells_[i-2][j+4] = true;
  cells_[i-1][j+4] = true;
  cells_[i  ][j+4] = true;
  
  cells_[i+1][j+4] = true;
  cells_[i+1][j+3] = true;
  cells_[i+1][j+2] = true;
  
  // Update initial neighbors.
  for (int32_t i = 0; i < size_; ++i) {
    for (int32_t j = 0; j < size_; ++j) {
      if (cells_[i][j]) {
        UpdateNeighbors(i,j);
        PlayCellAndUpdatePossible(i, j, false);
      }
    }
  }
}

// Update neighbors map.
void Board2::UpdateNeighbors(int32_t i, int32_t j) {
  // There is 4-cell border around the neighbors map.
  i+=4;
  j+=4;
  // Horizontal flags
  neighbors_[i+4][j] |= 0x01;
  neighbors_[i+3][j] |= 0x02;
  neighbors_[i+2][j] |= 0x04;
  neighbors_[i+1][j] |= 0x08;
  neighbors_[i-1][j] |= 0x10;
  neighbors_[i-2][j] |= 0x20;
  neighbors_[i-3][j] |= 0x40;
  neighbors_[i-4][j] |= 0x80;
  // Vertical flags
  neighbors_[i][j+4] |= 0x0100;
  neighbors_[i][j+3] |= 0x0200;
  neighbors_[i][j+2] |= 0x0400;
  neighbors_[i][j+1] |= 0x0800;
  neighbors_[i][j-1] |= 0x1000;
  neighbors_[i][j-2] |= 0x2000;
  neighbors_[i][j-3] |= 0x4000;
  neighbors_[i][j-4] |= 0x8000;
  // D45 flags
  neighbors_[i+4][j+4] |= 0x010000;
  neighbors_[i+3][j+3] |= 0x020000;
  neighbors_[i+2][j+2] |= 0x040000;
  neighbors_[i+1][j+1] |= 0x080000;
  neighbors_[i-1][j-1] |= 0x100000;
  neighbors_[i-2][j-2] |= 0x200000;
  neighbors_[i-3][j-3] |= 0x400000;
  neighbors_[i-4][j-4] |= 0x800000;
  // D135 flags
  neighbors_[i+4][j-4] |= 0x01000000;
  neighbors_[i+3][j-3] |= 0x02000000;
  neighbors_[i+2][j-2] |= 0x04000000;
  neighbors_[i+1][j-1] |= 0x08000000;
  neighbors_[i-1][j+1] |= 0x10000000;
  neighbors_[i-2][j+2] |= 0x20000000;
  neighbors_[i-3][j+3] |= 0x40000000;
  neighbors_[i-4][j+4] |= 0x80000000;
}

// Update neighbors map.
void Board2::UnUpdateNeighbors(int32_t i, int32_t j) {
  // There is 4-cell border around the neighbors map.
  i+=4;
  j+=4;
  // Horizontal flags
  neighbors_[i+4][j] &= ~0x01;
  neighbors_[i+3][j] &= ~0x02;
  neighbors_[i+2][j] &= ~0x04;
  neighbors_[i+1][j] &= ~0x08;
  neighbors_[i-1][j] &= ~0x10;
  neighbors_[i-2][j] &= ~0x20;
  neighbors_[i-3][j] &= ~0x40;
  neighbors_[i-4][j] &= ~0x80;
  // Vertical flags
  neighbors_[i][j+4] &= ~0x0100;
  neighbors_[i][j+3] &= ~0x0200;
  neighbors_[i][j+2] &= ~0x0400;
  neighbors_[i][j+1] &= ~0x0800;
  neighbors_[i][j-1] &= ~0x1000;
  neighbors_[i][j-2] &= ~0x2000;
  neighbors_[i][j-3] &= ~0x4000;
  neighbors_[i][j-4] &= ~0x8000;
  // D45 flags
  neighbors_[i+4][j+4] &= ~0x010000;
  neighbors_[i+3][j+3] &= ~0x020000;
  neighbors_[i+2][j+2] &= ~0x040000;
  neighbors_[i+1][j+1] &= ~0x080000;
  neighbors_[i-1][j-1] &= ~0x100000;
  neighbors_[i-2][j-2] &= ~0x200000;
  neighbors_[i-3][j-3] &= ~0x400000;
  neighbors_[i-4][j-4] &= ~0x800000;
  // D135 flags
  neighbors_[i+4][j-4] &= ~0x01000000;
  neighbors_[i+3][j-3] &= ~0x02000000;
  neighbors_[i+2][j-2] &= ~0x04000000;
  neighbors_[i+1][j-1] &= ~0x08000000;
  neighbors_[i-1][j+1] &= ~0x10000000;
  neighbors_[i-2][j+2] &= ~0x20000000;
  neighbors_[i-3][j+3] &= ~0x40000000;
  neighbors_[i-4][j+4] &= ~0x80000000;
}

inline uint32_t Board2::PossibleLines(int32_t i, int32_t j) const {
  // No immediate close neighbor.
  if ((neighbors_[i+4][j+4] & 0x18181818) == 0) return 0;
  uint32_t result = 0;
  // +4 to skip border.
  uint32_t neigh = neighbors_[i+4][j+4];
  // Now check horizontal lines
  if ((neigh&0x0F) == 0x0F && IsPlayable(i-4, j, E)) { result |= ToUI32(LineConf::H4);}
  if ((neigh&0x1E) == 0x1E && IsPlayable(i-3, j, E)) { result |= ToUI32(LineConf::H3);}
  if ((neigh&0x3C) == 0x3C && IsPlayable(i-2, j, E)) { result |= ToUI32(LineConf::H2);}
  if ((neigh&0x78) == 0x78 && IsPlayable(i-1, j, E)) { result |= ToUI32(LineConf::H1);}
  if ((neigh&0xF0) == 0xF0 && IsPlayable(i  , j, E)) { result |= ToUI32(LineConf::H0);}
  
  // Now vertical lines
  if ((neigh&0x0F00) == 0x0F00 && IsPlayable(i, j-4, N)) { result |= ToUI32(LineConf::V4);}
  if ((neigh&0x1E00) == 0x1E00 && IsPlayable(i, j-3, N)) { result |= ToUI32(LineConf::V3);}
  if ((neigh&0x3C00) == 0x3C00 && IsPlayable(i, j-2, N)) { result |= ToUI32(LineConf::V2);}
  if ((neigh&0x7800) == 0x7800 && IsPlayable(i, j-1, N)) { result |= ToUI32(LineConf::V1);}
  if ((neigh&0xF000) == 0xF000 && IsPlayable(i, j  , N)) { result |= ToUI32(LineConf::V0);}
  
  // Now D45 lines
  if ((neigh&0x0F0000) == 0x0F0000 && IsPlayable(i-4, j-4, NE)) { result |= ToUI32(LineConf::D4);}
  if ((neigh&0x1E0000) == 0x1E0000 && IsPlayable(i-3, j-3, NE)) { result |= ToUI32(LineConf::D3);}
  if ((neigh&0x3C0000) == 0x3C0000 && IsPlayable(i-2, j-2, NE)) { result |= ToUI32(LineConf::D2);}
  if ((neigh&0x780000) == 0x780000 && IsPlayable(i-1, j-1, NE)) { result |= ToUI32(LineConf::D1);}
  if ((neigh&0xF00000) == 0xF00000 && IsPlayable(i  , j  , NE)) { result |= ToUI32(LineConf::D0);}
  
  // Now D135 lines
  if ((neigh&0x0F000000) == 0x0F000000 && IsPlayable(i-4, j+4, SE)) { result |= ToUI32(LineConf::A4);}
  if ((neigh&0x1E000000) == 0x1E000000 && IsPlayable(i-3, j+3, SE)) { result |= ToUI32(LineConf::A3);}
  if ((neigh&0x3C000000) == 0x3C000000 && IsPlayable(i-2, j+2, SE)) { result |= ToUI32(LineConf::A2);}
  if ((neigh&0x78000000) == 0x78000000 && IsPlayable(i-1, j+1, SE)) { result |= ToUI32(LineConf::A1);}
  if ((neigh&0xF0000000) == 0xF0000000 && IsPlayable(i  , j  , SE)) { result |= ToUI32(LineConf::A0);}
  
  return result;
}

// We assume the caller translated the played_move into a played cell (this
// should a unique implicit translation).
void Board2::PlayCellAndUpdatePossible(int32_t played_i, int32_t played_j, bool un_play)
{
  // TEMP
  // cells_[played_i][played_j] = true;
  // UpdateAllowed();
  // return;
  // Version 1: we do not do any optimization. We just go through every line
  // we can place on the board and see if it overlap an existing one.
  // If it doesnt,
//  cout << "Updating possible after " << played_i << " " << played_j << endl;
  // First check each existing possible to see if it's now invalid.
  for (uint32_t k = 0; k < possible_moves_.size();) {
    int32_t di = possible_moves_[k].GetPlayi(*this) - played_i;
    int32_t dj = possible_moves_[k].GetPlayj(*this) - played_j;
    // Skip if too far last played. Not invalidated for sure.
    if (max(abs(di), abs(dj)) > 7) { k++; continue; }
    // If it's not on one of the for main lines going through move_played, it
    // is still valid for sure as well.
    if (di != 0 && dj != 0 && di != dj && di != -dj) { k++; continue; }
    
    // Now we no for sure this possible move is to be checked.
    // We could be clever in checking, but we will simply drop these possible moves
    // And regenerate all the possibles moves for the position along the four main lines
    // going through the place we played.
    if ( k == (possible_moves_.size() - 1)) {
      possible_moves_.pop_back();
      break;
    } else {
      possible_moves_[k] = possible_moves_.back();
      possible_moves_.pop_back();
    }
    // Do not increment k in this case.
  }
  
  // Now can play cell.
  if (un_play)
    cells_[played_i][played_j] = false;
  else
    cells_[played_i][played_j] = true;
  
  // Now add possible moves for the locations around the move played.
  int32_t mini = max(0, played_i-7);
  int32_t maxi = min(size_-1, played_i+7);
  int32_t minj = max(0, played_j-7);
  int32_t maxj = min(size_-1, played_j+7);
  for (int32_t k = -7; k <= 7; ++k) {
    int32_t i = played_i + k;
    int32_t j = played_j;
    if (i >= mini && i <= maxi && !cells_[i][j]) {
      uint32_t possibles = PossibleLines(i, j);
      if (possibles != 0) {
        AppendPossibleLines(i, j, possibles);
      }
    }
    // This trick allow for this function to work after Play or after UnPlay.
    if (k==0) continue;
    i = played_i;
    j = played_j + k;
    if (j >= minj && j <= maxj && !cells_[i][j]) {
      uint32_t possibles = PossibleLines(i, j);
      if (possibles != 0) {
        AppendPossibleLines(i, j, possibles);
      }
    }
    i = played_i + k;
    j = played_j + k;
    if (i >= mini && i <= maxi && j >= minj && j <= maxj && !cells_[i][j]) {
      uint32_t possibles = PossibleLines(i, j);
      if (possibles != 0) {
        AppendPossibleLines(i, j, possibles);
      }
    }
    i = played_i + k;
    j = played_j - k;
    if (i >= mini && i <= maxi && j >= minj && j <= maxj && !cells_[i][j]) {
      uint32_t possibles = PossibleLines(i, j);
      if (possibles != 0) {
        AppendPossibleLines(i, j, possibles);
      }
    }
  }
}


void Board2::AppendPossibleLines(int32_t i, int32_t j, uint32_t possibles)
{
  uint32_t mask = 1;
  while (mask != (0x1<<20)) {
    if ((mask & possibles) != 0) {
      possible_moves_.push_back(PossibleMove(i,j,LineConf(mask)));
    }
    mask <<= 1;
  }
}

void Board2::Dump(void) const {
  // First coordinate is assume to X, 2nd is Y.
  // (0,0) is lower left so we need to start with the end of direction j.
  for (int32_t j = size_-1; j >= 0; --j) {
    if (j < 10) {
      cout << " ";
    }
    cout << j << " ";
    for (int32_t i = 0; i < size_; ++i) {
      if (cells_[i][j]) cout << "X";
      else {
        uint32_t possibles = PossibleLines(i, j);
        if (possibles != 0)
          cout << "O";
        else
          cout << " ";
      }
    }
    cout << endl;
  }
  cout << "   ";
  for (int32_t i = 0; i < size_; ++i) {
    if (i < 10) cout << " ";
    else cout << i/10;
  }
  cout << endl;
  cout << "   ";
  for (int32_t i = 0; i < size_; ++i) {
    cout << i%10;
  }
  
  for (uint32_t i = 0; i < possible_moves_.size(); ++i) {
    cout << possible_moves_[i].Geti() 
         << " " << possible_moves_[i].Getj() 
         << " " << possible_moves_[i].GetDir()
         << " " << endl;
  }
  
  /*
  for (int32_t j = size_-1; j >= 0; --j) {
    for (int32_t i = 0; i < size_; ++i) {
      cout << (int)would_overlap_[i][j] << " ";
    }
    cout << endl;
  }
  */
}

bool Board2::Play(PossibleMove move)
{
  int32_t i = move.GetPlayi(*this);
  int32_t j = move.GetPlayj(*this);
//  cout << "Playing move " << move.Geti() << " " << move.Getj()
//    << " with implicit dot " << i << " " << j << " " << move.GetDir() << endl;
  
  // Sanity checks
  if (i < 0 || i >= size_ || j <=0 || j>= size_) {
    cout << "Bad coordinates in Play: " << i << " " << j << " with codes "
         << move.Geti() << " " << move.Getj() << " " << move.GetDir() << endl;
    return false;
  }
  
  // Is the cell free?
  if (cells_[i][j]) {
    cout << "Cell already played: " << i << " " << j << endl;
    return false;
  }
  
  if (!IsPlayable(move.Geti(), move.Getj(), move.GetDir())) {
    cout << "The move " << move.Geti() << " " << move.Getj() << " " << move.GetDir()
      << " is not playable." << endl;
    return false;
  }
  
  // All cases for constraint:
  // - the three cells in the middle of the line cannot have a line starting there
  // in both directions identical to those of the line we are playing.
  // - on both ends, we have 4 cells (included one ends of the played line) where we cannot
  // start a line that would overlap with the new line.
  int32_t i1 = move.Geti();
  int32_t i2 = i1+4;
  if (move.GetDir() == Direction::N) i2 = i1;
  int32_t j1 = move.Getj();
  int32_t j2 = j1+4;
  if (move.GetDir() == Direction::E) j2 = j1;
  else if (move.GetDir() == Direction::SE) j2 = j1-4;
  for (int32_t k = -3; k <= 3; ++k) {
    BlockLine(i1 + k*(i2-i1)/4, j1 + k*(j2-j1)/4, move.GetDir());
    BlockLine(i2 + k*(i1-i2)/4, j2 + k*(j1-j2)/4, OppositeDir(move.GetDir()));
  }

  // Update neighbors information.
  UpdateNeighbors(i, j);
  // Update possible moves
  PlayCellAndUpdatePossible(i, j, false);

  // Record in history after recording where we played (for rollback and backtracking).
  move.SetPlayed(i, j);
  history_.Record(move);
  return true;
}

void Board2::BlockLine(int32_t i, int32_t j, Direction dir) {
//    cout << "Blocking line starting at " << i << " " << j << " in direction " << dir << endl;
  if ((would_overlap_[i][j] & dir) == 0) {
    would_overlap_[i][j] |= dir;
  } else if ((would_overlap2_[i][j] & dir) == 0) {
    would_overlap2_[i][j] |= dir;
  } else {
    // Error
    cout << "More than two redundant constraints..." << endl;
  }
}

void Board2::UnBlockLine(int32_t i, int32_t j, Direction dir) {
  if ((would_overlap2_[i][j] & dir) != 0) {
    would_overlap2_[i][j] &= ~dir;
  } else if ((would_overlap_[i][j] & dir) != 0) {
    would_overlap_[i][j] &= ~dir;
  } else {
    // Error
    cout << "Trying to unblock an unexistent constraint..." << endl;
  }
}

void Board2::UpdateAllowed(void)
{
  possible_moves_.clear();
  for (int32_t i = 0; i < size_; ++i) {
    for (int32_t j = 0; j < size_; ++j) {
      // Already played there.
      if (cells_[i][j]) {
        continue;
      }
      uint32_t possibles = PossibleLines(i, j);
      if (possibles != 0) {
        AppendPossibleLines(i, j, possibles);
      }
    }
  }
}

// Rollback last move.
void Board2::Rollback(void)
{
  // Get latest move and coordinates.
  auto last_move = history_.PopLast();
  int32_t played_i = last_move.GetPlayedi();
  int32_t played_j = last_move.GetPlayedj();
  // Update all structures in sight.
  int32_t i1 = last_move.Geti();
  int32_t i2 = i1+4;
  if (last_move.GetDir() == Direction::N) i2 = i1;
  int32_t j1 = last_move.Getj();
  int32_t j2 = j1+4;
  if (last_move.GetDir() == Direction::E) j2 = j1;
  else if (last_move.GetDir() == Direction::SE) j2 = j1-4;
  for (int32_t k = -3; k <= 3; ++k) {
    UnBlockLine(i1 + k*(i2-i1)/4, j1 + k*(j2-j1)/4, last_move.GetDir());
    UnBlockLine(i2 + k*(i1-i2)/4, j2 + k*(j1-j2)/4, OppositeDir(last_move.GetDir()));
  }

  // Update neighbors information.
  UnUpdateNeighbors(played_i, played_j);
  // Update possible moves
  PlayCellAndUpdatePossible(played_i, played_j, true);
}

// Encode in SS5 format (we might have other format depending on the type
// of input training data we want to use for our machine learning system.
void Board2::EncodeSS5(float new_data[Board2::size_][Board2::size_][5]) const
{
  std::fill((float*)new_data, ((float*)new_data)+Board2::size_*Board2::size_*5, 0.0f);
  for (int32_t i = 0; i < history_.NumMoves(); ++i) {
    new_data[history_.GetMove(i).GetPlayedi()]
            [history_.GetMove(i).GetPlayedj()]
            [4] = 1.0f;
    new_data[history_.GetMove(i).Geti()]
            [history_.GetMove(i).Getj()]
            [history_.GetMove(i).GetDirKey()] = 1.0f;
  }
  // Add initial cross.
  int32_t i = size_/2;
  int32_t j = size_/2;
  new_data[i+1][j+1][4] = 1.0f;
  new_data[i+2][j+1][4] = 1.0f;
  new_data[i+3][j+1][4] = 1.0f;
  
  new_data[i+4][j+1][4] = 1.0f;
  new_data[i+4][j  ][4] = 1.0f;
  new_data[i+4][j-1][4] = 1.0f;
  
  new_data[i+4][j-2][4] = 1.0f;
  new_data[i+3][j-2][4] = 1.0f;
  new_data[i+2][j-2][4] = 1.0f;
  
  new_data[i+1][j-2][4] = 1.0f;
  new_data[i+1][j-3][4] = 1.0f;
  new_data[i+1][j-4][4] = 1.0f;
  
  new_data[i+1][j-5][4] = 1.0f;
  new_data[i  ][j-5][4] = 1.0f;
  new_data[i-1][j-5][4] = 1.0f;
  
  new_data[i-2][j-5][4] = 1.0f;
  new_data[i-2][j-4][4] = 1.0f;
  new_data[i-2][j-3][4] = 1.0f;

  new_data[i-2][j-2][4] = 1.0f;
  new_data[i-3][j-2][4] = 1.0f;
  new_data[i-4][j-2][4] = 1.0f;
  
  new_data[i-5][j-2][4] = 1.0f;
  new_data[i-5][j-1][4] = 1.0f;
  new_data[i-5][j  ][4] = 1.0f;
  
  new_data[i-5][j+1][4] = 1.0f;
  new_data[i-4][j+1][4] = 1.0f;
  new_data[i-3][j+1][4] = 1.0f;
  
  new_data[i-2][j+1][4] = 1.0f;
  new_data[i-2][j+2][4] = 1.0f;
  new_data[i-2][j+3][4] = 1.0f;
  
  new_data[i-2][j+4][4] = 1.0f;
  new_data[i-1][j+4][4] = 1.0f;
  new_data[i  ][j+4][4] = 1.0f;
  
  new_data[i+1][j+4][4] = 1.0f;
  new_data[i+1][j+3][4] = 1.0f;
  new_data[i+1][j+2][4] = 1.0f;
  
  // Substract mean per channel.
  for (int32_t channel = 0; channel < 5; ++channel) {
    float mean = (float)history_.NumMoves()/((float)Board2::size_ * (float)Board2::size_);
    if (channel == 4) {
      mean = (float)(history_.NumMoves()+36)/((float)Board2::size_ * (float)Board2::size_);
    }
//    cout << "Mean: " << mean << endl;
    float sum2 = 0;
    for (int32_t i = 0; i < size_; ++i) {
      for (int32_t j = 0; j < size_; ++j) {
        new_data[i][j][channel] -= mean;
        sum2 += new_data[i][j][channel]*new_data[i][j][channel];
      }
    }
    sum2 = sqrt(sum2/(size_*size_));
//    cout << "Standard deviation: " << sum2 << endl;
    for (int32_t i = 0; i < size_; ++i) {
      for (int32_t j = 0; j < size_; ++j) {
        new_data[i][j][channel] /= sum2;
//        cout << new_data[i][j][channel] << " ";
      }
    }
  }
}

void Board2::Replay(const MoveHistory& history)
{
  for (int32_t i = 0; i < history.NumMoves(); ++i) {
    Play(history.GetMove(i));
  }
}