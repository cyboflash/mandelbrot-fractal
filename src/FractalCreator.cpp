#include <assert.h>

#include "FractalCreator.h"

namespace fractal {
  FractalCreator::FractalCreator(int width, int height):
    m_width(width), m_height(height), m_totalNbrPixels(0),
    m_historgram(new int [Mandelbrot::NBR_ITERATIONS]{0}),
    m_fractal(new int [width*height]{0}),
    m_bitmap(m_width, m_height),
    m_zoomList(m_width, m_height),
    m_gotFirstRange(false)
  {
    m_zoomList.add(Zoom(m_width/2, m_height/2, 4.0/m_height));
  }

  FractalCreator::~FractalCreator() {
  }

  int FractalCreator::getRange(int iterations) const {
    int rangeIdx = 0;

    for (int i = 1; i < static_cast<int>(m_ranges.size()); i++) {
      rangeIdx = i;
      if (m_ranges[i] > iterations)
        break;
    }

    rangeIdx--;

    assert(rangeIdx >= 0);
    assert(rangeIdx < static_cast<int>(m_ranges.size()));

    return rangeIdx;
  }

  void FractalCreator::run(std::string name) {
    calculateIteration();
    calculateTotalIterations();

    // Insert 0.0 and 1.0 range ends
    // insertColorRangeIfNeeded(0.0, RGB(0, 0, 0));
    // insertColorRangeIfNeeded(1.0, RGB(255, 255, 255));

    calculateRangeTotals();
    drawFractal();
    writeBitmap(name);
  }

  void FractalCreator::insertColorRangeIfNeeded(double rangeEnd, const RGB& rgb) {
    auto it = std::find(m_ranges.begin(), m_ranges.end(), rangeEnd);
    if (it != m_ranges.end()) {
      m_ranges.push_back(rangeEnd);
      m_colors.push_back(rgb);
    }
  }

  void FractalCreator::calculateRangeTotals() {
    int rangeIdx = 0;

    for (int i = 0; i < Mandelbrot::NBR_ITERATIONS; i++) {
      int nbrPixels = m_historgram[i];

      if (i >= m_ranges[rangeIdx+1])
        rangeIdx++;

      m_totalRanges[rangeIdx] += nbrPixels;
    }

  }

  void FractalCreator::addColoRange(double rangeEnd, const RGB& rgb) {
    m_ranges.push_back(rangeEnd*Mandelbrot::NBR_ITERATIONS);
    m_colors.push_back(rgb);

    if (m_gotFirstRange) {
      m_totalRanges.push_back(0);
    }
    m_gotFirstRange = true;

  }

  void FractalCreator::calculateIteration() {
    for(int y = 0; y < m_height; y++)
      for(int x = 0; x < m_width; x++)
      {
        pair<double, double> coords = m_zoomList.doZoom(x, y);

        int iterations = Mandelbrot::getIterations(coords.first, coords.second);

        if (iterations != Mandelbrot::NBR_ITERATIONS)
          m_historgram[iterations]++;

        m_fractal[y*m_width + x] = iterations;
      }
  }

  void FractalCreator::calculateTotalIterations() {
    m_totalNbrPixels = 0;
    for (int i=0; i<Mandelbrot::NBR_ITERATIONS; i++) m_totalNbrPixels += m_historgram[i];

  }

  void FractalCreator::drawFractal() {
    for(int y = 0; y < m_height; y++)
      for(int x = 0; x < m_width; x++)
      {
        uint8_t red   = 0;
        uint8_t green = 0;
        uint8_t blue  = 0;

        int iterations = m_fractal[y*m_width + x];

        int rangeIdx = getRange(iterations);
        int totalRange = m_totalRanges[rangeIdx];
        int rangeStart = m_ranges[rangeIdx];

        RGB& startColor = m_colors[rangeIdx];
        RGB& endColor = m_colors[rangeIdx+1];
        RGB colorDiff = endColor - startColor;

        if (Mandelbrot::NBR_ITERATIONS != iterations)
        {
          int totalPixels = 0;
          for (int i=rangeStart; i<=iterations; i++) {
            totalPixels += m_historgram[i];
          }
          double hue = static_cast<double>(totalPixels)/totalRange;
          red = startColor.r + colorDiff.r*hue;
          green = startColor.g + colorDiff.g*hue;
          blue = startColor.b + colorDiff.b*hue;
        }

        m_bitmap.setPixel(x, y, red, green, blue);
      }
  }

  void FractalCreator::writeBitmap(std::string filename) {
    m_bitmap.write(filename);
  }

  void FractalCreator::addZoom(const Zoom& zoom) {
    m_zoomList.add(zoom);
  }
}
