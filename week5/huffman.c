//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {			//Huffman树结构
	char c;		
	int weight;		//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};		//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 	//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;			//实验步骤 
FILE *Src, *Obj;
	
void statCount();		//步骤1：统计文件中字符频率
void createHTree();		//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();		//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 		//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();			//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();			//输出步骤3的结果
void print4();			//输出步骤4的结果

int main()
{
        if((Src=fopen("input.txt","r"))==NULL) {
	        fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1; 
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);		//输入当前实验步骤 
	
	statCount();			//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1)?print1():1;   	//输出实验步骤1结果	
	createHTree();			//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2)?print2(Root):2; 	//输出实验步骤2结果	
	makeHCode();		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3)?print3():3;   	//输出实验步骤3结果
	(Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);
        return 0;
} 

//【实验步骤1】开始 
void statCount()
{
	char text[500];
	fgets(text, 500, Src);
	text[strcspn(text, "\n")] = '\0';
	int textLen = strlen(text);
	for (int i = 0; i < textLen; ++i)
	{
		if (text[i] != '\n')
		{
			Ccount[text[i]]++;
		}
	}
	Ccount[0] = 1;
}


//【实验步骤1】结束

//【实验步骤2】开始
void createHTree()
{
	struct tnode *forest[128];
	struct tnode *p;
	int fIndex = 0;
	for (int i = 0; i < 128; ++i)
	{
		if (Ccount[i] > 0)
		{
			p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = p->right = NULL;
			forest[fIndex++] = p;
		}
	}
	for (int i = 0; i < fIndex - 1; ++i)
	{
		for (int j = 0; j < fIndex - 1 - i; ++j)
		{
			if (forest[j]->weight > forest[j + 1]->weight)
			{
				struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
				temp = forest[j];
				forest[j] = forest[j + 1];
				forest[j + 1] = temp;
			}
		}
	}
	int i = 0;
	for (; i < fIndex - 1; ++i)
	{
		if (forest[i]->weight == forest[i + 1]->weight)
		{
			int left = i, right = i + 1;
			while (right + 1 < fIndex && forest[right + 1]->weight == forest[right]->weight)
			{
				right++;
			}
			for (int j = left; j < right; ++j)
			{
				for (int k = left; k < right - j; ++k)
				{
					if (forest[k]->c > forest[k + 1]->c)
					{
						struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
						temp = forest[k];
						forest[k] = forest[k + 1];
						forest[k + 1] = temp;
					}
				}
			}
			i = right;
		}
	}
	int fNum = fIndex;
	while (fNum > 1)
	{
		struct tnode *newT = (struct tnode *)malloc(sizeof(struct tnode));
		newT->left = forest[0];
		newT->right = forest[1];
		newT->weight = forest[0]->weight + forest[1]->weight;
		fNum -= 2;
		memmove(forest, forest + 2, fNum * sizeof(struct tnode *));
		int flag = 0;
		for (int j = 0; j < fNum; ++j)
		{
			if (forest[j]->weight > newT->weight)
			{
				memmove(forest + j + 1, forest + j, (fNum - j) * sizeof(struct tnode *));
				forest[j] = newT;
				fNum++;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			forest[fNum] = newT;
			fNum++;
		}
	}
	Root = forest[0];

	
}



//【实验步骤2】结束

//【实验步骤3】开始
void visitHTree(struct tnode *node, char *code, int depth) {
    if (node == NULL) {
        return;
    }

    // 如果是叶节点，保存当前编码
    if (node->left == NULL && node->right == NULL) {
        code[depth] = '\0';  // 添加字符串结束符
        strcpy(HCode[node->c], code);
        return;
    }

    // 左子树路径添加'0'
    if (node->left != NULL) {
        code[depth] = '0';
        visitHTree(node->left, code, depth + 1);
    }

    // 右子树路径添加'1'
    if (node->right != NULL) {
        code[depth] = '1';
        visitHTree(node->right, code, depth + 1);
    }
}

void makeHCode() {
    // 初始化HCode数组
    for (int i = 0; i < 128; i++) {
        HCode[i][0] = '\0';
    }

    // 临时存储编码的缓冲区
    char code[MAXSIZE];

    // 从根节点开始遍历生成编码
    if (Root != NULL) {
        visitHTree(Root, code, 0);
    }
}



//【实验步骤3】结束

//【实验步骤4】开始
char strH[6000];
void atoHZIP()
{
	fseek(Src, 0, SEEK_SET);
	char text[500];
	fgets(text, 500, Src);
	text[strcspn(text, "\n")] = '\0';
	int textLen = strlen(text);
	for (int i = 0; i < textLen; ++i)
	{
		strcat(strH, HCode[text[i]]);
	}
	strcat(strH,HCode[0]);
	int strHLen = strlen(strH);
	unsigned char hc = 0;
	int i = 0;
	for (; i < strHLen; i++)
	{
		hc = (hc << 1) | (strH[i] - '0');
		if ((i + 1) % 8 == 0)
		{

			fputc(hc, Obj);		// 输出到目标（压缩）文件中
			printf("%x", hc); // 按十六进制输出到屏幕上
			hc = 0;
		}
	}
}


//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}

