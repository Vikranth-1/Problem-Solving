#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void topView(struct node *root) {

    if (root == NULL)
        return;

    // Queue for BFS
    struct node* queue[MAX];
    int hd[MAX];  // store horizontal distances
    int front = 0, rear = 0;

    // Array to store top view nodes
    int top[MAX];
    int visited[MAX] = {0};

    int offset = MAX / 2;  // shift for negative HD

    // Initialize
    queue[rear] = root;
    hd[rear] = 0;
    rear++;

    while (front < rear) {

        struct node* current = queue[front];
        int curr_hd = hd[front];
        front++;

        // If this HD is not yet visited
        if (!visited[curr_hd + offset]) {
            top[curr_hd + offset] = current->data;
            visited[curr_hd + offset] = 1;
        }

        // Push left child
        if (current->left) {
            queue[rear] = current->left;
            hd[rear] = curr_hd - 1;
            rear++;
        }

        // Push right child
        if (current->right) {
            queue[rear] = current->right;
            hd[rear] = curr_hd + 1;
            rear++;
        }
    }

    // Print top view from leftmost to rightmost
    for (int i = 0; i < MAX; i++) {
        if (visited[i]) {
            printf("%d ", top[i]);
        }
    }
}

int main() {
  
    struct node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	topView(root);
    return 0;
}
