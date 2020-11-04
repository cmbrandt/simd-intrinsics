// dot_18_avx512_vertical_fma_4.cxx


// Compile:
//    g++-10 -Wall -pedantic -std=c++17 -mavx512f -mfma -O3 dot_18_avx512_vertical_fma_4.cxx -o avx512_vertical_fma_4.exe

// Usage:
//    ./avx512_vertical_fma_4.exe len


#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_18_avx512_vertical_fma_4(std::int32_t n, double* x, double* y)
{
  __m512d temp1 = _mm512_setzero_pd();
  __m512d temp2 = _mm512_setzero_pd();
  __m512d temp3 = _mm512_setzero_pd();
  __m512d temp4 = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 32) {
    __m512d vx = _mm512_loadu_pd(&x[i]);
    __m512d vy = _mm512_loadu_pd(&y[i]);
    temp1 = _mm512_fmadd_pd(vx, vy, temp1);
    vx    = _mm512_loadu_pd(&x[i+8]);
    vy    = _mm512_loadu_pd(&y[i+8]);
    temp2 = _mm512_fmadd_pd(vx, vy, temp2);
    vx    = _mm512_loadu_pd(&x[i+16]);
    vy    = _mm512_loadu_pd(&y[i+16]);
    temp3 = _mm512_fmadd_pd(vx, vy, temp3);
    vx    = _mm512_loadu_pd(&x[i+24]);
    vy    = _mm512_loadu_pd(&y[i+24]);
    temp4 = _mm512_fmadd_pd(vx, vy, temp4);
  }

  return _mm512_reduce_add_pd(temp1) + _mm512_reduce_add_pd(temp2)
       + _mm512_reduce_add_pd(temp3) + _mm512_reduce_add_pd(temp4);    
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_18_avx512_vertical_fma_4( len, x.data(), y.data() );

  auto   t1  = std::chrono::steady_clock::now();
         dot = dot_18_avx512_vertical_fma_4( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << std::fixed << std::setprecision(0)
            << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
