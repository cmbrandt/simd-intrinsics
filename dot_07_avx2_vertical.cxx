// dot_07_avx2_vertical.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -mavx2 -O3 dot_07_avx2_vertical.cxx -o avx2_vertical.exe

// Usage:
//    ./avx2_vertical.exe len


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_07_avx2_vertical(std::int32_t n, double x[], double y[])
{
  __m256d temp = _mm256_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 4) {
    __m256d vx = _mm256_loadu_pd(&x[i]);
    __m256d vy = _mm256_loadu_pd(&y[i]);
    temp = _mm256_add_pd(_mm256_mul_pd(vx, vy), temp);
  }

  __m128d low128  = _mm256_castpd256_pd128(temp);
  __m128d high128 = _mm256_extractf128_pd(temp, 1);
  low128 = _mm_add_pd(low128, high128);

  __m128d high64 = _mm_unpackhi_pd(low128, low128);
  return _mm_cvtsd_f64(_mm_add_sd(low128, high64));
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_07_avx2_vertical( len, x.data(), y.data() );

  auto t1  = std::chrono::steady_clock::now();
       dot = dot_07_avx2_vertical( len, x.data(), y.data() );
  auto t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
