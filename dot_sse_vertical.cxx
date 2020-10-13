// dot_sse_vertical.cxx

// Compile:
//    g++-9 -Wall -pedantic -msse4 -std=c++17 dot_sse_vertical.cxx -o sse_vertical.exe

// Usage:
//    ./sse_vertical.exe


#include <chrono>
#include <iostream>
#include <vector>
#include <immintrin.h>


double dot_sse_vertical(std::int32_t n, double* x, double* y)
{
  return 5;
}


int main()
{
  std::int32_t len{5000};

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_sse_vertical( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
