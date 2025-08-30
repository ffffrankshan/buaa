#include <stdio.h>
#include <string.h>
int main()
{
    char num[200];
    fgets(num, sizeof(num), stdin);
    num[strcspn(num, "\n")] = '\0';
    int flag;
    int l = strlen(num);
    for (int i = 0; i < l; ++i)
    {
        if (num[i] == '.')
        {
            flag = i;
            break;
        }
    }
    if (flag == 1)
    {
        if (num[0] == '0')
        {
            while (num[flag + 1] == '0')
                flag++;
            char newNum[200];
            for (int i = 0; i < l - flag; i++)
                newNum[i] = num[flag + 1 + i];
            int newL = strlen(newNum);
            if (newL > 1)
            {
                for (int i = 0; i < newL; ++i)
                {
                    newNum[newL - i] = newNum[newL - 1 - i];
                    if (newL - 1 - i == 1)
                    {
                        newNum[1] = '.';
                        break;
                    }
                    newNum[newL + 1] = '\0';
                }
            }
            printf("%se-%d", newNum, flag);
        } else printf("%se0", num);
    } else {
        for (int i = 0; i < flag - 1; ++i)
        {
            num[flag - i] = num[flag - i - 1];
        }
        num[1] = '.';
        printf("%se%d", num, flag - 1);
    }
    return 0;
}
