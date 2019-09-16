#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  std::string str;
  int n, rn;
  bool same = true;

  std::cin >> str;
  n = str.size();
  rn = n / 2;

  for (int i = 0; i < rn && same; i++)
    same = str[i] == str[n - i - 1];

  LOG((same ? "TAK" : "NIE"));
  return 0;
}