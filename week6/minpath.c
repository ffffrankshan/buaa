#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct edge {
	int id;
	int weight;
};
struct edge Graph[1000][1000] = {0};

void prim(struct edge graph[][1000], int edges[], int n, int src)
{
	int minweight[1000] = {0};
	int min, num = 0;
	for(int i = 0; i < n; i++) {
		minweight[i] = graph[src][i].weight;
		edges[i] = src;
	}
	minweight[src] = 0;
	for(int i = 1; i < n; i++) {
		min = 0x7fffffff;
		int k = 0;
		for(int j = 0; j < n; j++) {
			if(minweight[j] != 0 && minweight[j] < min) {
				min = minweight[j];
				k = j;
			}
		}
		minweight[k] = 0;
		for(int j = 0; j < n; j++) {
			if(minweight[j] != 0 && graph[k][j].weight < minweight[j]) {
				minweight[j] = graph[k][j].weight;
				edges[j] = k;
			}
		}
	}
}
int cmp(const void *px, const void *py) {
	return *(int *)px - *(int *)py;
}

int main()
{
	int n, en;
	scanf("%d%d", &n, &en);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			Graph[i][j].weight = 0x7fffffff;
		}
	}
	
	int id, vi, vj, weight, sum = 0;
	int edges[1000] = {0}, result[1000] = {0};
	for(int i = 0; i < en; i++) {
		scanf("%d%d%d%d", &id, &vi, &vj, &weight);
		Graph[vi][vj].weight = Graph[vj][vi].weight = weight;
		Graph[vi][vj].id = Graph[vj][vi].id = id;
	}
	
	prim(Graph, edges, n, 0);
	
	for(int i = 1; i < n; i++) {
		result[i-1] = Graph[i][edges[i]].id;
		sum += Graph[i][edges[i]].weight;
	}
	qsort(result, n-1, sizeof(int), cmp);
	printf("%d\n", sum);
	for(int i = 0; i < n-1; i++) printf("%d ", result[i]);
    return 0;
}
