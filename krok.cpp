#include <iostream>

int pow_mod(int x, int pow, int mod) {
  if (pow <= 0) return 1;

  if (pow % 2 == 0) {
    int s = pow_mod(x, pow/2, mod) % mod;
    return (s * s) % mod;
  }
  return (x * pow_mod(x, pow - 1, mod)) % mod;
}

int main()
{
  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++)
  {
    int h, w;
    scanf("%i %i", &w, &h);

    printf("%i\n", pow_mod(w + 1, h, 10000));
  }

  return 0;
}