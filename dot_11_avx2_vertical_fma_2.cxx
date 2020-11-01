// dot_avx2_vertical_fma_2.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -mavx2 -mfma -O3 dot_avx2_vertical_fma_2.cxx -o avx2_vertical_fma_2.exe

// Usage:
//    ./avx2_vertical_fma_2.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_avx2_vertical_fma_2(std::int32_t n, double* x, double* y)
{
  __m256d temp1 = _mm256_setzero_pd();
  __m256d temp2 = _mm256_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 8) {
    __m256d vx = _mm256_load_pd(&x[i]);
    __m256d vy = _mm256_load_pd(&y[i]);
    temp1 = _mm256_fmadd_pd(vx, vy, temp1);
    vx    = _mm256_load_pd(&x[i+4]);
    vy    = _mm256_load_pd(&y[i+4]);
    temp2 = _mm256_fmadd_pd(vx, vy, temp2);
  }

  double sum1[4];
  double sum2[4];

  _mm256_store_pd(&sum1[0], temp1);
  _mm256_store_pd(&sum2[0], temp2);

  return sum1[0] + sum1[1] + sum1[2] + sum1[3]
       + sum2[0] + sum2[1] + sum2[2] + sum2[3];
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_avx2_vertical_fma_2( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
