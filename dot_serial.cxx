// dot_serial.cxx

// Compile:
//    g++-9 -Wall -pedantic -std=c++17 dot_serial.cxx -o serial.exe

// Usage:
//    ./serial.exe


#include <chrono>
#include <iostream>
#include <random>
#include <vector>


double dot_serial(std::int32_t n, double* x, double* y)
{
  double dot{0.0};

  for (std::int32_t i = 0; i < n; ++i)
    dot = dot + x[i] * y[i];

  return dot;
}


int main()
{
  std::int32_t len{5000};

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_serial( len, a.data(), b.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
