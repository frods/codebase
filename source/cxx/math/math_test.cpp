#include "math.h"
#include <stdio.h>
#include <time.h>

void sqrt_test(float val)
{
  printf("Square root of %f = %f\n", val, babilonian(val));

  clock_t start;
  start = clock();
  int iterations = 1000000;
  for(int i = 0; i < iterations; i++)
    babilonian(val);

  float elapsed =  clock() - start;
  float time_per_iteration = elapsed/iterations;
  printf("Time to calculate sqrt %f\n", time_per_iteration);

}

main(int arc, const char* argv[])
{
  // Test square root calculations
  sqrt_test(25.0);
  sqrt_test(2.0);
  sqrt_test(50.0);
  sqrt_test(16.0);
  sqrt_test(100.0);
  sqrt_test(123452356.0);

}
