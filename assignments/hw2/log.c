#include <stdio.h>


double approxLog(double a, int n)
{
  double deltaX = (a - 1) / N;
  double sum = 0.0;

    // Loop through each partition to compute the area of the trapezoid
  for (int k = 1; k <= N; ++k) {
    double xk_minus_1 = 1 + (k - 1) * deltaX;
    double xk = 1 + k * deltaX;

        // Apply the trapezoidal rule for each partition
    sum += (deltaX / 2) * (1 / xk_minus_1 + 1 / xk);
    }

  return sum;
}

int main(int argc, char* argv[])
{
  double a;
  int n;
  printf("Enter a: ");
  scanf("%lf", &a);
  printf("Enter n: ");
  scanf("%d", &n);
  double logarithm = approxLog(a, n);
  printf("Natural logarithm: %lf\n", logarithm);
  return 0;
}
