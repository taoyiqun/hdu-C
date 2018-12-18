#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>

#define TRUE 1
#define OK 1
#define ERROR 0
#define MAX_NAME 10    //顶点字符串的最大长度;
typedef int Status; // Status是函数的返回类型；
typedef char SElemType;
#define productsize 10  //初始分配值
#define pulssize 2  //分配增量
typedef struct Stack{             //栈的结构体
    SElemType *base;        //栈底指针指向头元素起始位置
    SElemType *top;         //栈顶指针指向尾元素起始位置
    int stacksize;
}Stack;
/*构造一个栈*/
Status ProductStack(Stack   *S){
    (*S).base=(int    *)malloc(productsize* sizeof(SElemType));
    if(!(*S).base){
        printf("构造栈失败");
        exit(0);
    }
    (*S).top=(*S).base;
    (*S).stacksize=productsize;
    return TRUE;
}
/*压栈*/
Status Push(Stack   *S, SElemType e){
    if((*S).top - (*S).base >= (*S).stacksize) // 栈满，追加存储空间
    {
        (*S).base = (Stack    *)realloc((*S).base, ((*S).stacksize + pulssize) * sizeof(SElemType));
        if( !(*S).base ){
            exit(0); // 存储分配失败
        }
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize +=pulssize;
    }
    *((*S).top)=e;          //赋值
    (*S).top++;          //栈顶指针往后移一位
    return TRUE;
}
/*出栈*/
Status Pop(Stack *S, SElemType *e) {
    if((*S).top == (*S).base){//栈为空
        printf("栈空\n");
        exit(0);
    }

    ((*S).top)--;          //栈顶指针往前移一位
    *e=*((*S).top);          //出栈
    return TRUE;
}
void ClearStack(Stack *S) { //清空栈的操作
    S->top=S->base;
}

int StackEmpty(Stack S){
    if(S.base == S.top) {
        return 1;	//空
    }
    else{
        return 0;
    }
}
Status Operate(int a,char op,int b, int    *res)//运算
{
    switch(op){
        case'+':{
            *res=b+a;
            break;
        }
        case'-':{
            *res=b-a;
            break;
        }
        case'*':{
            *res=b*a;
            break;
        }
        case'/':{
            if(a==0) {
                printf("表达式出现错误！0不能做除数\n");
                return ERROR;
            }
            *res=b/a;
            break;
        }
    }

    return OK;
}
Status Operating(char a[]) {
    char d,b;//操作数
    char th,q;//运算符
    int i=0;
    int ai;//char转成int存数字
    Stack OPTR;
    Stack OPND;
    ProductStack(&OPND);//创建空栈，存放操作数
    ProductStack(&OPTR);//创建空栈，存放运算符
    int res;//运算结果
    while(a[i]!='\0') {
        if (isdigit(a[i])) {
            ai = (a[i] - '0');//操作数转换为int型
            Push(&OPND, ai);//操作数进栈
        } else {
            switch (a[i]) {
                case '(': {
                    Push(&OPTR, a[i]);
                    break;
                }
                case '+': {
                    Push(&OPTR, a[i]);
                    break;
                }
                case '-': {
                    Push(&OPTR, a[i]);
                    break;
                }
                case '*': {
                    Push(&OPTR, a[i]);
                    break;
                }
                case '/': {
                    Push(&OPTR, a[i]);
                    break;
                }
                case ')': {
                    Pop(&OPTR, &q);//运算符
                    Pop(&OPTR, &th);
                    Pop(&OPND, &d);
                    Pop(&OPND, &b);
                    if (Operate(b, q, d, &res) == OK) {
                        Push(&OPND, res);//运算结果进栈
                        break;
                    } else {
                        printf("运算错误\n");
                        return ERROR;

                    }

                }
                default:{
                    printf("表达式出现错误！有非法字符\n");
                    return ERROR;
                }

            }
        }
        i++;
    }
    Pop(&OPND,&res);
    if(StackEmpty(OPND)){
        printf("结果为%d\n",res);
        return OK;
    } else{
        printf("检查是否有多余数字\n");
        return ERROR;
    }
}
int main() {
    char a[100];

    printf("输入一个算术表达式：");
    gets(a);

    if(Operating(a)){
        printf("运算成功\n");
    } else{
        printf("出现错误\n");
    }
    return 0;
}