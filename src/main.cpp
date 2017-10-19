#include <iostream>

#include "FractalCreator.h"
#include "Zoom.h"

using namespace std;
using namespace fractal;

int main() {
  FractalCreator fractalCreator(800, 600);

  fractalCreator.addColoRange(0.0, RGB(0, 0, 255));
  fractalCreator.addColoRange(0.05, RGB(255, 99, 71));
  fractalCreator.addColoRange(0.08, RGB(255, 215, 0));
  fractalCreator.addColoRange(1.0, RGB(255, 255, 255));

  fractalCreator.addZoom(Zoom(320, 223, 0.1));
  fractalCreator.addZoom(Zoom(337, 337, 0.1));
  fractalCreator.run("mandelbrot.bmp");

  cout << "Done" << endl;
  return 0;

} // main
