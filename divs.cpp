#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int a, b, k;

  std::cin >> a >> b >> k;
  if (k > b || a > b)
    LOG(0);
  else
  {
    int m = a % k;
    int n = b % k;

    a = a + m;
    b = b - n;

    LOG((b - a) / k + 1);
  }

  return 0;
}

/*
      
    */