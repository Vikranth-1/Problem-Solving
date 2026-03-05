#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

int main() {
    int n;
    scanf("%d", &n);

    int stack[MAX];
    int maxStack[MAX];
    int top = -1;
    int maxTop = -1;

    for(int i = 0; i < n; i++) {
        int type;
        scanf("%d", &type);

        if(type == 1) {
            int x;
            scanf("%d", &x);

            stack[++top] = x;

            if(maxTop == -1 || x >= maxStack[maxTop])
                maxStack[++maxTop] = x;

        } 
        else if(type == 2) {
            if(stack[top] == maxStack[maxTop])
                maxTop--;

            top--;
        } 
        else if(type == 3) {
            printf("%d\n", maxStack[maxTop]);
        }
    }

    return 0;
}
