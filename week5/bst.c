#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct tree {
	int num;
	struct tree *left, *right;
};

struct tree* create(int data) {
    struct tree* newNode = (struct tree*)malloc(sizeof(struct tree));
    newNode->num = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct tree* insert(struct tree* root, int data) {
    if(root == NULL) {
        root = create(data);
    } else {
        if(data < root->num) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
    }
    return root;
}

void order(struct tree* root, int h) 
{
	if(root == NULL) return;
	if(root -> left == NULL && root -> right == NULL) {
		printf("%d %d\n", root->num, h);
		return;
	}
	order(root->left, h+1);
	order(root->right, h+1);
}

int main()
{
	int n;
	scanf("%d", &n);
	int *a = (int *)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	struct tree *root = (struct tree*)malloc(sizeof(struct tree));
	root = NULL;
	for(int i = 0; i < n; i++) {
		root = insert(root, a[i]);
	}
	order(root, 1);
    return 0;
}
