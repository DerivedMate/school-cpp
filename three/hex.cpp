#include <iostream>
#include <cstring>
#include <math.h>
#define LOGE(x) std::cout << x << std::endl

int main()
{
  const int LEN = 2;
  char input[LEN];

  std::cin >> input;

  int i = LEN - 1;
  int acc = 0;
  for (char c : input)
  {
    int x;
    if (c >= 65 && c <= 70)
      x = int(c - 'A') + 10;
    else if (c >= 48 && c <= 57)
      x = c - 48;
    else
      throw "Hex out of range";

    acc += x * pow(16, i--);
  }

  LOGE(acc);
  LOGE((char)acc);

  return 0;
}