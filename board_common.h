#pragma once

#include <cstdint>

// Directions. We used the mask form for everything.
// We might get better performance by having two version depending on the context.
enum Direction {
  N  =   1,
  NW =   2,
  W  =   4,
  SW =   8,
  S  =  16,
  SE =  32,
  E  =  64,
  NE = 128,
  NOK = 256,
};

inline Direction OppositeDir(Direction dir) {
  switch(dir) {
    case N : return S ;
    case NW: return SE;
    case W : return E ;
    case SW: return NE;
    case S : return N ;
    case SE: return NW;
    case E : return W ;
    case NE: return SW;
    default: return NOK;
  }
}

enum class LineConf : uint32_t {
  H4 = 1      , H3 = 1 << 1 , H2 = 1 << 2 , H1 = 1 << 3 , H0 = 1 << 4 ,
  V4 = 1 << 5 , V3 = 1 << 6 , V2 = 1 << 7 , V1 = 1 << 8 , V0 = 1 << 9 ,
  D4 = 1 << 10, D3 = 1 << 11, D2 = 1 << 12, D1 = 1 << 13, D0 = 1 << 14 ,
  A4 = 1 << 15, A3 = 1 << 16, A2 = 1 << 17, A1 = 1 << 18, A0 = 1 << 19,
};

// There are ways to get a completely generic converson using "underlying_type".
// This simple, non generic, version is sufficient and more readable for here.
inline uint32_t ToUI32(LineConf conf) { return static_cast<uint32_t>(conf); }

extern int32_t CountOnes(uint32_t conf);

// For a given move, gives us a 12-bit index (with a board size_ of 32).
extern uint32_t ToALine(int32_t i, int32_t j, LineConf conf);
