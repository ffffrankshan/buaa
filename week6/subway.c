#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>

#define MAX_STATIONS 512
#define INF 999999

// 地铁站点结构体
typedef struct
{
    char name[50];
    int is_transfer;
    int flag;
} station;

typedef struct
{
    int weight;
    int line_id;
} weight;

station BGvertexs[MAX_STATIONS];
weight BGweights[MAX_STATIONS][MAX_STATIONS];
int Vnum;

void read_subwayline_information(char *filename);
int add_vertex(station st);
void Dijkstra(int v0, int v1, int spath[]);
void printPath(int v0, int v1, int spath[]);

int main()
{
    read_subwayline_information("bgstations.txt");

    int spath[MAX_STATIONS];
    char start[50], end[50];

    //printf("Enter the starting station: ");
    scanf("%s", start);
    //printf("Enter the destination station: ");
    scanf("%s", end);

    int v0 = -1, v1 = -1;
    for (int i = 0; i < Vnum; i++)
    {
        if (strcmp(BGvertexs[i].name, start) == 0)
        {
            v0 = i;
        }
        if (strcmp(BGvertexs[i].name, end) == 0)
        {
            v1 = i;
        }
    }

    if (v0 == -1 || v1 == -1)
    {
        printf("One or both stations not found in the graph.\n");
        return 1;
    }

    Dijkstra(v0, v1, spath);
    printPath(v0, v1, spath);

    return 0;
}

void read_subwayline_information(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int total_line_num;
    int v1, v2;
    int line_id, staion_num_in_line;
    station st;
    fscanf(file, "%d", &total_line_num);
    for (int i = 0; i < total_line_num; ++i)
    {
        fscanf(file, "%d %d", &line_id, &staion_num_in_line);
        v1 = v2 = -1;
        for (int j = 0; j < staion_num_in_line; ++j)
        {
            fscanf(file, "%s %d", st.name, &st.is_transfer);
            v2 = add_vertex(st);

            if (v1 != -1)
            {
                BGweights[v1][v2].weight = BGweights[v2][v1].weight = 1;
                BGweights[v1][v2].line_id = BGweights[v2][v1].line_id = line_id;
            }

            v1 = v2;
        }
    }
    fclose(file);
    return;
}

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
