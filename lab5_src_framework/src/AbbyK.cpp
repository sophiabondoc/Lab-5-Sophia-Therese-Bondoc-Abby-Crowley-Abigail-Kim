// Abigail Kim
// Lab 5, ECE 2161-001
// Selection sort and quick sort implementations

#include "AbbyK.h"

// Swaps the values of x and y.
void swapValues(long& x, long& y) {
    long temp = x;
    x = y;
    y = temp;
}

// Selection Sort: sorts a[0..n-1] in increasing order. Each pass finds the
// smallest number in the unsorted part and swaps it into position.
void selectionSort(long a[], long n) {
    for (long i = 0; i < n - 1; i++) {
        long smallest = i;                 // index of smallest number found

        for (long j = i + 1; j < n; j++) {
            if (a[j] < a[smallest])
                smallest = j;
        }

        swapValues(a[i], a[smallest]);     // put the smallest number in position i
    }
}

// Quick Sort: sorts a[lo..hi] in increasing order. Picks the middle number
// as the pivot; smaller numbers go left and larger numbers go right.
void quickSort(long a[], long lo, long hi) {
    if (lo >= hi)                          // 0 or 1 elements are already sorted
        return;

    long pivot = a[(lo + hi) / 2];
    long i = lo;
    long j = hi;

    while (i <= j) {                       // swap pairs on opposite sides of pivot
        while (a[i] < pivot)               // skip numbers already on the left
            i++;
        while (a[j] > pivot)               // skip numbers already on the right
            j--;
        if (i <= j) {
            swapValues(a[i], a[j]);
            i++;
            j--;
        }
    }
    quickSort(a, lo, j);                   // sort the left part
    quickSort(a, i, hi);                   // sort the right part
}
