#include <stdio.h>
#include<stdlib.h>
#include <string.h>
const int shunxu[8][8]={'>','>','<','<','<','>','>','0',
                        '>','>','<','<','<','>','>','0',
                        '>','>','>','>','<','>','>','0',
                        '>','>','>','>','<','>','>','0',
                        '<','<','<','<','<','=','0','0',
                        '>','>','>','>','0','>','>','0',
                        '<','<','<','<','<','0','=','0'};//运算先后矩阵零代表错误
#define productsize 10     //储存空间初始分配量
#define pulssize    2       //储存空间分配增量
struct newnum{
    int fnum;
    int flag;
};//flag为0代表符号，为1代表数字，若flag为0，fnum为数字ascill码，否则为数字字符转换成的int型变量
struct stack{             //栈的结构体
    int *base;        //栈底指针指向头元素起始位置
    int *top;         //栈顶指针指向尾元素起始位置
    int stacksize;
};
/*构造一个栈*/
int productStack(struct stack   *S){
    (*S).base=(int    *)malloc(productsize* sizeof(int));
    if(!(*S).base){
        printf("构造栈失败");
        exit(0);
    }
    (*S).top=(*S).base;
    (*S).stacksize=productsize;
    return 1;
}
/*获取栈顶元素*/
int gettop(struct   stack   S, int *e){
    if(S.top > S.base)
    {
        *e = *(S.top-1);
        return 1;
    }
    else
        return 0;
}
/*压栈*/
int push(struct stack   *S, int    e){
    if((*S).top - (*S).base >= (*S).stacksize) // 栈满，追加存储空间
    {
        (*S).base = (struct stack    *)realloc((*S).base, ((*S).stacksize + pulssize) * sizeof(int));
        if( !(*S).base )
            exit(0); // 存储分配失败
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize +=pulssize;
    }
    *((*S).top)=e;          //赋值
    (*S).top++;          //栈顶指针往后移一位
    return 1;
}
/*出栈*/
int pop(struct  stack *S, int *e)
{
    if((*S).top == (*S).base)//栈为空
        return 0;
    ((*S).top)--;          //栈顶指针往前移一位
    *e=*((*S).top);          //出栈
    return 1;
}
/*将运算符号转换成先后矩阵的具体行列*/
int trans(int t) {
    switch(t){
        case '+':{
            return 0;
        }
        case '-':{
            return 1;
        }
        case '*':{
            return 2;
        }
        case '/':{
            return 3;
        }
        case '(':{
            return 4;
        }
        case ')':{
            return 5;
        }
        case '#':{
            return 6;
        }
        default:{
            return 7;
        }
    }
}
/*判断先后顺序*/
int panduan(int t1, int t2)
{
    int a=trans(t1);
    int b=trans(t2);
    int res=shunxu[a][b];
    if(res=='0'){
        printf("输入错误");
        exit(0);
    }
    return res;
}
/*运算*/
int oprate(int a, int theta, int b)
{
    int c;
    switch(theta)
    {
        case'+':
            c=a+b;
            break;
        case'-':
            c=a-b;
            break;
        case'*':
            c=a*b;
            break;
        case'/':c=a/b;
    }
    return c;
}
/*对得到的字符串处理，将符号和数字区分开，并且储存*/
int deal(char  e[],struct newnum    fe[]){
    char *p;
    int i=0;
    int j=0;;
    while (*(e+i)!='\0'){
        if(*(e+i)=='+'||*(e+i)=='-'||*(e+i)=='*'||*(e+i)=='/'||*(e+i)=='#'||*(e+i)=='('||*(e+i)==')'){
            fe[j].fnum=*(e+i);
            fe[j].flag=0;
            j++;
            i++;
        } else{
            int per=1;
            int fnum2=0;
            while ((*(e+i)!='\0')&&((*(e+i)>='0')&&(*(e+i)<='9'))){
                fnum2=fnum2*per+(*(e+i)-'0');
                per=per*10;
                i++;
            }
            fe[j].fnum=fnum2;
            fe[j].flag=1;
            j++;
        }
    }
    return  j;
}
/*整个式子的运算*/
int evaluate() {
    struct stack fuhao, num;
    int length=0;
    int x,theta,a,b;
    struct newnum   fexpression[200];
    char expression[200];
    gets(expression);
    strcat(expression,"#");
    length=deal(expression,fexpression);
    productStack(&fuhao);
    push(&fuhao, '#');
    productStack(&num);
    gettop(fuhao, &x);
    for (int i = 0; i < length; ) {
        if (((fexpression[i].flag==0)&&(fexpression[i].fnum != '#')) || x != '#'||fexpression[i].flag==1) {
            if (fexpression[i].flag==0){
                switch (panduan(x,fexpression[i].fnum)) {
                    case '<':
                        push(&fuhao, expression[i]);// 栈顶元素优先权低
                        i++;
                        break;
                    case '=':
                        pop(&fuhao, &x);
                        i++;
                        break;
                    case '>':
                        pop(&fuhao, &theta); // 退栈并将运算结果入栈
                        pop(&num, &b);
                        pop(&num, &a);
                        push(&num, oprate(a, theta, b));
                        break;
                }
            }else{
                push(&num,fexpression[i].fnum);
                i++;
            }
            gettop(fuhao, &x);
        } else{
            break;
        }
    }
    gettop(num,&x);
    return x;
}
int main() {
    printf("请输入算术表达式:");
    printf("%d\n", evaluate());
    return 0;
}