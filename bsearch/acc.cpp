#include <iostream>
#define LOGE(x) std::cout << x << std::endl
#define String const char *

int *aggrInput(int n)
{
  int *acc = new int(n);
  int i = 0;
  while (i < n)
  {
    if (std::cin >> acc[i])
      i++;
  }

  return acc;
}

int *bsearch(int *arr, int len, int x)
{
  int s = arr[0];
  int e = arr[len - 1];
  int i = (s + e + 1) / 2;
}

template <typename T>
void printAll(T *arr, int len)
{
  for (int i = 0; i < len; i++)
    LOGE(arr[i]);
}

int main()
{
  int n, q;
  // -------- Read the length of entries -------- //
  LOGE("Enter the number of entries");
  std::cin >> n;

  // -------- Read the entries -------- //
  LOGE("Enter " << n << " entries");
  int *entries = aggrInput(n);

  // -------- Read the number of questions -------- //
  LOGE("Enter the number of questions");
  std::cin >> q;

  // -------- Read the questions -------- //
  LOGE("Enter " << q << " questions");
  int *questions = aggrInput(q);

  std::cin.get();
  return 0;
}