#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct tree{
	int id;
	struct tree *left, *mid, *right;
};
struct tree root[205];

struct gate{
	int id;
	int num;
};

void insert(struct tree root[], int r, int s1, int s2, int s3) {
    root[r].id = r;
	if(s2 == -1) {//mid
		root[s1].id = s1;
		root[r].left = NULL;
		root[r].mid = &(root[s1]);
		root[r].right = NULL;
	} else if(s3 == -1) {//left&right
		root[s1].id = s1;
		root[s2].id = s2;
		root[r].left = &(root[s1]);
		root[r].mid = NULL;
		root[r].right = &(root[s2]);
	} else {//all
		root[s1].id = s1;
		root[s2].id = s2;
		root[s3].id = s3;
		root[r].left = &(root[s1]);
		root[r].mid = &(root[s2]);
		root[r].right = &(root[s3]);
	}
}

int cmp(const void *p1, const void *p2) {
	struct gate *d1 = (struct gate *)p1;
    struct gate *d2 = (struct gate *)p2; 
    if(d1->num > d2->num) return 1;
    else if(d1->num < d2->num) return -1;
    else {
    	if(d1->id > d2->id) return -1;
    	else if(d1->id < d2->id) return 1;
	}
	return 0;
}
int ans[105];
void order(struct tree *root) 
{
	int index = 0;
	if(root->left == NULL && root->right == NULL) order(root->mid);
	else if(root->mid == NULL) {
		if((root->left->id) < 100 && (root->right->id) < 100) {
			ans[index++] = root->left;
			ans[index++] = root->right;
			return;
		} else if((root->left->id) < 100 && (root->right->id) > 100) {
			ans[index++] = root->left;
			order(root->right);
		} else if ((root->left->id) > 100 && (root->right->id) < 100) {
			ans[index++] = root->right;
			order(root->left);
		} else {
			order(root->left);
			order(root->right);
		}
	} else {
		if((root->mid->id) > 100 && (root->left->id) < 100 && (root->right->id) < 100) {
			ans[index++] = root->left;
			ans[index++] = root->right;
			order(root->mid);
		} else if((root->mid->id) < 100 && (root->left->id) < 100 && (root->right->id) < 100){
			ans[index++] = root->left;
			ans[index++] = root->mid;
			ans[index++] = root->right;
			return;
		} else {
			order(root->left);
			order(root->mid);
			order(root->right);
		}
	}  
}

int main()
{
	char input[50];
    while(fgets(input, 50, stdin) != NULL){
        int len = strlen(input);
        if(len == 2)//'-1'
            break;
        input[strcspn(input, "\n")] = '\0';
        int r, s1, s2, s3;
        sscanf(input, "%d %d %d %d", &r, &s1, &s2, &s3);
        insert(root, r, s1, s2, s3);
    }
	struct gate a[105];
	int id, num, index = 0;
	while(scanf("%d %d", &id, &num) != EOF) {
		a[index].id = id;
		a[index].num = num;
		index++;
	}
	qsort(a, index, sizeof(struct gate), cmp);
	
	order(&root[100]);
	for(int i = 0; i < index; i++) {
		printf("%d->%d", a[i].id, ans[i]);
	}
    return 0;
}
