#include <iostream>
#define LOG(x) std::cout << x << std::endl

int main()
{
  int n, buff;
  int grades[] = {0, 0, 0, 0, 0, 0};
  std::cin >> n;

  for (int i = 0; i < n && std::cin >> buff; i++)
    grades[buff - 1]++;

  for (int g : grades)
  {
    std::cout << " " << g;
  }
  std::cout << std::endl;
  
  return 0;
}