#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 2000
struct edge {
    int eno; 
    int adjvex;
    struct edge *next;
 };
struct ver {
    struct edge *link;
} ; 
struct ver Graph[MAXSIZE];
int Visited[MAXSIZE] = {0};
int Paths[MAXSIZE] = {0};
int Vnum;	        
int V0, V1; 
struct edge *insertEdge(struct edge *head, int avex, int eno)
{
    struct edge *e, *p;
    e =(struct edge *)malloc(sizeof(struct edge));
    e->eno = eno;
    e->adjvex = avex;
	e->next = NULL;
    if(head == NULL)  
	{ 
	    head = e; 
	    return head; 
	}
    for(p = head; p->next != NULL; p = p->next)
        ;
    p->next = e; 
    return head;
}
void printPath(int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", Paths[i]);
    printf("\n");
    return;
}
void eDFS(int v, int level)
{
    struct edge *p;
    if(v == V1) { 
		printPath(level); 
		return; 
	}
    for(p = Graph[v].link; p != NULL; p = p->next)  
        if(!Visited[p->adjvex]) {
			Paths[level] = p->eno;
			Visited[p->adjvex] = 1;
            eDFS(p->adjvex,level+1);
            Visited[p->adjvex] = 0;
        }
}

int main()
{
	int en, eno, v1, v2;
	scanf("%d %d", &Vnum, &en);
	for(int i = 0; i < en; i++) {
		scanf("%d %d %d", &eno, &v1, &v2);
		Graph[v1].link = insertEdge(Graph[v1].link, v2, eno);
		Graph[v2].link = insertEdge(Graph[v2].link, v1, eno);
	}
	V0 = 0; 
	V1 = Vnum-1;
	Visited[V0] = 1;
	eDFS(V0, 0);
	return 0;
}
