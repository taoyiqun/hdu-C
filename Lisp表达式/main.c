#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>

#define TRUE 1
#define OK 1
#define ERROR 0
#define MAX_NAME 10    //�����ַ�������󳤶�;
typedef int Status; // Status�Ǻ����ķ������ͣ�
typedef char SElemType;
#define productsize 10  //��ʼ����ֵ
#define pulssize 2  //��������
typedef struct Stack{             //ջ�Ľṹ��
    SElemType *base;        //ջ��ָ��ָ��ͷԪ����ʼλ��
    SElemType *top;         //ջ��ָ��ָ��βԪ����ʼλ��
    int stacksize;
}Stack;
/*����һ��ջ*/
Status ProductStack(Stack   *S){
    (*S).base=(int    *)malloc(productsize* sizeof(SElemType));
    if(!(*S).base){
        printf("����ջʧ��");
        exit(0);
    }
    (*S).top=(*S).base;
    (*S).stacksize=productsize;
    return TRUE;
}
/*ѹջ*/
Status Push(Stack   *S, SElemType e){
    if((*S).top - (*S).base >= (*S).stacksize) // ջ����׷�Ӵ洢�ռ�
    {
        (*S).base = (Stack    *)realloc((*S).base, ((*S).stacksize + pulssize) * sizeof(SElemType));
        if( !(*S).base ){
            exit(0); // �洢����ʧ��
        }
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize +=pulssize;
    }
    *((*S).top)=e;          //��ֵ
    (*S).top++;          //ջ��ָ��������һλ
    return TRUE;
}
/*��ջ*/
Status Pop(Stack *S, SElemType *e) {
    if((*S).top == (*S).base){//ջΪ��
        printf("ջ��\n");
        exit(0);
    }

    ((*S).top)--;          //ջ��ָ����ǰ��һλ
    *e=*((*S).top);          //��ջ
    return TRUE;
}
void ClearStack(Stack *S) { //���ջ�Ĳ���
    S->top=S->base;
}

int StackEmpty(Stack S){
    if(S.base == S.top) {
        return 1;	//��
    }
    else{
        return 0;
    }
}
Status Operate(int a,char op,int b, int    *res)//����
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
                printf("���ʽ���ִ���0����������\n");
                return ERROR;
            }
            *res=b/a;
            break;
        }
    }

    return OK;
}
Status Operating(char a[]) {
    char d,b;//������
    char th,q;//�����
    int i=0;
    int ai;//charת��int������
    Stack OPTR;
    Stack OPND;
    ProductStack(&OPND);//������ջ����Ų�����
    ProductStack(&OPTR);//������ջ����������
    int res;//������
    while(a[i]!='\0') {
        if (isdigit(a[i])) {
            ai = (a[i] - '0');//������ת��Ϊint��
            Push(&OPND, ai);//��������ջ
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
                    Pop(&OPTR, &q);//�����
                    Pop(&OPTR, &th);
                    Pop(&OPND, &d);
                    Pop(&OPND, &b);
                    if (Operate(b, q, d, &res) == OK) {
                        Push(&OPND, res);//��������ջ
                        break;
                    } else {
                        printf("�������\n");
                        return ERROR;

                    }

                }
                default:{
                    printf("���ʽ���ִ����зǷ��ַ�\n");
                    return ERROR;
                }

            }
        }
        i++;
    }
    Pop(&OPND,&res);
    if(StackEmpty(OPND)){
        printf("���Ϊ%d\n",res);
        return OK;
    } else{
        printf("����Ƿ��ж�������\n");
        return ERROR;
    }
}
int main() {
    char a[100];

    printf("����һ���������ʽ��");
    gets(a);

    if(Operating(a)){
        printf("����ɹ�\n");
    } else{
        printf("���ִ���\n");
    }
    return 0;
}