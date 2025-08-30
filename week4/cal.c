#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXSIZE 100
typedef double DataType;
//枚举类型enum
enum symbol {NUM, OP, EQ, OTHER};
enum oper {EPT, ADD, MIN, MUL, DIV, LEFT, RIGHT};
int Pri[] = {-1, 0, 0, 1, 1, 2, 2};//operator priority
union sym {
    DataType num;
    enum oper op;
} ; 

//use two
DataType Num_stack[MAXSIZE];
enum oper Op_stack[MAXSIZE]; 
int Ntop=-1;
int Otop=-1;

enum symbol getSym(union sym *item)
{
    int n;
    char c;
    while((c = getchar()) != '=') {
        if(isdigit(c)){
            for(n = 0; isdigit(c); c=getchar())
                n = n*10 + c-'0'; 
            ungetc(c, stdin);
            item->num = n;
            return NUM;
        } 
        else 
            switch(c)  {
                case '+': item->op = ADD; return OP;
                case '-': item->op = MIN; return OP;
                case '*': item->op = MUL; return OP;
                case '/': item->op = DIV; return OP;
                case '(': item->op = LEFT; return OP;
                case ')': item->op = RIGHT; return OP;
                case ' ': case '\t': case '\n': break;
                default: return OTHER;
            }          
    }
    return EQ;
}

void pushOp(enum oper op)
{
    
    Op_stack[++Otop] = op;
}
enum oper popOp()
{
    if(Otop != -1){ 
        return Op_stack[Otop--] ; 
    } 
    return EPT;
}
enum oper topOp()
{
    return Op_stack[Otop];
}
void pushNum(DataType num)
{
    Num_stack[++Ntop] = num;
}
DataType popNum()
{
    return Num_stack[Ntop--];
}
void compute(enum oper op)
{
    DataType tmp;
    switch(op) {
        case ADD:
            pushNum(popNum() + popNum()); break;
        case MIN: 
            tmp = popNum(); 
            pushNum(popNum() - tmp); break;
        case  MUL: 
            pushNum(popNum() * popNum()); break;
        case DIV: 
            tmp = popNum(); 
            pushNum(popNum() / tmp); break;
    }
}
void operate(enum oper op)
{
    enum oper t;
    if(op != RIGHT) { 
        while(Pri[op] <= Pri[topOp()] && topOp() != LEFT)//before can calculate 
            compute(popOp());        
        pushOp(op);       
    }
    else//calculate inside bracket
        while((t = popOp()) != LEFT) 
            compute(t); 
}

int main()
{
    union sym item;
    enum symbol s;
    while((s = getSym(&item)) != EQ) {
        if(s == NUM)
            pushNum(item.num);
        else if(s == OP)
            operate(item.op);
    } 
    while(Otop >= 0)
        compute(popOp());
    if(Ntop == 0)
        printf("%.2f\n", popNum());
    return 0;
}
