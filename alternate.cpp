#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int len, b;
  std::cin >> len;

  int log[len / 2];
  for (int i = 0; i < len; i++)
  {
    std::cin >> b;
    if (i % 2 == 1)
      log[(i - 1) / 2] = b;
    else
      std::cout << " " << b;
  }
  std::cout << std::endl;

  for (int i = 0; i < len / 2; i++)
    std::cout << " " << log[i];
  std::cout << std::endl;
  return 0;
}