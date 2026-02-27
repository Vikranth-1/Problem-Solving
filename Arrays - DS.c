#include <stdio.h>
#include <stdlib.h>

int* reverseArray(int a_count, int* a, int* result_count) {
    int* reversed = (int*)malloc(a_count * sizeof(int));
    for (int i = 0; i < a_count; i++) {
        reversed[i] = a[a_count - 1 - i];
    }
    *result_count = a_count;
    return reversed;
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result_count;
    int* result = reverseArray(n, arr, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d ", result[i]);
    }

    free(arr);
    free(result);
    return 0;
}
