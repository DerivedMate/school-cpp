#include <iostream>

void fill(int *arr, int m, int n) 
{  
    for (int i = 0; i < m; i++) 
      for (int j = 0; j < n; j++) 
        *((arr+i*n) + j) = 0;
} 
  
int main() 
{ 
    int m, n;
    std::cin >> m >> n;
    int arr[m][n];
  
    fill((int *)arr, m, n); 
    return 0; 
} 