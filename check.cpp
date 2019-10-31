#include <iostream>
#include <string>
using namespace std;

int main()
{
  int szyfr, k, x;
  cin >> szyfr;
  cin >> k;
  string alfabet = "abcdefghijklmnopqrstuvwxyz";
  string napis;
  cin >> napis;
  x = napis.size();
  if (szyfr == 1)
  {
    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < 27; j++)
      {
        char a = alfabet[j], b = napis[i];
        if (alfabet[j] == napis[i] && j + k > 26)
        {
          napis[i] = alfabet[k - 1];
          break;
        }
        else if (alfabet[j] == napis[i] && j + k < 27)
        {
          napis[i] = alfabet[j + k - 1];
          break;
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < 27; j++)
      {
        if (alfabet[j] == napis[i] && j - k < 0)
          napis[i] = alfabet[k - 1];
        else if (alfabet[j] == napis[i] && j - k >= 0)
          napis[i] = alfabet[j - k];
      }
    }
  }

  cout << napis;
}