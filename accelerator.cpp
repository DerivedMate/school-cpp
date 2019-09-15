#include <iostream>
// #include <chrono>
#include <map>
#define LOGE(x) std::cout << x << std::endl

void aggrInput(int n, int *acc)
{
  for (int i = 0; i < n; i++)
    std::cin >> acc[i];
}

std::map<int, int> bsDict;

int bsrec(int *arr, int x, int s, int e)
{
  // -------- Check the chache -------- //
  auto entry = bsDict.find(x);
  if (entry != bsDict.end())
  {
    return entry->second;
  }
  int i = (s + e + 1) / 2;

  // -------- Check the edges -------- //
  if (arr[s] == x)
    return s;
  else if (arr[e] == x)
    return e;
  else if (s >= e || x > arr[e] || x < arr[s])
  {
    bsDict[x] = -1;
    return -1;
  }

  // -------- The main search -------- //
  if (arr[i] == x)
  {
    bsDict[x] = i;
    return i;
  }
  else if (x >= arr[i])
    return bsrec(arr, x, i, e);
  else if (x < arr[i])
    return bsrec(arr, x, s, i - 1);
}

int main()
{
  int n, q;

  // -------- Get entries -------- //
  std::cin >> n;
  int entries[n];
  aggrInput(n, entries);

  // -------- Get questions -------- //
  std::cin >> q;
  int questions[q];
  aggrInput(q, questions);

  for (int i = 0; i < q; i++)
  {
    int anIndex = bsrec(entries, questions[i], 0, n - 1);
    int qst = questions[i];
    int k = anIndex;
    int j = anIndex + 1;
    int n = 0;

    // -------- Question out off range -------- //
    if (k == -1)
      n = 0;
    else
    {
      while (entries[k--] == qst)
        n++;

      while (entries[j++] == qst)
        n++;
    }

    LOGE(n);
  }

  return 0;
}