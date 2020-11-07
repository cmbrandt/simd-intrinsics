// dot_16_avx512_vertical_fma.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -mavx512f -mfma -O3 dot_16_avx512_vertical_fma.cxx -o avx512_vertical_fma.exe

// Usage:
//    ./avx512_vertical_fma.exe len


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_16_avx512_vertical_fma(std::int32_t n, double x[], double y[])
{
  __m512d temp = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 8) {
    __m512d vx = _mm512_loadu_pd(&x[i]);
    __m512d vy = _mm512_loadu_pd(&y[i]);
    temp = _mm512_fmadd_pd(vx, vy, temp);
  }

  return _mm512_reduce_add_pd(temp);
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_16_avx512_vertical_fma( len, x.data(), y.data() );

  auto t1  = std::chrono::steady_clock::now();
       dot = dot_16_avx512_vertical_fma( len, x.data(), y.data() );
  auto t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
