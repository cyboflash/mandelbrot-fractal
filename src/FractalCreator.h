#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include "Zoom.h"
#include "ZoomList.h"

namespace fractal {
  class FractalCreator {
    private:
      int m_width;
      int m_height;
      int m_totalNbrPixels{0};
      std::unique_ptr<int[]> m_historgram;
      std::unique_ptr<int[]> m_fractal;
      Bitmap m_bitmap;
      ZoomList m_zoomList;

      void calculateIteration();
      void calculateTotalIterations();
      void drawFractal();
      void writeBitmap(std::string filename);

    public:
      FractalCreator(int width, int height);
      virtual ~FractalCreator();

      void addZoom(const Zoom& zoom);
      void run(std::string name);

  };
}

#endif // FRACTALCREATOR_H_
