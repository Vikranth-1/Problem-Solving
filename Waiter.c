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

/* ---------- Sieve of Eratosthenes ---------- */

/* Numbers go up to 10^5, so we need at most the first q <= 1200 primes.
 * The 1200th prime is 9733, well under 10^5. Sieve up to 10000 to be safe. */
#define SIEVE_MAX 100000

int primes[SIEVE_MAX];
int prime_count = 0;

void build_sieve(int need) {
    bool composite[SIEVE_MAX + 1];
    memset(composite, false, sizeof(composite));
    for (int i = 2; i <= SIEVE_MAX && prime_count < need; i++) {
        if (!composite[i]) {
            primes[prime_count++] = i;
            for (long long j = (long long)i*i; j <= SIEVE_MAX; j += i)
                composite[j] = true;
        }
    }
}

/* ---------- waiter ---------- */

int* waiter(int number_count, int* number, int q, int* result_count) {
    int n = number_count;

    build_sieve(q);

    int* result = malloc(n * sizeof(int));
    int  ri = 0;

    /* Current working stack A (simulate as array, top = end) */
    int* A = malloc(n * sizeof(int));
    int  a_sz = 0;

    /* Push input onto A so that first element is at bottom, last at top */
    for (int i = 0; i < n; i++) A[a_sz++] = number[i];

    int* B = malloc(n * sizeof(int));  /* divisible pile   */
    int* C = malloc(n * sizeof(int));  /* non-divisible pile */

    for (int iter = 0; iter < q; iter++) {
        int p   = primes[iter];
        int b_sz = 0;
        int c_sz = 0;

        /* Process A from top to bottom (end to start) */
        for (int i = a_sz - 1; i >= 0; i--) {
            if (A[i] % p == 0)
                B[b_sz++] = A[i];
            else
                C[c_sz++] = A[i];
        }

        /* Append B (top to bottom) into result */
        for (int i = b_sz - 1; i >= 0; i--)
            result[ri++] = B[i];

        /* C becomes new A. C[c_sz-1] is the top (last pushed). */
        a_sz = 0;
        for (int i = 0; i < c_sz; i++)
            A[a_sz++] = C[i];
    }

    /* Remaining in A: append top to bottom */
    for (int i = a_sz - 1; i >= 0; i--)
        result[ri++] = A[i];

    free(A); free(B); free(C);

    *result_count = n;
    return result;
}

/* ---------- main ---------- */

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));
    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));
    free(first_multiple_input);

    char** number_temp = split_string(rtrim(readline()));
    int* number = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        number[i] = parse_int(*(number_temp + i));
    free(number_temp);

    int result_count;
    int* result = waiter(n, number, q, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));
        if (i != result_count - 1) fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    free(result);
    free(number);
    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);
    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) { data = '\0'; break; }
    }
    if (data_length == 0) { free(data); return NULL; }
    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) data = '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) data = '\0';
        else data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
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
        if (!splits) return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
