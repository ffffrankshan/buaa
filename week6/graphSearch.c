#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct 
{
    int vertices;
    int edges;
    int adj[MAX_VERTICES][MAX_VERTICES];
}graph;

void dfs(graph *graph, int start, int visited[])
{
    visited[start] = 1;
    printf("%d ", start);
    for(int i = 0; i < graph->vertices; ++i) {
        if(graph->adj[start][i] == 1 && !visited[i]) {
            dfs(graph, i, visited);
        }
    }
}

void bfs(graph *graph, int start, int visited[])
{
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    while(front < rear) {
        int x = queue[front++];
        printf("%d ",x);
        for(int i = 0; i < graph->vertices; ++i) {
            if(graph->adj[x][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    graph graph;
    scanf("%d %d", &graph.vertices, &graph.edges);
    for(int i = 0; i < graph.vertices; ++i) { 
        for(int j = 0; j < graph.vertices; ++j) {
            graph.adj[i][j] = 0;
        }
    }
    for(int i = 0; i < graph.edges; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph.adj[u][v] = 1;
        graph.adj[v][u] = 1;
    }

    /*int visited1[MAX_VERTICES] = {0};
    dfs(&graph, 0, visited1);
    printf("\n");*/
    int visited2[MAX_VERTICES] = {0};
    bfs(&graph, 2, visited2);
    printf("\n");

    /*int remove;
    scanf("%d", &remove);
    for(int i = 0; i < graph.vertices; ++i) {
        graph.adj[remove][i] = 0;
        graph.adj[i][remove] = 0;
    }

    int visited3[MAX_VERTICES] = {0};
    dfs(&graph, 0, visited3);
    printf("\n");
    int visited4[MAX_VERTICES] = {0};
    bfs(&graph, 0, visited4);*/
    return 0;
}