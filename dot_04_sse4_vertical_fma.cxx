// dot_04_sse4_vertical_fma.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -msse4 -mfma -O3 dot_04_sse4_vertical_fma.cxx -o sse4_vertical_fma.exe

// Usage:
//    ./sse4_vertical_fma.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_04_sse4_vertical_fma(std::int32_t n, double* x, double* y)
{
  __m128d temp = _mm_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 2) {
    __m128d vx = _mm_load_pd(&x[i]);
    __m128d vy = _mm_load_pd(&y[i]);
    temp = _mm_fmadd_pd(vx, vy, temp);
  }

  double sum[2];
  _mm_store_pd(&sum[0], temp);

  return sum[0] + sum[1];
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_04_sse4_vertical_fma( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
