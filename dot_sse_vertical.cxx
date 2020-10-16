// dot_sse_vertical.cxx

// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -msse4 -O3 dot_sse_vertical.cxx -o sse_vertical.exe

// Usage:
//    ./sse_vertical.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_sse_vertical(std::int32_t n, double* x, double* y)
{
  __m128d temp = _mm_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 2) {
    __m128d vx = _mm_load_pd(&x[i]);
    __m128d vy = _mm_load_pd(&y[i]);
    temp = _mm_add_pd(_mm_mul_pd(vx, vy), temp);
  }

  double sum[2];
  _mm_store_pd(&sum[0], temp);

  return sum[0] + sum[1];
}


int main(int argc, char** argv)
{
  std::int32_t len{50000};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_sse_vertical( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
