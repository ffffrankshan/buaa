#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int needTime;
    int waitTime;
} customer;

int haveSpace(int window[], int windowNum)
{
    for (int i = 0; i < windowNum; ++i)
    {
        if (window[i] == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *numPerPeriod = (int *)malloc(n * sizeof(int));

    int totalNum = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &numPerPeriod[i]);
        totalNum += numPerPeriod[i];
    }

    customer list[totalNum];
    customer *queue[totalNum];
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < numPerPeriod[i]; ++j)
        {
            scanf("%d", &list[index].needTime);
            list[index].waitTime = 0;
            index++;
        }
    }

    int window[5] = {0};
    int windowNum = 3;
    int nowQueueNum = 0;

    index = 0;
    int queueIndex = 0;
    int queueLIndex = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < numPerPeriod[i]; ++k)
        {
            nowQueueNum++;
            queue[queueIndex++] = &list[index++];
        }
        while((nowQueueNum / windowNum) >= 7 && windowNum < 5)
        {
            windowNum++;
        }
        for (int j = 0; j < windowNum; ++j)
        {
            if(nowQueueNum==0) break;
            if (haveSpace(window, windowNum))
            {
                for (int k = 0; k < windowNum; ++k)
                {
                    if (window[k] == 0)
                    {
                        window[k] = queue[queueLIndex++]->needTime;
                        nowQueueNum--;
                        break;
                    }
                }
            }
        }

        for (int k = 0; k < windowNum; ++k)
        {
            if (window[k] != 0)
            {
                window[k]--;
            }
        }
        if (nowQueueNum != 0)
        {
            for (int p = queueLIndex; p < queueIndex; ++p)
            {
                queue[p]->waitTime++;
            }
        }
        if ((nowQueueNum / windowNum) < 7 && windowNum > 3)
        {
            windowNum--;
        }
    }
    while (queueLIndex < queueIndex)
    {
        for (int u = queueLIndex; u < queueIndex; u++)
        {
            int check = 0;
            for (int k = 0; k < windowNum; ++k)
            {
                if (window[k] == 0)
                {
                    window[k] = queue[queueLIndex++]->needTime;
                    check++;
                    nowQueueNum--;
                    break;
                }
            }
        }

        for (int k = 0; k < windowNum; ++k)
        {
            if (window[k] != 0)
            {
                window[k]--;
            }
        }
        for (int p = queueLIndex; p < queueIndex; ++p)
        {
            queue[p]->waitTime++;
        }
        if ((nowQueueNum / windowNum) < 7 && windowNum > 3)
        {
            windowNum--;
        }
    }

    for (int i = 0; i < totalNum; ++i)
    {
        printf("%d : %d\n", i + 1, list[i].waitTime);
    }
    return 0;
}