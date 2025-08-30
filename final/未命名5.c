#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int readInt() {
    int tem;
    scanf("%d",&tem);
    return tem;
}
const int INF = 0x3f3f3f3f;
typedef struct
{
    int id;
    int type[10];
    int num;
} station;

typedef struct
{
    int weight;
} weight;

station BGvertexs[MAX_STATIONS];
weight BGweights[MAX_STATIONS][MAX_STATIONS];
int Vnum;
int add_vertex(station st)
{
    int i;
    for (i = 0; i < MAX_STATIONS; ++i)
    {
        if (BGvertexs[i].flag == 1)
        {
            if (strcmp(BGvertexs[i].name, st.name) == 0)
            {
                break;
            }
        }
        else if (BGvertexs[i].flag == 0)
        {
            strcpy(BGvertexs[i].name, st.name);
            BGvertexs[i].is_transfer = st.is_transfer;
            BGvertexs[i].flag = 1;
            Vnum++;
            break;
        }
    }
    return i;
}

void Dijkstra(int v0, int v1, int spath[])
{
    int i, j, v, minweight;
    char wfound[MAX_STATIONS] = {0}; // 用于标记从v0到相应顶点是否找到最短路径，0未找到，1找到
    int sweight[MAX_STATIONS];
    for (i = 0; i < Vnum; i++)
    {
        sweight[i] = BGweights[v0][i].weight == 0 ? INF : BGweights[v0][i].weight; // 初始化数组Sweight
        spath[i] = (BGweights[v0][i].weight == 0 ? -1 : v0); // 初始化数组spath
    }
    sweight[v0] = 0;
    wfound[v0] = 1;
    for (i = 0; i < Vnum - 1; i++)
    { // 迭代VNUM-1次
        minweight = INF;
        for (j = 0; j < Vnum; j++) // 找到未标记的最小权重值顶点
            if (!wfound[j] && (sweight[j] < minweight))
            {
                v = j;
                minweight = sweight[v];
            }
        wfound[v] = 1; // 标记该顶点为已找到最短路径
        if (v == v1)
            return;                // 找到(v0,v1)最短路径，返回
        for (j = 0; j < Vnum; j++) // 找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
            if (!wfound[j] && (BGweights[v][j].line_id > 0) && (minweight + BGweights[v][j].weight < sweight[j]))
            {
                sweight[j] = minweight + BGweights[v][j].weight;
                spath[j] = v; // 记录前驱顶点
            }
    }
}

void printPath(int v0, int v1, int spath[])
{

    char path[80] = {0}, buf[80];
    int board[80], bcount = 0, line = -1, sc = 0; // bcount为从v0到v1最短路径的乘坐站数，sc为乘坐某一线路的站数
    int i;
    do
    { // 获得乘坐站序列，该序列为倒的，即起始站在最后
        board[bcount++] = v1;
    } while ((v1 = spath[v1]) != v0);
    board[bcount++] = v0;
    line = BGweights[board[bcount - 1]][board[bcount - 2]].line_id;
    sprintf(buf, "%s-%d(", BGvertexs[board[bcount - 1]].name, line);
    strcpy(path, buf);
    sc = 1;
    for (i = bcount - 2; i > 0; i--, sc++)
        if (BGweights[board[i]][board[i - 1]].line_id != line)
        {
            line = BGweights[board[i]][board[i - 1]].line_id;
            sprintf(buf, "%d)-%s-%d(", sc, BGvertexs[board[i]].name, line);
            strcat(path, buf);
            sc = 0;
        }
    sprintf(buf, "%d)-%s\n", sc, BGvertexs[board[i]].name);
    strcat(path, buf);
    puts(path);
}

int main() {
    int n = readInt();
	for(int i = 0; i < n; i++) {
		scanf("%d", &BGvertexs[i].id);
		for(int j = 0; j < 10; j++) {
			int a;
			scanf("%d", &a);
			if(a == -1) break;
			BGvertexs[i].type[j] = a;
			BGvertexs[i].num++;
		}
	}

    while(1) {
        int u = readInt(), v = readInt(), weight = readInt();
        if(u == -1 && v == -1 && weight == -1) break;
        addedge(u, v, weight);
    }
	int sta = readInt();
	
    for(int i = 1; i <= n ;i++)
        if(i != sta)
            dis[i] = INF;

    for(int i = 1; i <= n ;i++) {
        int tem = -1, minDis = INF;
        for(int j = 1; j <= n ;j++)
            if(!vis[j] && dis[j] < minDis)
                minDis = dis[j], tem = j;
        
        vis[tem] = 1;
        for(nptr p = head[tem]; p ; p = p -> next)
            if(!vis[p -> v] && p -> weight + dis[tem] < dis[p -> v])
                dis[p -> v] = p -> weight + dis[tem], from[p -> v] = tem;
    }
	int typ = readInt();
	for(int i = 0; i < n; i++) {//v
		for(int j = 0; j < typenum[v[i]]; j++) {//idx
			if(type[v[i]][j] == typ) {
				int end = v[i];
				
    			printf("%d %d\n", end, dis[end]);
				if(dis[end] != 0) {
					int tem = end, cnt = 0;
    				while(tem) {
        				road[++cnt] = tem;
        				tem = from[tem];
    				}

    				for(int k = cnt; k > 1 ;k--)
        				printf("%d-", road[k]);
					printf("%d\n", road[1]);
				}
    			
			}
		}
	}
    return 0;
}
