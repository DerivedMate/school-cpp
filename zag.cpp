#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>

#define ll long long

ll f(ll p, ll x)
{
  return x*x*x + x * p;
}

ll bsrec(ll p, ll x, ll s, ll e)
{
  ll i = (s + e) / 2;
  ll y = f(p, i);

  if (y == x)
  {
    // bsDict[x] = i;
    return i;
  }
  else if (s >= e)
  {
    // bsDict[x] = -1;
    return -1;
  }
  else if (x >= y)
    return bsrec(p, x, i + 1, e);
  else if (x < y)
    return bsrec(p, x, s, i - 1);
}

int main()
{
  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++)
  {
    ll p, q, ind;

    std::cin >> p >> q;
    ll s = 0, e = std::cbrt(q);
    if (f(p, 0) == q)
      ind = s;
    else if (f(p, e) == q)
      ind = e;
    else 
      ind = bsrec(p, q, 0, std::cbrt(q));

    if (ind == -1)
      std::cout << "NIE" << std::endl;
    else
      std::cout << ind << std::endl;
  }

  return 0;
}