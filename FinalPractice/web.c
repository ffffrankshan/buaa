#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char website[105][85], vis[105], totalWeb;
char page[105][85], totalPage;

int backStk[105], backTop = -1;
int forwardStk[105], forwardTop = -1;
char op[15], url[85];

int readInt() {
    int tem;
    scanf("%d", &tem);
    return tem;
}

int findPage(char *url) {
    for(int i = 0; i < totalPage; i++) {
        if(strcmp(page[i], url) == 0) 
            return i;
    }
    strcpy(page[totalPage], url);
    return totalPage++;
}

void updateWebsite(int i) {
    char *tem = (char *)malloc(85);
    strcpy(tem, page[i] + strlen("https://"));
    char *p = tem;
    while(*p != '/') p++;
    *p = 0; // 截断字符串
    for(int i = 0; i < totalWeb; i++) 
        if(strcmp(website[i], tem) == 0) {
            vis[i]++;
            return ;
        }
    strcpy(website[totalWeb], tem);
    vis[totalWeb++] = 1;
}

int history[105], total;

int main() {
    int current = findPage("https://www.baidu.com/");
    history[total++] = current;
    updateWebsite(current);
    int tem;
    while(1) {
        scanf("%s", op);
        if(strcmp(op, "VISIT") == 0) {
            backStk[++backTop] = current;
            scanf("%s", url);
            forwardTop = -1; // 清空前进栈
            current = findPage(url);
        } else if(strcmp(op, "<-") == 0) {
            if(backTop == -1)
                continue;
            forwardStk[++forwardTop] = current;
            current = backStk[backTop--];
        } else if(strcmp(op, "->") == 0) {
            if(forwardTop == -1)
                continue;
            backStk[++backTop] = current;
            current = forwardStk[forwardTop--];
        } else if(strcmp(op, "QUIT") == 0) {
        	tem = readInt();
        	break;
		} else 
            break;
        history[total++] = current;
        updateWebsite(current);
    }
    for(int i = 0; i < total; i++)
        printf("%s\n", page[history[i]]);
    if(tem == 1) {
        int maxVis = 0, maxId = -1;
        for(int i = 0; i < totalWeb; i++) {
            if(vis[i] > maxVis) {
                maxVis = vis[i];
                maxId = i;
            }
        }
       	printf("%s %d", website[maxId], maxVis);
    }
}