#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct code {
	char ch;
	struct code *next;
};

int main()
{
	char input[32];
    gets(input);
    char key[128];
    int k = 0, l = 0, count[128]={0};
    while(input[k] != '\0') {
        if(!count[input[k]]) {
            count[input[k]] = 1;
            key[l] = input[k];
            l++;
        }
        k++;
    }
    key[l] = '\0';
    for(int i = 32; i <= 126; i++) {
        if(!count[i]) {
            key[l] = (char)i;
            l++;
        }
    }
    key[l] = '\0';
	
	struct code c[l];
	for(int i = 0; i < l; i++) {
        c[i].ch = key[i];
        if(i == l-1) {
            c[i].next = &c[0];
        } else {
            c[i].next = &c[i+1];
        }
    }
	
	struct code *current = &c[0];
    char theKey[2][l];
    for(int i = 0; i < l - 1; ++i) {
        theKey[0][i] = current->ch;
        int move = current->ch;
        struct code *temp = current;
		while(temp->next != current) {
			temp = temp->next;
		}
		temp->next = current->next;
        current = current->next;
        for(int j = 1; j < move; ++j) {
            current = current->next;
        }
        theKey[1][i] = current->ch;
    }
    theKey[0][l - 1] = current->ch;
    theKey[1][l - 1] = c[0].ch;
	
	FILE *in, *out;
	in = fopen("in.txt", "r"); 
	out = fopen("in_crpyt.txt", "w");
	char text;
	while((text = fgetc(in)) != EOF) {
		if(text >= 32 && text <= 126) {
			for(int j = 0; j < l; j++) {
				if(text == theKey[0][j]) {
					text = theKey[1][j];
					break;
				}
			}
		}
		fputc(text, out);	
	}
	fclose(in);
    fclose(out);
    return 0;
}
