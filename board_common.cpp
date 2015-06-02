#include "board_common.h"

// This method is from K&R C book.
// There are other options, lots of good methods using bit operations,
// but nowadays we should probably be using gcc builtin popcount.
// This is NOT a bottleneck at this stage.
int32_t CountOnes(uint32_t conf) {
  int32_t result = 0;
  while(conf != 0)
  {
    conf = conf & (conf-1);
    result++;
  }
  return result;
}

uint32_t ToALine(int32_t i, int32_t j, LineConf conf) {
  switch(conf) {
    case LineConf::H4: return ((i-4) << 7) | (j     << 2) | 0x2; break;
    case LineConf::H3: return ((i-3) << 7) | (j     << 2) | 0x2; break;
    case LineConf::H2: return ((i-2) << 7) | (j     << 2) | 0x2; break;
    case LineConf::H1: return ((i-1) << 7) | (j     << 2) | 0x2; break;
    case LineConf::H0: return ((i  ) << 7) | (j     << 2) | 0x2; break;
    case LineConf::V4: return ((i  ) << 7) | ((j-4) << 2) | 0x0; break;
    case LineConf::V3: return ((i  ) << 7) | ((j-3) << 2) | 0x0; break;
    case LineConf::V2: return ((i  ) << 7) | ((j-2) << 2) | 0x0; break;
    case LineConf::V1: return ((i  ) << 7) | ((j-1) << 2) | 0x0; break;
    case LineConf::V0: return ((i  ) << 7) | ((j  ) << 2) | 0x0; break;
    case LineConf::D4: return ((i-4) << 7) | ((j-4) << 2) | 0x1; break;
    case LineConf::D3: return ((i-3) << 7) | ((j-3) << 2) | 0x1; break;
    case LineConf::D2: return ((i-2) << 7) | ((j-2) << 2) | 0x1; break;
    case LineConf::D1: return ((i-1) << 7) | ((j-1) << 2) | 0x1; break;
    case LineConf::D0: return ((i  ) << 7) | ((j  ) << 2) | 0x1; break;
    case LineConf::A4: return ((i-4) << 7) | ((j+4) << 2) | 0x3; break;
    case LineConf::A3: return ((i-3) << 7) | ((j+3) << 2) | 0x3; break;
    case LineConf::A2: return ((i-2) << 7) | ((j+2) << 2) | 0x3; break;
    case LineConf::A1: return ((i-1) << 7) | ((j+1) << 2) | 0x3; break;
    case LineConf::A0: return ((i  ) << 7) | ((j  ) << 2) | 0x3; break;
    default: return false; break;
  }
}
