#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int n, div = false;
  std::cin >> n;
  for (int i = 2; i < n && !div; i++)
    div = n % i == 0;

  LOG((div ? "zlozona" : "pierwsza"));
  return 0;
}