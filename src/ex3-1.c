/*
 * Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with only one
 * test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* not found */
}

/* binsearch2: same as above, 1 test less in the loop */
int binsearch2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while (low <= high) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low+high) / 2;
    }
    return x == v[mid] ? mid : -1;
}

/*
 * performance test
 * I am using more stuff than what was introduced at this point of the book
 * fully knowing that this is just a test anyway.
 * I also know that rand() sucks and rand() % N sucks even more. But this
 * is just a small test.
 */

#define N 100000000

int arr[N];

int main(void)
{
    clock_t t1, t2;
    int i, n, r;

    srand(time(NULL));
    n = 0;
    for (i = 0; i < N; i++) {
        arr[i] = n;
        n += rand() % 100;
    }

    t1 = clock();
    r = binsearch(1000, arr, N);
    t2 = clock();
    printf("%d\n", t2 - t1);

    t1 = clock();
    r = binsearch2(1000, arr, N);
    t2 = clock();
    printf("%d\n", t2 - t1);

    return 0;
}
