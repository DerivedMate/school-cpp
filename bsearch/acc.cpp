#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#define LOGE(x) std::cout << x << std::endl

void aggrInput(int n, int *acc)
{
  for (int i = 0; i < n; i++)
    std::cin >> acc[i];
}

std::map<int, int> bsDict;

int bsrec(int *arr, int len, int x, int s, int e)
{
  auto entry = bsDict.find(x);
  if (entry != bsDict.end())
  {
    return entry->second;
  }
  int i = (s + e + 1) / 2;

  if (arr[i] == x) {
    bsDict[x] = i;
    return i;
  }
  else if (s >= e) {
    bsDict[x] = 0;
    return 0;
  }
  else if (x >= arr[i])
    return bsrec(arr, len, x, i, e);
  else if (x < arr[i])
    return bsrec(arr, len, x, s, i - 1);
}

int bsearch(int *arr, int len, int x, int start)
{
  auto entry = bsDict.find(x);
  if (entry != bsDict.end())
  {
    return entry->second;
  }
  int s = start;
  int e = len - 1;
  int i;

  do
  {
    i = (s + e + 1) / 2;

    if (x >= arr[i])
    {
      s = i;
    }
    else
    {
      e = i - 1;
    }
  } while (arr[i] != x && s < e);

  bsDict[x] = i;

  return i;
}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  int n, q;

  std::cin >> n;
  int entries[n];
  aggrInput(n, entries);

  std::cin >> q;
  int questions[q];
  aggrInput(q, questions);

  auto end = std::chrono::high_resolution_clock::now();
  LOGE((end - start).count());
  LOGE("n: " << n);
  LOGE("q: " << q);

  for (int i = 0; i < q; i++)
  {
    auto start = std::chrono::high_resolution_clock::now();

    int anIndex = bsrec(entries, n, questions[i], 0, n - 1);
    int qst = questions[i];
    int k = anIndex;
    int j = anIndex + 1;
    int n = 0;

    while (entries[k] == qst && k >= 0)
    {
      n++;
      k--;
    }

    while (entries[j] == qst && j <= n)
    {
      n++;
      j++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    LOGE((end - start).count());

    LOGE(n);
  }

  return 0;
}