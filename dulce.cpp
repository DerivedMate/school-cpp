#include <iostream>
#include <cstdlib>

int eat(int* arr, int n, int n_types, int bound_a, int bound_b) {
  int type_count[n_types];
  for(int i = 0; i < n_types-1; i++)
    type_count[i] = 0;

  for(int i = bound_a; i < bound_b; i++) {
    if(type_count[arr[i] - 1] > 1)
      return 0;

    type_count[arr[i] - 1] += 1;
  }

  return 1;
}

int main() {
  int n, n_types, count = 0;
  std::scanf("%i %i", &n, &n_types);

  int dulce[n];
  for(int i = 0; i < n; i++)
    std::scanf("%i", &dulce[i]);
  
  for(int sz = 0; sz < n; sz++) {
    for(int a = 0; a+sz < n; a++)
      count += eat(dulce, n, n_types, a, a+sz);
  }

  std::printf("%i\n", count);

  return 0;
}