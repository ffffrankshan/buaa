#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct stone {
	int w;
	struct stone *next;
};
struct stone *list = NULL;

struct stone* insert(struct stone *list, int item)
{ 
struct stone *p = NULL, *q = NULL, *r = NULL;
r = (struct stone*)malloc(sizeof(struct stone)); //创建一个数据项为item的新结点
r->w = item; r->next = NULL;
if(list == NULL) /* 情况1：list是一个空表 */
return r;
for(p=list; p != NULL && item > p->w; q = p, p = p->next) /* 找到插入位置 */
;
if( p == list){ /*情况2：在首结点前插入 */
r->next = p;
return r;
} 
else { /* 情况3：在结点q后插入一个结点 */
q->next = r;
r->next = p;
}
return list;
}

int main()
{
	int sum = 0;
	while(1) {
		int n;
		scanf("%d", &n);
		if(n == 999999) break;
		if(n > 0) {
			list = insert(list, n);
			sum += n;
		} else if(n < 0) {
			int n1 = 0-n;
			if(n1 <= sum) {
				struct stone *p;
				int add = 0;
				for(p = list; p!=NULL; p = p->next) {
					add += p->w;
					if(add == n1) {
						list = p->next;
						break;
					} else if(add > n1) {
						list = p;
						list->w = add-n1;
						break;
					}
				}
			}
		} else if(n == 0){
			struct stone *p;
			int add = 0;
			for(p = list; p!=NULL; p = p->next) {
				if(p->w < 10) {
					add += p->w;
					if(p == list) list = list->next;
					else {
						struct stone *q;
						for(q = list; q->next != p; q = q->next)
							;
						q->next = p->next;
					}
				}
			}
			list = insert(list, add);
		}
	}
	struct stone *p;
	for(p = list; p!=NULL; p = p->next) {
		if(p->w != 0) printf("%d ", p->w);
	}
    return 0;
}
