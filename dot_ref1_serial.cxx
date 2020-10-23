// dot_ref1_serial.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -O3 dot_ref1_serial.cxx -o serial.exe

// Usage:
//    ./serial.exe len


#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>


double dot_serial(std::int32_t n, double* x, double* y)
{
  double dot{0.0};

  for (std::int32_t i = 0; i < n; ++i)
    dot = dot + x[i] * y[i];

  return dot;
}


int main(int argc, char** argv)
{
  std::int32_t len{6553600};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_serial( len, a.data(), b.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << std::fixed
            << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
