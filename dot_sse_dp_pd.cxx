// dot_sse_dp_pd.cxx

// Compile:
//    g++-9 -Wall -pedantic -msse4 -std=c++17 dot_sse_dp_pd.cxx -o sse_dp_pd.exe

// Usage:
//    ./sse_dp_pd.exe


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_sse_dp_pd(std::int32_t n, double* x, double* y)
{
  const int mask = 0b11110001;

  __m128d temp = _mm_setzero_pd();

  for (std::int32_t i = 0; i < n; i = i + 2) {
    __m128d vx = _mm_load_pd(&x[0]);
    __m128d vy = _mm_load_pd(&y[0]);
    temp = _mm_dp_pd(vx, vy, mask);
  }

  double sum[2];
  _mm_store_pd(&sum[0], temp);

  //std::cout << "\ninside function:"
  //          << "\nsum[0] = " << sum[0]
  //          << "\nsum[1] = " << sum[1] << std::endl;

  return sum[0];
}


int main()
{
  std::int32_t len{5000};

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_sse_dp_pd( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
