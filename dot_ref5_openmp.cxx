// dot_ref5_openmp.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -fopenmp -mavx512f -mfma -O3 -mavx512f dot_ref5_openmp.cxx -o openmp.exe

// Usage:
//    ./openmp.exe len


#include <chrono>
#include <iostream>
#include <vector>
#include <omp.h>


double dot_ref5_openmp(std::int32_t n, double x[], double y[])
{
  double dot{0.0};

  #pragma omp simd reduction (+:dot)
    for (std::int32_t i = 0; i < n; ++i)
      dot = dot + x[i] * y[i];

  return dot;
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  double dot = dot_ref5_openmp( len, a.data(), b.data() );

  auto t1  = std::chrono::steady_clock::now();
       dot = dot_ref5_openmp( len, a.data(), b.data() );
  auto t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
