#include <iostream>
#define LOG(x) std::cout << x << std::endl

const int ALPH_LEN = 26;

int whatLetter(char c)
{
  // -------- Is a capital letter -------- //
  if (c >= 'A' && c <= 'Z')
    return 1;

  // -------- Is a lower-case letter -------- //
  else if (c >= 'a' && c <= 'z')
    return 2;

  // -------- Isn't a letter -------- //
  else
    return 0;
}

int main()
{
  int c_dc, k;
  std::string input;
  std::cin >> c_dc >> k >> input;

  for (char &c : input)
  {
    int kindOfLetter = whatLetter(c);
    // -------- If is a letter -------- //
    if (kindOfLetter != 0)
    {
      int base = (kindOfLetter == 1 ? 'A' : 'a');
      // -------- Encode -------- //
      if (c_dc == 1)
      {
        c = base + ((c - base + k) % ALPH_LEN);
      }

      // -------- Decode -------- //
      else
      {
        int x = (c - base - k) % ALPH_LEN;
        if (x < 0)
          x += ALPH_LEN;
        c = base + (x);
      }
    }
  }

  LOG(input);

  return 0;
}