#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 500
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 20
#define MAX_PRESS_LEN 30
#define MAX_DATE_LEN 10

struct book {
    char title[MAX_TITLE_LEN + 1];
    char author[MAX_AUTHOR_LEN + 1];
    char press[MAX_PRESS_LEN + 1];
    char date[MAX_DATE_LEN + 1];
};

void sort(struct book a[], int num) {
    struct book temp;
    for(int i = 0; i < num - 1; ++i) {
        for(int j = 0; j < num - 1 - i; ++j) {
            if(strcmp(a[j].title, a[j + 1].title) > 0) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void deleteBook(struct book a[], int *num, int index) {
    for(int i = index; i < *num - 1; ++i) {
        a[i] = a[i + 1];
    }
    (*num)--;
}

int main() 
{
    FILE *in = fopen("books.txt", "r");
    FILE *out = fopen("ordered.txt", "w");
    struct book list[MAX_BOOKS];
    int num = 0;
    char line[MAX_TITLE_LEN + MAX_AUTHOR_LEN + MAX_PRESS_LEN + MAX_DATE_LEN + 4]; 
    while(fgets(line, sizeof(line), in) != NULL) {
        sscanf(line, "%s %s %s %s", list[num].title, list[num].author, list[num].press, list[num].date);
        num++;
    }
    sort(list, num);

    int order;
    char key[MAX_TITLE_LEN];
    while(scanf("%d", &order) == 1) {
        switch(order) {
            case 1:
                scanf("%s %s %s %s", list[num].title, list[num].author, list[num].press, list[num].date);
                num++;
                sort(list, num);
                break;
            case 2:
                scanf("%s", key);
                for (int i = 0; i < num; ++i) {
                    if (strstr(list[i].title, key) != NULL) {
                        printf("%-50s%-20s%-30s%-10s\n", list[i].title, list[i].author, list[i].press, list[i].date);
                    }
                }
                break;
            case 3:
                scanf("%s", key);
                for (int i = 0; i < num; ++i) {
                    if (strstr(list[i].title, key) != NULL) {
                        deleteBook(list, &num, i);
                        i--; 
                    }
                }
                sort(list, num);
                break;
            case 0:
                for (int i = 0; i < num; ++i) {
                    fprintf(out, "%-50s%-20s%-30s%-10s\n", list[i].title, list[i].author, list[i].press, list[i].date);
                }
                fclose(in);
                fclose(out);
                return 0;
            default:
                break;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
