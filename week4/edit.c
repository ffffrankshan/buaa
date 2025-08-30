#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int op;
    int pos;
    int n;
    char str[512];
} operate;

void add(int pos, char *str, char *text)
{
    int strLen = strlen(str);
    memmove(text + pos + strLen, text + pos, strlen(text + pos) + 1);
    memmove(text + pos, str, strLen);
}

void del(int pos, int n, char *text)
{
    if (strlen(text + pos) >= n)
    {
        memmove(text + pos, text + pos + n, strlen(text + pos + n) + 1);
    }
    else
    {
        text[pos] = '\0';
    }
}

void undo(operate step[], int index, char *text)
{
    switch(step[index].op)
    {
    	case 1:
        	del(step[index].pos, strlen(step[index].str), text);
        	break;
    	case 2:
        	add(step[index].pos, step[index].str, text);
        	break;
    	case 0:
        	undo(step, index - 1, text);
    }
    step[index].op = 0;//already undo
}

int main()
{
    char text[512];
    gets(text);

    int n = 0;
    operate step[100];
    scanf("%d", &n);
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        int op, pos;
        char str[512];
        scanf("%d %d %s", &op, &pos, str);
        step[i].op = op;
        step[i].pos = pos;
        memcpy(step[i].str, str, strlen(str) + 1);
        if (op == 2) step[i].n = 0;
    }
    index = n;

    char order[20];
    int back = 1;
    getchar();
    while(gets(order) != NULL)
    {
        if (strcmp(order, "\n") == 0)
            continue;
        if (strlen(order) == 1)
        {
            undo(step, index - back, text);
            back += 2;
            index++;
        }
        else if (strlen(order) == 2 && order[0] == '-' && order[1] == '1')
            break;
        else
        {
            back = 1;
            int op;
            sscanf(order, "%d", &op);
            if (op == 1)
            {
                sscanf(order, "%d %d %s", &step[index].op, &step[index].pos, step[index].str);
                add(step[index].pos, step[index].str, text);
            }
            else if (op == 2)
            {
                sscanf(order, "%d %d %d", &step[index].op, &step[index].pos, &step[index].n);
                memmove(step[index].str, text + step[index].pos, step[index].n);
                del(step[index].pos, step[index].n, text);
            }
            index++;
        }
    }
    puts(text);
    return 0;
}