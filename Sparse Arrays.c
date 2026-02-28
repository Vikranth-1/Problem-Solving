#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    char stringList[n][101];

    for(int i = 0; i < n; i++) {
        scanf("%s", stringList[i]);
    }

    int q;
    scanf("%d", &q);

    char query[101];

    for(int i = 0; i < q; i++) {
        scanf("%s", query);

        int count = 0;

        for(int j = 0; j < n; j++) {
            if(strcmp(query, stringList[j]) == 0) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}