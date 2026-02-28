#include <stdio.h>
#include <stdlib.h>

int main() {
    long n, q;
    scanf("%ld %ld", &n, &q);

    // Use long to avoid overflow
    long *arr = calloc(n + 2, sizeof(long));

    for(long i = 0; i < q; i++) {
        long a, b, k;
        scanf("%ld %ld %ld", &a, &b, &k);

        arr[a] += k;
        if(b + 1 <= n)
            arr[b + 1] -= k;
    }

    long max = 0;
    long current = 0;

    // Build prefix sum and track maximum
    for(long i = 1; i <= n; i++) {
        current += arr[i];
        if(current > max)
            max = current;
    }

    printf("%ld\n", max);

    free(arr);
    return 0;
}