#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int n, x, a = -2, b = -2, buff;
  std::cin >> n >> x;

  for (int i = 0; i < n && std::cin >> buff; i++)
    if (buff == x && a == -2)
    {
      a = i;
      b = i;
    }
    else if (buff == x)
      b = i;

  LOG(a + 1 << " " << b + 1);

  return 0;
}