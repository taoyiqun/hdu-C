#include <stdio.h>
#include<stdlib.h>
#include <string.h>
const int shunxu[8][8]={'>','>','<','<','<','>','>','0',
                        '>','>','<','<','<','>','>','0',
                        '>','>','>','>','<','>','>','0',
                        '>','>','>','>','<','>','>','0',
                        '<','<','<','<','<','=','0','0',
                        '>','>','>','>','0','>','>','0',
                        '<','<','<','<','<','0','=','0'};//�����Ⱥ������������
#define productsize 10     //����ռ��ʼ������
#define pulssize    2       //����ռ��������
struct newnum{
    int fnum;
    int flag;
};//flagΪ0������ţ�Ϊ1�������֣���flagΪ0��fnumΪ����ascill�룬����Ϊ�����ַ�ת���ɵ�int�ͱ���
struct stack{             //ջ�Ľṹ��
    int *base;        //ջ��ָ��ָ��ͷԪ����ʼλ��
    int *top;         //ջ��ָ��ָ��βԪ����ʼλ��
    int stacksize;
};
/*����һ��ջ*/
int productStack(struct stack   *S){
    (*S).base=(int    *)malloc(productsize* sizeof(int));
    if(!(*S).base){
        printf("����ջʧ��");
        exit(0);
    }
    (*S).top=(*S).base;
    (*S).stacksize=productsize;
    return 1;
}
/*��ȡջ��Ԫ��*/
int gettop(struct   stack   S, int *e){
    if(S.top > S.base)
    {
        *e = *(S.top-1);
        return 1;
    }
    else
        return 0;
}
/*ѹջ*/
int push(struct stack   *S, int    e){
    if((*S).top - (*S).base >= (*S).stacksize) // ջ����׷�Ӵ洢�ռ�
    {
        (*S).base = (struct stack    *)realloc((*S).base, ((*S).stacksize + pulssize) * sizeof(int));
        if( !(*S).base )
            exit(0); // �洢����ʧ��
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize +=pulssize;
    }
    *((*S).top)=e;          //��ֵ
    (*S).top++;          //ջ��ָ��������һλ
    return 1;
}
/*��ջ*/
int pop(struct  stack *S, int *e)
{
    if((*S).top == (*S).base)//ջΪ��
        return 0;
    ((*S).top)--;          //ջ��ָ����ǰ��һλ
    *e=*((*S).top);          //��ջ
    return 1;
}
/*���������ת�����Ⱥ����ľ�������*/
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
/*�ж��Ⱥ�˳��*/
int panduan(int t1, int t2)
{
    int a=trans(t1);
    int b=trans(t2);
    int res=shunxu[a][b];
    if(res=='0'){
        printf("�������");
        exit(0);
    }
    return res;
}
/*����*/
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
/*�Եõ����ַ������������ź��������ֿ������Ҵ���*/
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
/*����ʽ�ӵ�����*/
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
                        push(&fuhao, expression[i]);// ջ��Ԫ������Ȩ��
                        i++;
                        break;
                    case '=':
                        pop(&fuhao, &x);
                        i++;
                        break;
                    case '>':
                        pop(&fuhao, &theta); // ��ջ������������ջ
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
    printf("�������������ʽ:");
    printf("%d\n", evaluate());
    return 0;
}