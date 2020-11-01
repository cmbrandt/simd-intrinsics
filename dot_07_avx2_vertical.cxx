// dot_3_avx2_vertical.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -mavx2 -O3 dot_3_avx2_vertical.cxx -o avx2_vertical.exe

// Usage:
//    ./avx2_vertical.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_3_avx2_vertical(std::int32_t n, double* x, double* y)
{
  __m256d temp = _mm256_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 4) {
    __m256d vx = _mm256_load_pd(&x[i]);
    __m256d vy = _mm256_load_pd(&y[i]);
    temp = _mm256_add_pd(_mm256_mul_pd(vx, vy), temp);
  }

  double sum[4];
  _mm256_store_pd(&sum[0], temp);

  return sum[0] + sum[1] + sum[2] + sum[3];
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_3_avx2_vertical( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
