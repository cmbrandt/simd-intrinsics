// dot_13_avx512_vertical.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -mavx512f -O3 dot_13_avx512_vertical.cxx -o avx512_vertical.exe

// Usage:
//    ./avx2_vertical.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_13_avx512_vertical(std::int32_t n, double* x, double* y)
{
  __m512d temp = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 8) {
    __m512d vx = _mm512_loadu_pd(&x[i]);
    __m512d vy = _mm512_loadu_pd(&y[i]);
    temp = _mm512_add_pd(_mm512_mul_pd(vx, vy), temp);
  }
 /*
  double sum[8];
  _mm512_store_pd(&sum[0], temp);

  return sum[0] + sum[1] + sum[2] + sum[3]
       + sum[4] + sum[5] + sum[6] + sum[7];
// */
  return _mm512_reduce_add_pd(temp);
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_13_avx512_vertical( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
