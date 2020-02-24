#include <iostream>
#include <cstdlib>

int main()
{
  unsigned long long n, count = 0, zeroes = 0;
  std::scanf("%llu", &n);

  unsigned short vs[n];
  for (unsigned long long i = 0; i < n; i++)
  {
    std::scanf("%hu", &vs[i]);

    if (vs[i] == 1)
      count += zeroes;
    else
      zeroes++;
  }

  std::printf("%llu\n", count);
  return 0;
}

/*for (int j = 0; j < i; j++)
    {
      if (vs[i] + vs[j] == 1 && vs[j] == 0)
        count++;
    }
*/