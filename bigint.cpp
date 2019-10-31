#include <iostream>
#define LOG(x) std::cout << x << std::endl

int num_of_char(char c)
{
  return c - '0';
}

void logg(void *x)
{
  std::cout << x;
}

void normalizeSize(std::string &str, int dist)
{
  int len = str.size();
  int diff = dist - len;

  // Just to speed things up;
  if (diff > 0)
  {
    std::string margin = "";
    for (int i = 0; i < diff; i++)
      margin += '0';

    str = margin + str;
  }
}

bool oper(std::string &op, char a, char b)
{
  int na = num_of_char(a),
      nb = num_of_char(b);
      
  if (op == "==")
    return na == nb;
  else if (op == "!=")
    return na != nb;
  else if (op == ">=")
    return na >= nb;
  else if (op == ">")
    return na > nb;
  else if (op == "<=")
    return na <= nb;
  else if (op == "<")
    return na < nb;
}

bool isSimple(std::string &op)
{
  return op == "==" || op == "!=";
}

int main()
{
  std::string a, op, b;

  std::cin >> a >> op >> b;
  int as = a.size(),
      bs = b.size(),
      sz = as;

  // -------- Normalize the input -------- //
  if (as > bs)
    normalizeSize(b, as);
  else if (bs > as)
  {
    sz = bs;
    normalizeSize(a, bs);
  }

  // -------- Compare -------- //
  bool match = true;
  if (isSimple(op))
  {
    if (op == "==")
      match = a == b;
    else
      match = a != b;
  }
  // Skip the margin
  else
  {
    int i = 0;
    while (i < sz && a[i] == b[i])
      i++;
    match = oper(op, a[i], b[i]);
  }

  LOG((match ? "TAK" : "NIE"));

  return 0;
}