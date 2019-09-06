#include <iostream>
#define LOGE(x) std::cout << x << std::endl;

int* aggrInput(int n)
{
  int *acc = new int(n);

  std::cin >> *acc;

  return acc;
}

template <typename T>
void printAll(T *arr, int len)
{
  for (int i = 0; i < len; i++)
    LOGE(*arr[i])
}

int main()
{

  int* input = aggrInput(2);

  printAll(&input, 2);

  std::cin.get();
  return 0;
}