#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    int flag; // 0->num 1->operator
    char operator;
    int num;
    struct node *parent, *left, *right;
} node;

void pushStack(node *stack[], node *arr, int *top)
{
    stack[++(*top)] = arr;
}

node *popStack(node *stack[], int *top)
{
    return stack[(*top)--];
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '(' || ch == ')')
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

void pushChar(char stack[], char value, int *top)
{
    stack[++(*top)] = value;
}

char popChar(char stack[], int *top)
{
    return stack[(*top)--];
}

node *tranToRPN(char *expression, int *topRPN)
{
    int top = -1;
    char stack[100];
    node *RPN = (node *)malloc(sizeof(node) * 100);
    int expLen = strlen(expression);
    for (int i = 0; i < expLen; ++i)
    {
        if (expression[i] == ' ')
            continue;
        if (isdigit(expression[i]))
        {
            int num = 0;
            while (isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            RPN[++(*topRPN)].num = num;
            RPN[*topRPN].flag = 0;
            i--;
        }

        if (expression[i] == '(')
        {
            pushChar(stack, expression[i], &top);
        }

        if (expression[i] == ')')
        {
            char ch;
            while (stack[top] != '(')
            {
                ch = popChar(stack, &top);
                RPN[++(*topRPN)].operator= ch;
                RPN[(*topRPN)].flag = 1;
            }
            ch = popChar(stack, &top);
        }

        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            if (top == -1 || stack[top] == '(' || precedence(expression[i]) > precedence(stack[top]))
            {
                pushChar(stack, expression[i], &top);
            }
            else
            {
                char ch;
                while (top != -1 && precedence(stack[top]) >= precedence(expression[i]) && stack[top] != '(')
                {
                    ch = popChar(stack, &top);
                    RPN[++(*topRPN)].operator= ch;
                    RPN[(*topRPN)].flag = 1;
                }
                pushChar(stack, expression[i], &top);
            }
        }
        if (expression[i] == '=')
        {
            while (top != -1)
            {
                char ch = popChar(stack, &top);
                RPN[++(*topRPN)].operator= ch;
                RPN[(*topRPN)].flag = 1;
            }
        }
    }
    return RPN;
}
int cal(node *root)
{
    switch ((root->operator))
    {
    case '+':
        return (root->left->num) + (root->right->num);
        break;
    case '-':
        return (root->left->num) - (root->right->num);
        break;
    case '*':
        return (root->left->num) * (root->right->num);
        break;
    case '/':
        return (root->left->num) / (root->right->num);
        break;

    default:
        return 0;
        break;
    }
}
int ans = 0;
int calTree(node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->left != NULL && root->right != NULL)
    {
        calTree(root->left);
        calTree(root->right);
    }

    if (root->left != NULL && root->right != NULL && root->left->flag == 0 && root->right->flag == 0)
    {
        root->num = cal(root);
        root->flag = 0;
    }

    return root->num;
}

int main()
{
    char *expression = (char *)malloc(100 * sizeof(char));
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = '\0';
    node *rpn = (node *)malloc(100 * sizeof(node));
    int topRPN = -1;
    rpn = tranToRPN(expression, &topRPN);
    node *stack[100];

    int top = -1;
    for (int i = 0; i <= topRPN; i++)
    {
        if (rpn[i].flag == 0)
        {
            pushStack(stack, &rpn[i], &top);
        }
        else
        {
            rpn[i].right = popStack(stack, &top);
            rpn[i].left = popStack(stack, &top);
            pushStack(stack, &rpn[i], &top);
        }
    }
    if (rpn[topRPN].left->flag == 1 && rpn[topRPN].right->flag == 1)
        printf("%c %c %c\n", rpn[topRPN].operator, rpn[topRPN].left->operator, (rpn[topRPN].right)->operator);
    else
        printf("%c %c %d\n", rpn[topRPN].operator, rpn[topRPN].left->operator, rpn[topRPN].right->num);
    ans = calTree(&rpn[topRPN]);
    printf("%d", ans);
    return 0;
}