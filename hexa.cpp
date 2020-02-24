#include <iostream>

bool is_digit(char &c)
{
  return c >= '0' && c <= '9';
}

bool is_letter_lower(char &c)
{
  return c >= 'a' && c <= 'z';
}

bool is_letter_upper(char &c)
{
  return c >= 'A' && c <= 'Z';
}

int normalize_atom(char &c)
{
  if (is_digit(c))
    return c - '0';
  else if (is_letter_lower(c))
    return c - 'a' + 10;
  return c - 'A' + 10;
}

int dec_of_n(std::string &str, int n)
{
  int sum = 0;
  for (int i = 0; i < str.size(); i++)
    sum = sum * n + normalize_atom(str[i]);

  return sum;
}

int main()
{
  std::string buff;
  std::cin >> buff;

  std::cout << dec_of_n(buff, 16);
}