// dot_01_sse4_vertical.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -msse4 -O3 dot_01_sse4_vertical.cxx -o sse4_vertical.exe

// Usage:
//    ./sse4_vertical.exe len


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_01_sse4_vertical(std::int32_t n, double* x, double* y)
{
  __m128d temp = _mm_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 2) {
    __m128d vx = _mm_load_pd(&x[i]);
    __m128d vy = _mm_load_pd(&y[i]);
    temp = _mm_add_pd(_mm_mul_pd(vx, vy), temp);
  }

  __m128d high64 = _mm_unpackhi_pd(temp, temp);
  return _mm_cvtsd_f64(_mm_add_sd(temp, high64));
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_01_sse4_vertical( len, x.data(), y.data() );

  auto   t1  = std::chrono::steady_clock::now();
         dot = dot_01_sse4_vertical( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
