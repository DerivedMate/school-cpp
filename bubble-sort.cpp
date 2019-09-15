#include <iostream>
#include <ostream>
#define LOG(x) std::cout << x << std::endl

void swap(int* arr, int a, int b) {
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int* bsort(int* arr, int len) {
  bool unswapped = false;
  while(!unswapped) {
    unswapped = true;

    for (int i = 0; i < len - 1; i++) {
      if(arr[i] > arr[i+1]) {
        swap(arr, i, i + 1);
        unswapped = false;
      }
    }
  }

  return arr;
}

int main() {
  const int N = 5;
  int x[N] = {3, 2, 4, 5, 1};

  bsort(x, N);

  for(int i = 0; i < N; i++) {
    LOG(x[i]);
  }
  
  std::cin.get();
  return 0;
}
