#include <stdio.h>
#include <stdlib.h>

int* dynamicArray(int n, int q, int queries[][3], int* result_count) {
    int** arr = (int**)malloc(n * sizeof(int*));
    int* sizes = (int*)calloc(n, sizeof(int));
    int* capacities = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        arr[i] = NULL;
    }
    
    int lastAnswer = 0;
    int* results = (int*)malloc(q * sizeof(int));
    int resIndex = 0;
    
    for (int i = 0; i < q; i++) {
        int type = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];
        
        int idx = (x ^ lastAnswer) % n;
        
        if (type == 1) {
            if (sizes[idx] == capacities[idx]) {
                capacities[idx] = capacities[idx] == 0 ? 1 : capacities[idx] * 2;
                arr[idx] = (int*)realloc(arr[idx], capacities[idx] * sizeof(int));
            }
            arr[idx][sizes[idx]++] = y;
        } else if (type == 2) {
            lastAnswer = arr[idx][y % sizes[idx]];
            results[resIndex++] = lastAnswer;
        }
    }
    
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    free(sizes);
    free(capacities);
    
    *result_count = resIndex;
    return results;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    int queries[q][3];
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i][0], &queries[i][1], &queries[i][2]);
    }
    
    int result_count;
    int* results = dynamicArray(n, q, queries, &result_count);
    
    for (int i = 0; i < result_count; i++) {
        printf("%d\n", results[i]);
    }
    
    free(results);
    return 0;
}
