// dot_17_avx512_vertical_fma_2.cxx


// Compile:
//    g++ -Wall -pedantic -std=c++17 -mavx512f -mfma -O3 dot_17_avx512_vertical_fma_2.cxx -o avx512_vertical_fma_2.exe

// Usage:
//    ./avx512_vertical_fma_2.exe len


#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_17_avx512_vertical_fma_2(std::int32_t n, double* x, double* y)
{
  __m512d temp1 = _mm512_setzero_pd();
  __m512d temp2 = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 16) {
    __m512d vx = _mm512_loadu_pd(&x[i]);
    __m512d vy = _mm512_loadu_pd(&y[i]);
    temp1 = _mm512_fmadd_pd(vx, vy, temp1);
    vx    = _mm512_loadu_pd(&x[i+8]);
    vy    = _mm512_loadu_pd(&y[i+8]);
    temp2 = _mm512_fmadd_pd(vx, vy, temp2);
  }

  double sum[16];
  _mm512_store_pd(&sum[0], temp1);
  _mm512_store_pd(&sum[8], temp2);

  return sum[0]  + sum[1]  + sum[2]  + sum[3]
       + sum[4]  + sum[5]  + sum[6]  + sum[7]
       + sum[8]  + sum[9]  + sum[10] + sum[11]
       + sum[12] + sum[13] + sum[14] + sum[15];
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_17_avx512_vertical_fma_2( len, x.data(), y.data() );

  auto   t1  = std::chrono::high_resolution_clock::now();
         dot = dot_17_avx512_vertical_fma_2( len, x.data(), y.data() );
  auto   t2  = std::chrono::high_resolution_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << std::fixed << std::setprecision(0)
            << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
