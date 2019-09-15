#include <iostream>
#include <cmath>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int n, m, k;
  std::cin >> n;
  m = n;
  int q = 1;
  for (int i = 1; n > 0; i++)
  {
    n -= n % q;
    LOG(n / q << " | " << (m - n) * q);
    k = (m - n);
    // LOG(n/q);
    // LOG(m - n);
    q *= 10;
  }

  return 0;
}
