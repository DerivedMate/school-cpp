#include <iostream>
#define LOG(x) std::cout << x << std::endl

int nwd(int a, int b)
{
  int t = b;
  while (b > 1)
  {
    a = a % b;
    b = a;
  }

  return a;
}

int min(const int* xs) {
  
}

int main()
{
  int n;
  std::cin >> n;

  int xs[n], buff;
  for (int i = 0; i < n && std::cin >> buff; i++)
    xs[n] = buff;

  LOG(nwd(xs[0], xs[1]));

  return 0;
}