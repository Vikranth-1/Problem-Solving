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
int parse_int(char*);

/* -------- Helper Functions -------- */

void inorder(int node, int* left, int* right, int* res, int* idx){
    if(node == -1) return;

    inorder(left[node], left, right, res, idx);
    res[(*idx)++] = node;
    inorder(right[node], left, right, res, idx);
}

void swapDepth(int node, int depth, int k, int* left, int* right){
    if(node == -1) return;

    if(depth % k == 0){
        int temp = left[node];
        left[node] = right[node];
        right[node] = temp;
    }

    swapDepth(left[node], depth+1, k, left, right);
    swapDepth(right[node], depth+1, k, left, right);
}

/* -------- Required Function -------- */

int** swapNodes(int indexes_rows, int indexes_columns, int** indexes, int queries_count, int* queries, int* result_rows, int* result_columns) {

    int n = indexes_rows;

    int left[1025], right[1025];

    for(int i=1;i<=n;i++){
        left[i] = indexes[i-1][0];
        right[i] = indexes[i-1][1];
    }

    *result_rows = queries_count;
    *result_columns = n;

    int** result = malloc(queries_count * sizeof(int*));

    for(int i=0;i<queries_count;i++){

        result[i] = malloc(n * sizeof(int));

        int k = queries[i];

        swapDepth(1,1,k,left,right);

        int idx = 0;
        inorder(1,left,right,result[i],&idx);
    }

    return result;
}

/* -------- Main Function -------- */

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int** indexes = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(indexes + i) = malloc(2 * sizeof(int));

        char** indexes_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int indexes_item = parse_int(*(indexes_item_temp + j));
            *(*(indexes + i) + j) = indexes_item;
        }
    }

    int queries_count = parse_int(ltrim(rtrim(readline())));

    int* queries = malloc(queries_count * sizeof(int));

    for (int i = 0; i < queries_count; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));
        *(queries + i) = queries_item;
    }

    int result_rows;
    int result_columns;

    int** result = swapNodes(n, 2, indexes, queries_count, queries, &result_rows, &result_columns);

    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            fprintf(fptr, "%d", result[i][j]);

            if (j != result_columns - 1) {
                fprintf(fptr, " ");
            }
        }

        if (i != result_rows - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

/* -------- Input Helper Functions -------- */

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
            break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return NULL;
    while (*str && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return NULL;

    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;

    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
