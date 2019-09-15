#include <iostream>
#define LOGE(x) std::cout << x << std::endl

int main()
{
  const int LEN = 9;
  char number[LEN];
  int year;

  std::cin >> number >> year;

  int lastNum = number[LEN - 1] - '0';

  LOGE((lastNum * 2 + 5) * 50 + 1764 - year);

  return 0;
}