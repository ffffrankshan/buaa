#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct node {
	char word[100];
	int count;
	struct node *left, *right;
};
struct node *root = NULL;

int getWord(FILE *fp, char *w) {
	int c;
	while(!isalpha(c = fgetc(fp)))
		if(c == EOF) return c;
		else continue;
	do {
		*w++ = tolower(c);
	} while(isalpha(c = fgetc(fp)));
	*w = '\0';
	return 1;
}

struct node* insertWord(struct node *q, char *w) {
	if(q == NULL) {
		q = (struct node*)malloc(sizeof(struct node));
		strcpy(q->word, w);
		q->count = 1;
		q->left = q->right = NULL;
	} else if(strcmp(w, q->word) == 0) {
		q->count++;
	} else if(strcmp(w, q->word) < 0){
		q->left = insertWord(q->left, w);
	} else {
		q->right = insertWord(q->right, w);
	}
	return q;
}

void midorder(struct node* p) {
    if(p != NULL) {
    	midorder(p->left);
    	printf("%s %d\n", p->word, p->count);
    	midorder(p->right);
	}
}
    

int main()
{
	FILE *in = fopen("article.txt", "r");
	char text[100];
	while(getWord(in, text) != EOF) {
		root = insertWord(root, text);
	}

	struct node *p = root;
	int cnt = 0;
	while(p != NULL) {
		printf("%s", p->word);
		p = p->right;
		cnt++;
		if(cnt == 3) break;
		printf(" ");
	}
	printf("\n");
	midorder(root);
	
	fclose(in);
    return 0;
}
