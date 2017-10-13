#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

namespace fractal {

// align struct on a 2 byte boundary
#pragma pack(2)
struct BitmapFileHeader {
  char header[2]{'B', 'M'};
  int32_t fileSize;
  int32_t reserved{0};
  int32_t dataOffset;
};

}  // namespace fractal

#endif // BITMAPFILEHEADER_H_
