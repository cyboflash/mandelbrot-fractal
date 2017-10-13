#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <string>
#include <memory>

using namespace std;

namespace fractal {

  class Bitmap {
    private:
      int m_width{0};
      int m_height{0};
      unique_ptr<uint8_t> m_pPixels{nullptr};
    public:
      Bitmap(int m_width, int m_height);
      virtual ~Bitmap();

      bool write(string filename);
      void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

  };


}  // namespace fractal

#endif // BITMAP_H_
