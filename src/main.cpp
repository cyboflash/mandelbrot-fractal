#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>

#include <math.h>

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Mandelbrot.h"
#include "ZoomList.h"

using namespace std;
using namespace fractal;

int main() {
  const int HEIGHT = 600;
  const int WIDTH  = 800;

  Bitmap bitmap(WIDTH, HEIGHT);

  unique_ptr<int[]> historgram(new int [Mandelbrot::NBR_ITERATIONS]{0});
  unique_ptr<int[]> fractal(new int [WIDTH*HEIGHT]{0});

  ZoomList zoomList(WIDTH, HEIGHT);

  zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/HEIGHT));
  zoomList.add(Zoom(320, HEIGHT-223, 0.1));
  zoomList.add(Zoom(337, HEIGHT-337, 0.1));

  for(int y = 0; y < HEIGHT; y++)
    for(int x = 0; x < WIDTH; x++)
    {
      pair<double, double> coords = zoomList.doZoom(x, y);

      int iterations = Mandelbrot::getIterations(coords.first, coords.second);

      if (iterations != Mandelbrot::NBR_ITERATIONS)
        historgram[iterations]++;

      fractal[y*WIDTH + x] = iterations;

    }

  // calcualte total number of pixels
  int totalNbrPixels = 0;
  for (int i=0; i<Mandelbrot::NBR_ITERATIONS; i++) totalNbrPixels += historgram[i];

  // Draw the fractal
  for(int y = 0; y < HEIGHT; y++)
    for(int x = 0; x < WIDTH; x++)
    {
      uint8_t red   = 0;
      uint8_t green = 0;
      uint8_t blue  = 0;

      int iterations = fractal[y*WIDTH + x];

      if (Mandelbrot::NBR_ITERATIONS != iterations)
      {
        double hue = 0;
        for (int i=0; i<=iterations; i++) {
          hue += static_cast<double>(historgram[i])/totalNbrPixels;
        }
        green = pow(255, hue);
      }

      bitmap.setPixel(x, y, red, green, blue);
    }


  bitmap.write("test.bmp");
  cout << "Done" << endl;
  return 0;

} // main
