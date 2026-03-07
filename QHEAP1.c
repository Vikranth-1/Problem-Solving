#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int heap[MAX];
int size = 0;

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(int i){
    while(i > 0){
        int parent = (i - 1) / 2;
        if(heap[parent] > heap[i]){
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(int i){
    while(1){
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if(left < size && heap[left] < heap[smallest])
            smallest = left;

        if(right < size && heap[right] < heap[smallest])
            smallest = right;

        if(smallest != i){
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

void insert(int x){
    heap[size] = x;
    heapifyUp(size);
    size++;
}

void deleteValue(int x){
    int i;

    for(i = 0; i < size; i++){
        if(heap[i] == x)
            break;
    }

    heap[i] = heap[size - 1];
    size--;

    heapifyUp(i);
    heapifyDown(i);
}

int main() {

    int Q;
    scanf("%d", &Q);

    for(int i = 0; i < Q; i++){

        int type;
        scanf("%d", &type);

        if(type == 1){
            int x;
            scanf("%d", &x);
            insert(x);
        }

        else if(type == 2){
            int x;
            scanf("%d", &x);
            deleteValue(x);
        }

        else if(type == 3){
            printf("%d\n", heap[0]);
        }
    }

    return 0;
}
