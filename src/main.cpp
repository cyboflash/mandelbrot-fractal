#include <iostream>

#include "FractalCreator.h"
#include "Zoom.h"

using namespace std;
using namespace fractal;

int main() {
  FractalCreator fractalCreator(800, 600);
  fractalCreator.addZoom(Zoom(320, 223, 0.1));
  fractalCreator.addZoom(Zoom(337, 337, 0.1));
  fractalCreator.run("test.bmp");

  cout << "Done" << endl;
  return 0;

} // main
