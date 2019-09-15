#include <iostream>
#include <cmath>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int k, sum = 0, buff;
  std::cin >> k;

  for (int i = 0; i < k + 1 && std::cin >> buff; i++)
    sum += buff * (int)pow(2, i);

  LOG(sum + 1);

  return 0;
}