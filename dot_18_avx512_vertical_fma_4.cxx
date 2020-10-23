// dot_18_avx512_vertical_fma_4.cxx


// Compile:
//    g++-9 -Wall -pedantic -std=c++17 -mavx512f -mfma -O3 dot_18_avx512_vertical_fma_4.cxx -o avx512_vertical_fma_4.exe

// Usage:
//    ./avx512_vertical_fma_4.exe len


#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <immintrin.h>


double dot_18_avx512_vertical_fma_4(std::int32_t n, double* x, double* y)
{
  __m512d temp1 = _mm512_setzero_pd();
  __m512d temp2 = _mm512_setzero_pd();
  __m512d temp3 = _mm512_setzero_pd();
  __m512d temp4 = _mm512_setzero_pd();

  for (std::int32_t i = 0; i < n; i += 16) { // seg fault for i += 32
    __m512d vx = _mm512_load_pd(&x[i]);
    __m512d vy = _mm512_load_pd(&y[i]);
    temp1 = _mm512_fmadd_pd(vx, vy, temp1);
    vx    = _mm512_loadu_pd(&x[i+8]);
    vy    = _mm512_loadu_pd(&y[i+8]);
    temp2 = _mm512_fmadd_pd(vx, vy, temp2);
    vx    = _mm512_loadu_pd(&x[i+16]);
    vy    = _mm512_loadu_pd(&y[i+16]);
    temp3 = _mm512_fmadd_pd(vx, vy, temp3);
    vx    = _mm512_loadu_pd(&x[i+24]);
    vy    = _mm512_loadu_pd(&y[i+24]);
    temp4 = _mm512_fmadd_pd(vx, vy, temp4);
  }

  double sum[32];
  _mm512_store_pd(&sum[0],  temp1);
  _mm512_store_pd(&sum[8],  temp2);
  _mm512_store_pd(&sum[16], temp3);
  _mm512_store_pd(&sum[24], temp4);

  return sum[0]  + sum[1]  + sum[2]  + sum[3]
       + sum[4]  + sum[5]  + sum[6]  + sum[7]
       + sum[8]  + sum[9]  + sum[10] + sum[11]
       + sum[12] + sum[13] + sum[14] + sum[15]
       + sum[16] + sum[17] + sum[18] + sum[19]
       + sum[20] + sum[21] + sum[22] + sum[23]
       + sum[24] + sum[25] + sum[26] + sum[27]
       + sum[28] + sum[29] + sum[30] + sum[31];
}


int main(int argc, char** argv)
{
  std::int32_t len{65536};

  if (argc > 1)
    len = std::stoi(argv[1]);

  std::vector<double> x(len, 1.0);
  std::vector<double> y(len, 1.0);

  double dot = dot_18_avx512_vertical_fma_4( len, x.data(), y.data() );

  auto   t1  = std::chrono::steady_clock::now();
         dot = dot_18_avx512_vertical_fma_4( len, x.data(), y.data() );
  auto   t2  = std::chrono::steady_clock::now();

  auto dur =
    std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << std::fixed << std::setprecision(0)
            << "\nsize     = " << len
            << "\nsolution = " << dot
            << "\ntime     = " << dur.count() << std::endl;
}
