#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct node {
	char word[100];
	int count;
	struct node *link;
};
struct node *head = NULL;

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

int insertWord(struct node *p, char *w) {//after p
	struct node *q;
	q = (struct node *)malloc(sizeof(struct node));
	if(q == NULL) return -1;
	strcpy(q->word, w);
	q->count = 1;
	q->link = NULL;
	if(head == NULL) {
		head = q;
	} else if(p == NULL) {
		q->link = head;
		head = q;
	} else {
		q->link = p->link;
		p->link = q;
	}
	return 0;
}

int searchWord(char *w) {
	struct node *p, *q = NULL;
	for(p = head; p != NULL; q = p, p = p->link) {
		if(strcmp(w, p->word) < 0) break;
		else if(strcmp(w, p->word) == 0) {//found
			p->count++;
			return 0;
		}
	}
	return insertWord(q, w);
}

int main()
{
	FILE *in = fopen("article.txt", "r");
	char text[100];
	while(getWord(in, text) != EOF) {
		if(searchWord(text) ==-1)	return -1;
	}
	
	struct node *p;
	for(p = head; p != NULL; p = p->link)
		printf("%s %d\n", p->word, p->count);
	fclose(in);
    return 0;
}
