#include <fstream>

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

namespace fractal {
  Bitmap::Bitmap(int width, int height): m_width(width), m_height(height),
                                        m_pPixels(new uint8_t[width*height*3]{})
  {

  }

  Bitmap::~Bitmap() {

  }

  bool Bitmap::write(string filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(fileHeader) + sizeof(infoHeader) + m_width*m_height*3;
    fileHeader.dataOffset = sizeof(fileHeader) + sizeof(infoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    ofstream file;

    file.open(filename, ios::binary);
    if (!file) {
      return false;
    }
    // dynamic_cast<char *>(&fileHeader);
    file.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<char *>(m_pPixels.get()), m_width*m_height*3);

    file.close();
    if (!file) {
      return false;
    }

    return false;

  }
  void Bitmap::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t *pPixel = reinterpret_cast<uint8_t *>(m_pPixels.get());
    pPixel += m_width*y*3 + x*3;
    pPixel[0] = b;
    pPixel[1] = g;
    pPixel[2] = r;
  }
}
