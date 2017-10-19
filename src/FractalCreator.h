#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include <vector>

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

      std::vector<int> m_ranges;
      std::vector<RGB> m_colors;

      std::vector<int> m_totalRanges;

      bool m_gotFirstRange{false};

      void insertColorRangeIfNeeded(double rangeEnd, const RGB& rgb);

      void calculateRangeTotals();
      void calculateIteration();
      void calculateTotalIterations();
      void drawFractal();
      void writeBitmap(std::string filename);
      int getRange(int iterations) const;

    public:
      FractalCreator(int width, int height);
      virtual ~FractalCreator();

      void addZoom(const Zoom& zoom);
      void run(std::string name);
      void addColoRange(double rangeEnd, const RGB& rgb);

  };
}

#endif // FRACTALCREATOR_H_
