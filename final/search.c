#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readInt() {
    int tem;
    scanf("%d",&tem);
    return tem;
}

const int INF = 0x3f3f3f3f;

typedef struct node  node;
typedef struct node* nptr;

struct node {
    int v;
    int weight;
    nptr next;
};
nptr head[100005];      // 邻接表数组
int from[100005];   // 每个点被谁更新
int dis[100005];     // 每个点的最短距离
int vis[100005];     // 每个点是否被访问
int road[100005];    // 记录从起点到终点的路径

nptr newnode() { return (nptr)malloc(sizeof(node)); }
nptr getnode(int v, int weight) {
    nptr p = newnode();
    p -> v = v;
    p -> weight = weight;
    p -> next = NULL;
    return p;
}

void addedge(int u, int v, int weight) {
    nptr p = getnode(v, weight);
    p -> next = head[u];
    head[u] = p;
}

int v[205], type[100000][10], typenum[100000] = {0};

struct ans {
	int end;
	int dis;
};
struct ans a[205];
int cmp(const void *p1, const void *p2) {
	struct ans *d1 = (struct ans *)p1;
    struct ans *d2 = (struct ans *)p2; 
    if(d1->dis < d2->dis) return -1;
    else if(d1->dis > d2->dis) return 1;
    return 0;
}

int main() {
    int n = readInt();
	for(int i = 1; i <= n; i++) {
		int ver;
		scanf("%d", &ver);
		v[i] = ver;
		for(int j = 1; j <= 9; j++) {
			int a;
			scanf("%d", &a);
			if(a == -1) break;
			type[ver][j] = a;
			typenum[ver]++;
		}
	}

    while(1) {
        int u = readInt(), v = readInt(), weight = readInt();
        if(u == -1 && v == -1 && weight == -1) break;
        addedge(u, v, weight);
    }
	int sta = readInt();
	
    for(int i = 1; i <= n ;i++)
        if(v[i] != sta)
            dis[v[i]] = INF;

    for(int i = 1; i <= n ;i++) {
        int tem = -1, minDis = INF;
        for(int j = 1; j <= n ;j++)
            if(!vis[v[j]] && dis[v[j]] < minDis)
                minDis = dis[v[j]], tem = v[j];
        
        vis[tem] = 1;
        for(nptr p = head[tem]; p ; p = p -> next)
            if(!vis[p -> v] && p -> weight + dis[tem] < dis[p -> v])
                dis[p -> v] = p -> weight + dis[tem], from[p -> v] = tem;
    }
	int typ = readInt();
	int ans[205], idx = 0;
	for(int i = 1; i <= n; i++) {//v
		for(int j = 1; j <= typenum[v[i]]; j++) {//idx
			if(type[v[i]][j] == typ) {
				int end = v[i];
				a[idx].end = end;
				a[idx].dis = dis[end];
				idx++;
			}
		}
	}
	qsort(a, idx, sizeof(struct ans), cmp);
	for(int i = 0; i < idx; i++) {
		printf("%d %d", a[i].end, a[i].dis);
				if(a[i].dis == 0) {
					printf("\n");
				} else {
					printf(" ");
					int tem = a[i].end, cnt = 0;
    				while(tem) {
        				road[++cnt] = tem;
        				tem = from[tem];
    				}

    				for(int k = cnt; k > 1 ;k--)
        				printf("%d-", road[k]);
					printf("%d\n", road[1]);
				}
	}
    return 0;
}