// dot_14_avx512_vertical_2.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -mavx512f -O3 dot_14_avx512_vertical_2.cxx -o avx512_vertical_2.exe

// Usage:
//    ./avx512_vertical_2.exe len


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_14_avx512_vertical_2(std::int32_t n, double* x, double* y)
{
  __m512d temp1 = _mm512_setzero_pd();
  __m512d temp2 = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 16) {
    __m512d vx = _mm512_loadu_pd(&x[i]);
    __m512d vy = _mm512_loadu_pd(&y[i]);
    temp1 = _mm512_add_pd(_mm512_mul_pd(vx, vy), temp1);
    vx    = _mm512_loadu_pd(&x[i+8]);
    vy    = _mm512_loadu_pd(&y[i+8]);
    temp2 = _mm512_add_pd(_mm512_mul_pd(vx, vy), temp2);
  }
/*
  double sum[16];
  _mm512_store_pd(&sum[0], temp1);
  _mm512_store_pd(&sum[8], temp2);

  return sum[0]  + sum[1]  + sum[2]  + sum[3]
       + sum[4]  + sum[5]  + sum[6]  + sum[7]
       + sum[8]  + sum[9]  + sum[10] + sum[11]
       + sum[12] + sum[13] + sum[14] + sum[15];
*/
  return _mm512_reduce_add_pd(temp1) + _mm512_reduce_add_pd(temp2);
}


int main(int argc, char** argv)
{
  std::int32_t len{50000};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_14_avx512_vertical_2( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
