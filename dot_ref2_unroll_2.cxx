// dot_ref2_unroll_2.cxx

// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -O3 dot_ref2_unroll_2.cxx -o unroll_2.exe

// Usage:
//    ./unroll_4.exe len


#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>


double dot_unroll_2(std::int32_t n, double* x, double* y)
{
  double temp1{0.0};
  double temp2{0.0};

  for (std::int32_t i = 0; i < n; i += 2) {
    temp1 = temp1 + x[i]   * y[i];
    temp2 = temp2 + x[i+1] * y[i+1];
  }

  return temp1 + temp2;
}


int main(int argc, char** argv)
{
  std::int32_t len{50000};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  std::cout << "\na.size() = " << a.size()
            << "\nb.size() = " << b.size() << std::endl;

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_unroll_2( len, a.data(), b.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}