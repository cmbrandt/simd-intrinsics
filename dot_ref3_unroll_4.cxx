// dot_ref3_unroll_4.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -O3 dot_ref3_unroll_4.cxx -o unroll_4.exe

// Usage:
//    ./unroll_4.exe len


#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>


double dot_unroll_4(std::int32_t n, double* x, double* y)
{
  double temp1{0.0};
  double temp2{0.0};
  double temp3{0.0};
  double temp4{0.0};

  for (std::int32_t i = 0; i < n; i += 4) {
    temp1 = temp1 + x[i]   * y[i];
    temp2 = temp2 + x[i+1] * y[i+1];
    temp3 = temp3 + x[i+2] * y[i+2];
    temp4 = temp4 + x[i+3] * y[i+3];
  }

  return temp1 + temp2 + temp3 + temp4;
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  std::cout << "\na.size() = " << a.size()
            << "\nb.size() = " << b.size() << std::endl;

  auto   t1  = std::chrono::steady_clock::now();
  double dot = dot_unroll_4( len, a.data(), b.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
