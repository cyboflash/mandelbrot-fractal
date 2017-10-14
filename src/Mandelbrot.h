#ifndef MANDELBROT_H_
#define MANDELBROT_H_

namespace fractal {

  class Mandelbrot {
    public :
      Mandelbrot();
      virtual ~Mandelbrot();

      static const int NBR_ITERATIONS = 1000;

    public:
      static int getIterations(double x, double y);

  };
}

#endif // MANDELBROT_H_
