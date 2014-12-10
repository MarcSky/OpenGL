#include "algorithm.h"
#include <stdio.h>

void bubble_sort(int *iarr, int num) {
   int i, j, temp;
   for (i = 1; i < num - 1; i++) {
      for (j = 0; j < num - 1 - i ; j++) {
         if (iarr[j] > iarr[j + 1]) {
            temp = iarr[j];
            iarr[j] = iarr[j + 1];
            iarr[j + 1] = temp;
         }
      }
   }
}

void quick_sort(int * a, long N) {
  long i = 0, j = N;
  int temp, p;
  p = a[ N>>1 ];
  do {
    while ( a[i] < p ) i++;
    while ( a[j] > p ) j--;

    if (i <= j) {
      temp = a[i]; a[i] = a[j]; a[j] = temp;
      i++; j--;
    }
  } while ( i<=j );

  if ( j > 0 ) quick_sort(a, j);
  if ( N > i ) quick_sort(a+i, N-i);
}

void stupid_sort(int *arr, int elements) {
    int flag = 0;
    int i = 0;
    do { flag = 0; i = 0;
        while (i < elements - 1) {
            if (arr[i] > arr[i+1]) {
                int buf = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = buf;
                flag = 1;
                break;
            }
            i++;
        }
    }
    while(flag);
}


int dichotomy_search(int search, int *arr, int elements) {
    quick_sort(arr, elements);

    int imax = elements - 1;
    int imin = 0;
    while (imax >= imin)
    {
        int imid = imin + ((imax - imin) / 2);
        if (arr[imid] == search)
            return imid;
        else if (arr[imid] < search)
            imin = imid + 1;
        else
            imax = imid - 1;
    }
    return 0;
}

int direct_search(int search, int *arr, int elements) {
    for (int i = 0; i < elements; i++) {
        if (arr[i] == search) {
            return i;
        }
    }
    return 0;
}
