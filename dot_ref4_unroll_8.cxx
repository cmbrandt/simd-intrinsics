// dot_ref4_unroll_8.cxx


// Compile:
//    g++-10 -Wall -Wpedantic -std=c++17 -mavx512f -mfma -O3 -mavx512f dot_ref4_unroll_8.cxx -o unroll_8.exe

// Usage:
//    ./unroll_8.exe len


#include <chrono>
#include <iostream>
#include <vector>


double dot_ref4_unroll_8(std::int32_t n, double x[], double y[])
{
  double temp1{0.0};
  double temp2{0.0};
  double temp3{0.0};
  double temp4{0.0};
  double temp5{0.0};
  double temp6{0.0};
  double temp7{0.0};
  double temp8{0.0};

  for (std::int32_t i = 0; i < n; i += 8) {
    temp1 = temp1 + x[i]   * y[i];
    temp2 = temp2 + x[i+1] * y[i+1];
    temp3 = temp3 + x[i+2] * y[i+2];
    temp4 = temp4 + x[i+3] * y[i+3];
    temp5 = temp5 + x[i+4] * y[i+4];
    temp6 = temp6 + x[i+5] * y[i+5];
    temp7 = temp7 + x[i+6] * y[i+6];
    temp8 = temp8 + x[i+7] * y[i+7];
  }

  return temp1 + temp2 + temp3 + temp4
       + temp5 + temp6 + temp7 + temp8;
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> a(len, 1.0);
  std::vector<double> b(len, 1.0);

  double dot = dot_ref4_unroll_8( len, a.data(), b.data() );

  auto t1  = std::chrono::steady_clock::now();
       dot = dot_ref4_unroll_8( len, a.data(), b.data() );
  auto t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\nmicrosec = " << dur.count() << std::endl;
}
