#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000000
#define MAXOPS 100000

int main() {

    int Q;
    scanf("%d", &Q);

    char S[MAX] = "";
    
    // stack to store previous states
    char *stack[MAXOPS];
    int top = -1;

    for(int i = 0; i < Q; i++) {

        int type;
        scanf("%d", &type);

        if(type == 1) { // append

            char str[100000];
            scanf("%s", str);

            stack[++top] = strdup(S);  // save current state
            strcat(S, str);

        }
        else if(type == 2) { // delete

            int k;
            scanf("%d", &k);

            stack[++top] = strdup(S);  // save current state
            int len = strlen(S);
            S[len - k] = '\0';

        }
        else if(type == 3) { // print

            int k;
            scanf("%d", &k);
            printf("%c\n", S[k - 1]);

        }
        else if(type == 4) { // undo

            if(top >= 0) {
                strcpy(S, stack[top]);
                free(stack[top]);
                top--;
            }

        }
    }

    return 0;
}
