#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NHASH 3001
#define MULT 37

unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}

typedef struct wordNode
{
    char word[25];
    struct wordNode *next;
} wordNode;

wordNode *hashTable[NHASH] = {NULL};

void insertHashTable(char *word)
{
    unsigned int h = hash(word);
    wordNode *newNode = (wordNode *)malloc(sizeof(wordNode));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    if (hashTable[h] == NULL)
        hashTable[h] = newNode;
    else
    {
        wordNode *current = hashTable[h];
        wordNode *temp = NULL;
        while (current != NULL && strcmp(current->word, word) < 0)
        {
            temp = current;
            current = current->next;
        }
        temp->next = newNode;
        newNode->next = current;
    }
}

void searchHashTable(char *word)
{
    unsigned int h = hash(word);
    wordNode *current = hashTable[h];
    if(strcmp(current->word, word) == 0)
    {
        printf("1 1");
        return;
    }
    int count = 0;
    while (current != NULL && strcmp(current->word, word) < 0)
    {
        count++;
        current = current->next;
    }
    if (current != NULL && strcmp(current->word, word) == 0)
    {
        printf("1 %d", count);
    }
    else
    {
        printf("0 %d", count);
    }
    return;
}

void normalSearch(char *dictionary[], int index, char *target)
{
    int searchCount = 0;
    for (int i = 0; i < index; ++i)
    {
        searchCount++;
        if (strcmp(dictionary[i], target) == 0)
        {
            printf("1 %d\n", searchCount);
            return;
        }
        else if (strcmp(dictionary[i], target) > 0)
        {
            printf("0 %d\n", searchCount);
            return;
        }
    }
    printf("0 %d\n", searchCount);
    return;
}

void binarySearch(char *dictionary[], int Left, int Right, char *target)
{
    int left = Left;
    int right = Right - 1;
    int mid = left + (right - left) / 2;
    int count = 0;
    while (left <= right)
    {
        count++;
        mid = (left + right) / 2;
        if (strcmp(dictionary[mid], target) > 0)
        {
            right = mid - 1;
        }
        else if (strcmp(dictionary[mid], target) == 0)
        {
            printf("1 %d", count);
            return;
        }
        else
        {
            left = mid + 1;
        }
    }
    printf("0 %d", count);
    return;
}

int indexTable[26];
void buildTable(char *dictionary[], int index)
{
    int alphaCount = 0;
    int alpha = 'a';
    for (int i = 0; i < index; ++i)
    {
        if (*dictionary[i] == alpha)
        {
            alphaCount++;
        }
        else
        {
            indexTable[alpha - 'a'] = alphaCount;
            alpha++;
            --i;
        }
    }
    indexTable[alpha - 'a'] = alphaCount;
    return;
}

int main()
{
    char word[25];
    char *wordList[3500];
    int listIndex = 0;
    FILE *input = fopen("dictionary3000.txt", "r");
    while (fgets(word, 25, input) != NULL)
    {
        word[strcspn(word, "\n")] = '\0';
        word[strcspn(word, "\r")] = '\0';
        wordList[listIndex++] = strdup(word);
    }

    char target[25];
    int method = 0;
    scanf("%s %d", target, &method);
    switch (method)
    {
    case 1:
        normalSearch(wordList, listIndex, target);
        break;
    case 2:
        binarySearch(wordList, 0, listIndex, target);
        break;
    case 3:
        buildTable(wordList, listIndex);
        int Right = indexTable[(*target) - 'a'];
        int Left = 0;
        if ((*target) != 'a')
        {
            Left = indexTable[(*target) - 'a' - 1];
        }
        binarySearch(wordList, Left, Right, target);
        break;
    case 4:
        for (int i = 0; i < listIndex; ++i)
        {
            insertHashTable(wordList[i]);
        }
        searchHashTable(target);
        break;
    default:
        break;
    }
    return 0;
}

