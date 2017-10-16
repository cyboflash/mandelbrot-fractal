#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>

#include "Zoom.h"

namespace fractal {
  class FractalCreator {
    public:
      FractalCreator(int width, int height);
      virtual ~FractalCreator();

      void calculateIteration();
      void drawFractal();
      void writeBitmap(std::string filename);
      void addZoom(const Zoom& zoom);

  };
}

#endif // FRACTALCREATOR_H_
