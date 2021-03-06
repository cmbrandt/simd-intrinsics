// dot_02_sse4_vertical_2.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -msse4 -O3 dot_02_sse4_vertical_2.cxx -o sse4_vertical_2.exe

// Usage:
//    ./sse4_vertical_2.exe len


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_02_sse4_vertical_2(std::int32_t n, double x[], double y[])
{
  __m128d temp1 = _mm_setzero_pd();
  __m128d temp2 = _mm_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 4) {
    __m128d vx = _mm_load_pd(&x[i]);
    __m128d vy = _mm_load_pd(&y[i]);
    temp1 = _mm_add_pd(_mm_mul_pd(vx, vy), temp1);
    vx    = _mm_load_pd(&x[i+2]);
    vy    = _mm_load_pd(&y[i+2]);
    temp2 = _mm_add_pd(_mm_mul_pd(vx, vy), temp2);
  }

  temp2 = _mm_add_pd(temp1, temp2);

  __m128d high64 = _mm_unpackhi_pd(temp2, temp2);
  return _mm_cvtsd_f64(_mm_add_sd(temp2, high64));
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_02_sse4_vertical_2( len, x.data(), y.data() );

  auto t1  = std::chrono::steady_clock::now();
       dot = dot_02_sse4_vertical_2( len, x.data(), y.data() );
  auto t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
