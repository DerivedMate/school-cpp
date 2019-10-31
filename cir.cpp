#include <iostream>
#include <cmath>

int main()
{
  double r, pi = M_PI;
  std::cin >> r;

  std::cout.precision(3);

  std::cout << std::fixed << pi * std::pow(r, double(2)) << std::endl
            << 2.0 * pi * r;

  return 0;
}