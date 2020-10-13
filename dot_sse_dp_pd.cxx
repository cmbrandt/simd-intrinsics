// dot_sse_dp_pd.cxx

// Compile:
//    g++-9 -Wall -pedantic -msse4 -std=c++17 dot_sse_dp_pd.cxx -o sse_dp_pd.exe

// Usage:
//    ./sse_dp_pd.exe


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_sse_dp_pd(std::int32_t n, double* x, double* y)
{
  return 5;
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
