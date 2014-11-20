#include "algorithm.h"
#include <stdio.h>
void bubble_sort(int *iarr, int num) {
   int i, j, temp;
   for (i = 1; i < num; i++) {
      for (j = 0; j < num - 1; j++) {
         if (iarr[j] > iarr[j + 1]) {
            temp = iarr[j];
            iarr[j] = iarr[j + 1];
            iarr[j + 1] = temp;
         }
      }


   }
}

int comp (const int *i, const int *j) { return *i - *j; }

void quick_sort(int *m, int s) {
    qsort(m, s, sizeof (int), (int(*) (const void *, const void *)) comp);
}
