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
    int n = 0;
    for (int i = a; i <= b;)
    {
      int m = i % k;
      if (m == 0)
      {
        n += (b - i) / k + 1;
        break;
      }
      i += k - m;
    }

    LOG(n);
  }

  return 0;
}

/*
      
    */