#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define str std::string
#define LOG(x) std::cout << x << std::endl

int diff(str a, str b)
{
  if (b > a)
    std::swap(a, b);

  int out = 0;
  int n = b.size();
  for(int i = 0; i < n; i++) 
    out += (a[i] - b[i]) * (int)pow(10.0, float(n - i - 1));

  return out;
}

int main()
{

  str a = "0555", b = "0551";
  LOG(diff(a, b));
}