#include<stdio.h>
#include<string.h>

int numStack[200];
int topNumStack = -1;
char operatorStack[200];
int topOperatorStack = -1;

int priority(char operator)
{
    if (operator== '*' || operator== '/')
        return 2;
    else if (operator== '+' || operator== '-')
        return 1;
    else
        return 0;
}

int calculate(int a, int b, char c)
{
    switch(c)
    {
    	case '+':
        	return a+b;
    	case '-':
        	return a-b;
    	case '*':
        	return a*b;
    	case '/':
        	return a/b;
    	default:
        	return 0;
    }
}
int main()
{
    char s[200];
    gets(s);
    int i = 0, num, result;
    while (s[i] != '=') {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num = 0;
            while (s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + s[i] - '0';
                i++;
            }
    		numStack[++topNumStack] = num;
        } else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            while (topOperatorStack != -1 && priority(s[i]) <= priority(operatorStack[topOperatorStack]))
            {
                int b = numStack[topNumStack--];
                int a = numStack[topNumStack--];
                char c = operatorStack[topOperatorStack--];
                result = calculate(a, b, c);
                numStack[++topNumStack] = result;
            }
            operatorStack[++topOperatorStack] = s[i];
            i++;
        } else i++;
    }
    while (topOperatorStack != -1) {
        int b = numStack[topNumStack--];
        int a = numStack[topNumStack--];
        char c = operatorStack[topOperatorStack--];
        result = calculate(a, b, c);
        numStack[++topNumStack] = result;
    }
    printf("%d", numStack[topNumStack--]);
    return 0;
}