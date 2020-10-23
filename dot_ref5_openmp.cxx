// dot_ref5_openmp.cxx


// Compile:
//    g++-9 -Wall -pedantic -fopenmp -std=c++17 -O3 dot_ref5_openmp.cxx -o openmp.exe

// Usage:
//    ./openmp.exe len


#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <omp.h>


double dot_ref_openmp(std::int32_t n, double* x, double* y)
{
  double dot{0.0};

  #pragma omp simd reduction (+:dot)
    for (std::int32_t i = 0; i < n; ++i)
      dot = dot + x[i] * y[i];

  return dot;
}


int main(int argc, char** argv)
{
  std::int32_t len{50000};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_ref_openmp( len, a.data(), b.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
