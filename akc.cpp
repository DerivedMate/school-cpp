#include <iostream>
#include <cmath>
#define LOGE(x) std::cout << x << std::endl

const void aggrInput(const int n, int *acc)
{
  for (int i = 0; i < n; i++)
    scanf("%i", &acc[i]);
}

int bsrec(const int *arr, int x, int s, int e)
{
  int i = (s + e) / 2;

  if (arr[i] == x)
    return i;
  else if (s >= e)
    return -1;

  else if (x > arr[i])
    return bsrec(arr, x, i + 1, e);
  else
    return bsrec(arr, x, s, i - 1);
}

int bsloop(int arr[], int x, int s, int e)
{
  while (true)
  {
    int i = (s + e) / 2;

    if (arr[i] == x)
      return i;
    else if (s >= e)
      return -1;

    else if (x > arr[i])
      s = i + 1;
    else
      e = i - 1;
  }
}

int main()
{
  int n, q;

  std::cin >> n;
  int entries[n];
  aggrInput(n, entries);

  std::cin >> q;
  int questions[q];
  aggrInput(q, questions);
  int last_i_a = -1, last_i_b = -1;
  int lastQ = -1;

  for (int i = 0; i < q; i++)
  {
    int qst = questions[i];
    int anIndex;

    if (qst < entries[0] || qst > entries[n - 1])
      anIndex = -1;
    else if (last_i_a == -1)
      anIndex = bsrec(entries, qst, 0, n - 1);

    else if (qst > lastQ)
      anIndex = bsrec(entries, qst, last_i_b, n - 1);
    else
      anIndex = bsrec(entries, qst, 0, last_i_a);

    int k = anIndex;
    int j = anIndex + 1;
    int count = 0;

    if (k == -1)
      count = 0;
    else
    {
      int skip = std::min(300.0, std::sqrt((double)n) + 1);
      while (k >= 0 && entries[k] == qst)
        k -= skip;

      k = std::max(k, 0);
      while (entries[k] != qst)
        k++;
      // "k" is now the left most occurrence index

      while (j < n && entries[j] == qst)
        j += skip;

      j = std::min(j, n - 1);
      while (entries[j] != qst)
        j--;
      // "j" is now the right most occurrence index

      last_i_a = k;
      last_i_b = j;
      lastQ = qst;

      count = j - k + 1;
    }

    printf("%i\n", count);
  }

  return 0;
}