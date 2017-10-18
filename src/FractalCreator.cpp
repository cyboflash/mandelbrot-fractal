#include "FractalCreator.h"

namespace fractal {
  FractalCreator::FractalCreator(int width, int height):
    m_width(width), m_height(height), m_totalNbrPixels(0),
    m_historgram(new int [Mandelbrot::NBR_ITERATIONS]{0}),
    m_fractal(new int [width*height]{0}),
    m_bitmap(m_width, m_height),
    m_zoomList(m_width, m_height)
  {
    m_zoomList.add(Zoom(m_width/2, m_height/2, 4.0/m_height));
  }

  FractalCreator::~FractalCreator() {
  }

  void FractalCreator::run(std::string name) {
    calculateIteration();
    calculateTotalIterations();
    drawFractal();
    writeBitmap(name);
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
    RGB startColor(0, 0, 29);
    RGB endColor(255, 178, 74);
    RGB colorDiff = endColor - startColor;

    for(int y = 0; y < m_height; y++)
      for(int x = 0; x < m_width; x++)
      {
        uint8_t red   = 0;
        uint8_t green = 0;
        uint8_t blue  = 0;

        int iterations = m_fractal[y*m_width + x];

        if (Mandelbrot::NBR_ITERATIONS != iterations)
        {
          double hue = 0;
          for (int i=0; i<=iterations; i++) {
            hue += static_cast<double>(m_historgram[i])/m_totalNbrPixels;
          }
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
