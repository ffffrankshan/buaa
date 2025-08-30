#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FUNCTIONS 100
#define MAX_NAME_LENGTH 25
#define MAX_CALLED 12
#define MAX_STACK 205

typedef struct {
    char name[MAX_NAME_LENGTH];
    char *called[MAX_CALLED];
    int calls;
    int flag;
} Function;

typedef struct {
    char *stack[MAX_STACK];
    int top;
} Stack;

Function f[MAX_FUNCTIONS];
Stack s;
int functions = 0;

Function *instack(const char *name) {
    for (int i = 0; i < functions; i++) {
        if (strcmp(f[i].name, name) == 0) {
            return &f[i];
        }
    }
    strcpy(f[functions].name, name);
    f[functions].calls = 0;
    f[functions].flag = 0;
    return &f[functions++];
}

int main() {
    s.top = -1;
    int op;
    char name[MAX_NAME_LENGTH];

    while (scanf("%d", &op) != EOF) {
        if (op == 8) {
            scanf("%s", name);
            Function *current = instack(name);
            if (s.top >= 0) {
                char *callerName = s.stack[s.top];
                Function *caller = instack(callerName);
                int flag = 0;
                for (int i = 0; i < caller->calls; i++) {
                    if (strcmp(caller->called[i], name) == 0) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    caller->called[caller->calls] = strdup(name);
                    caller->calls++;
                    caller->flag = 1;
                }
            }
            s.stack[++s.top] = strdup(name);
        } else if (op == 0) {
            if (s.top >= 0) {
                free(s.stack[s.top]);
                s.top--;
            }
            if (s.top == -1) {
                break;
            }
        }
    }

    for (int i = 0; i < functions; i++) {
        if (f[i].flag && f[i].calls > 0) {
            printf("%s:", f[i].name);
            for (int j = 0; j < f[i].calls; j++) {
                printf("%s", f[i].called[j]);
                if (j < f[i].calls - 1) {
                    printf(",");
                }
            }
            printf("\n");
        }
    }

    for (int i = 0; i <= s.top; i++) {
        free(s.stack[i]);
    }
    for (int i = 0; i < functions; i++) {
        for (int j = 0; j < f[i].calls; j++) {
            free(f[i].called[j]);
        }
    }

    return 0;
}