#include <stdio.h>
#include <string.h>
int top = 0;
struct node
{
    char bracket;
    int line;
};
void pushStack(struct node newBrackets[], int *top, struct node brackets)
{
    newBrackets[(*top)++] = brackets;
}

char popStack(struct node newBrackets[], int *top)
{
    return newBrackets[--(*top)].bracket;
}
struct node brackets[300];
struct node newBrackets[300];
int main()
{
    FILE *infile = fopen("example.c", "r");
    char text[1000];
    int line = 0;
    int index = 0;
    while (fgets(text, 1000, infile) != NULL)
    {
        if (strcmp(text, "\n") == 0)
        {
            line++;
            continue;
        }
        line++;
        int textLen = strlen(text);
        for (int i = 0; i < textLen; ++i)
        {
            if (text[i] == '(' || text[i] == ')' || text[i] == '{' || text[i] == '}' || text[i] == '"' || text[i] == '*' || text[i] == '/' || text[i] == '\'')
            {
                brackets[index].bracket = text[i];
                brackets[index++].line = line;
            }
        }
        for (int i = 0; i < index - 1; ++i)
        {
            if (brackets[i].bracket == '/' && brackets[i + 1].bracket == '/' && brackets[i].line == brackets[i + 1].line)
            {
                for (int j = i; j < index; ++j)
                {
                    if (brackets[j].line == brackets[i].line)
                    {
                        brackets[j].bracket = '-';
                    }
                }
                break;
            }
        }
        for (int i = 0; i < index - 1; ++i)
        {
            if (brackets[i].bracket == '/' && brackets[i + 1].bracket == '*')
            {
                for (int j = i + 2; j < index - 1; ++j)
                {
                    if (brackets[j].bracket == '*' && brackets[j + 1].bracket == '/')
                    {
                        for (int k = i; k <= j + 1; ++k)
                        {
                            brackets[k].bracket = '-';
                        }
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < index; ++i)
        {
            if (brackets[i].bracket == '"')
            {
                for (int j = i + 1; j < index; ++j)
                {
                    if (brackets[j].bracket == '"')
                    {
                        for (int k = i; k <= j; ++k)
                        {
                            brackets[k].bracket = '-';
                        }
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < index; ++i)
        {
            if (brackets[i].bracket == '\'')
            {
                for (int j = i + 1; j < index; ++j)
                {
                    if (brackets[j].bracket == '\'')
                    {
                        for (int k = i; k <= j; ++k)
                        {
                            brackets[k].bracket = '-';
                        }
                        break;
                    }
                }
            }
        }
    }

    int check = 0;
    for (int i = 0; i < index; ++i) {
        if (brackets[i].bracket == '(' || brackets[i].bracket == '{') {
            pushStack(newBrackets, &top, brackets[i]);
        } else if (brackets[i].bracket == ')') {
            char symbol = popStack(newBrackets, &top);
            if (symbol != '(') {
                check++;
                printf("without maching ')' at line %d\n", brackets[i].line);
                break;
            }
        } else if (brackets[i].bracket == '}') {
            char symbol = popStack(newBrackets, &top);
            if (symbol == '(') {
                check++;
                printf("without maching '(' at line %d\n", newBrackets[top].line);
                break;
            } else if (symbol != '{') {
                check++;
                printf("without maching '}' at line %d\n", brackets[i].line);
                break;
            }
        }
    }
    if (check == 0)
    {
        if (top == 0)
        {
            for (int i = 0; i < index; i++)
            {
                if (brackets[i].bracket == '(' || brackets[i].bracket == ')' || brackets[i].bracket == '{' || brackets[i].bracket == '}')
                    printf("%c", brackets[i].bracket);
            }
        }
        else
        {
            while (top != 0)
            {
                top--;
                printf("without maching '%c' at line %d", newBrackets[top].bracket, newBrackets[top].line);
                break;
            }
        }
    }
    fclose(infile);
    return 0;
}