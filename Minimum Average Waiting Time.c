#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

long parse_long(char*);  // FIX 6: use long parser instead of int

/* ---------- Heap Structure ---------- */

typedef struct {
    long arrival;
    long cook;
} Customer;

void swap(Customer *a, Customer *b) {
    Customer t = *a;
    *a = *b;
    *b = t;
}

void heapify_up(Customer heap[], int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].cook <= heap[index].cook)
            break;
        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

void heapify_down(Customer heap[], int size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].cook < heap[smallest].cook)
            smallest = left;

        if (right < size && heap[right].cook < heap[smallest].cook)
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

void insert(Customer heap[], int *size, Customer val) {
    heap[*size] = val;
    heapify_up(heap, *size);
    (*size)++;
}

Customer extract_min(Customer heap[], int *size) {
    Customer min = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify_down(heap, *size, 0);
    return min;
}

int cmpArrival(const void *a, const void *b) {
    Customer *c1 = (Customer*)a;
    Customer *c2 = (Customer*)b;
    if (c1->arrival > c2->arrival) return 1;
    if (c1->arrival < c2->arrival) return -1;
    return 0;
}

/*
 * Complete the 'minimumAverage' function below.
 */

// FIX 1: return type changed from int to long to prevent overflow
long minimumAverage(int customers_rows, int customers_columns, long** customers) {

    int n = customers_rows;

    Customer *arr = malloc(n * sizeof(Customer));

    for (int i = 0; i < n; i++) {
        arr[i].arrival = customers[i][0];
        arr[i].cook    = customers[i][1];
    }

    qsort(arr, n, sizeof(Customer), cmpArrival);

    Customer *heap = malloc(n * sizeof(Customer));
    int heapSize = 0;

    long currentTime = 0;
    long totalWait   = 0;

    int i = 0;

    while (i < n || heapSize > 0) {

        // FIX 2: added i < n guard before accessing arr[i] to prevent out-of-bounds read
        if (heapSize == 0 && i < n && currentTime < arr[i].arrival)
            currentTime = arr[i].arrival;

        while (i < n && arr[i].arrival <= currentTime) {
            insert(heap, &heapSize, arr[i]);
            i++;
        }

        Customer c = extract_min(heap, &heapSize);

        currentTime += c.cook;
        totalWait   += currentTime - c.arrival;
    }

    free(heap);
    free(arr);

    // FIX 4: return type is now long, no truncation
    return totalWait / n;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = (int)parse_long(ltrim(rtrim(readline())));

    // FIX 6: use long** so input values are stored as long end-to-end
    long** customers = malloc(n * sizeof(long*));

    for (int i = 0; i < n; i++) {
        customers[i] = malloc(2 * sizeof(long));

        char** customers_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            customers[i][j] = parse_long(customers_item_temp[j]);
        }

        free(customers_item_temp);  // free the split array each row
    }

    long result = minimumAverage(n, 2, customers);

    fprintf(fptr, "%ld\n", result);

    // FIX 3: free every row then the outer array - no more memory leak
    for (int i = 0; i < n; i++) free(customers[i]);
    free(customers);

    fclose(fptr);

    return 0;
}

/* ---------- Helper Functions ---------- */

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length  = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line   = fgets(cursor, alloc_length - data_length, stdin);

        if (!line)
            break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
            break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);

        if (!data)
            break;
    }

    // FIX 5: guard against data_length == 0 (EOF on first read) to avoid data[-1]
    if (data_length == 0) {
        free(data);
        return NULL;
    }

    if (data[data_length - 1] == '\n')
        data[data_length - 1] = '\0';

    return data;
}

char* ltrim(char* str) {
    while (*str && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char*  token  = strtok(str, " ");
    int    spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }

    return splits;
}

// FIX 6: parse_long replaces parse_int so large values aren't truncated on input
long parse_long(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0')
        exit(EXIT_FAILURE);

    return value;
}
