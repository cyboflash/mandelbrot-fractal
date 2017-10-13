#include <iostream>
#include <limits>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Bitmap.h"

using namespace std;
using namespace fractal;

int main() {
  const int HEIGHT = 600;
  const int WIDTH  = 800;

  double min = numeric_limits<double>::max();
  double max = numeric_limits<double>::min();
  Bitmap bitmap(WIDTH, HEIGHT);
  for(int y = 0; y < HEIGHT; y ++)
    for(int x = 0; x < WIDTH; x ++)
    {
      double xFractal = 2.0*x/(WIDTH-1) - 1;
      double yFractal = 2.0*y/(HEIGHT-1) - 1;

      if (xFractal < min) min = xFractal;
      if (xFractal > max) max = xFractal;

      // bitmap.setPixel(x, y, 255, 0, 0);
    }
  // bitmap.write("red.bmp");
  cout << "min: " << min << " max: " << max << endl;
  cout << "Done" << endl;
  return 0;

} // main
