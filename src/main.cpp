#include <cstdint>
#include <iostream>
#include <limits>

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Mandelbrot.h"

using namespace std;
using namespace fractal;

int main() {
  const int HEIGHT = 600;
  const int WIDTH  = 800;

  uint8_t min = numeric_limits<uint8_t>::max();
  uint8_t max = numeric_limits<uint8_t>::min();
  Bitmap bitmap(WIDTH, HEIGHT);
  for(int y = 0; y < HEIGHT; y++)
    for(int x = 0; x < WIDTH; x++)
    {
      double xFractal = 2.0*(x - 200)/(HEIGHT-1) - 1;
      double yFractal = 2.0*y/(HEIGHT-1) - 1;

      int iterations = Mandelbrot::getIterations(xFractal, yFractal);
      uint8_t color =
        static_cast<uint8_t>(
            256*static_cast<double>(iterations)/Mandelbrot::NBR_ITERATIONS
        );
      // uint8_t color = (uint8_t);

      color = color*color*color;

      bitmap.setPixel(x, y, 0, color, 0);

      if (color < min) min = color;
      if (color > max) max = color;
    }
  bitmap.write("test.bmp");
  cout << "min: " << static_cast<int>(min) << " max: " << static_cast<int>(max) << endl;
  cout << "Done" << endl;
  return 0;

} // main
