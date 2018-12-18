#include<stdio.h>
#include<stdlib.h>
#include <mem.h>

#define ERROR -1
typedef char ElemType;
typedef struct LNode{
    ElemType      data;
    struct LNode  *next;
}LNode;
typedef LNode* LinkList;
LNode*   new(char data){
    LNode* node=(LNode*)malloc(sizeof(LNode));
    if(!node){
        exit(ERROR);
    }
    node->data=data;
    node->next=NULL;
    return node;

};
int compare(char a, char b){
    if(a>b){
        return 1;
    } else{
        if(a==b){
            return 0;
        } else{
            return -1;
        }
    }
}
int comp(const void *a, const void  *b){
    const char *n1=a;
    const char *n2=b;
    return *n1-*n2;
}
LinkList    ReadSet(){
    printf("Please input set, enter indicated ending,'nullset'indicate nullset \n");
    char k[300];
    scanf("%s",k);
    int len=0;
    LinkList front=(LinkList)malloc(sizeof(LNode));
    if(!front){
        exit(ERROR);
    }
    front->next=NULL;
    LNode   *rear=front;
    if(strcmp(k,"nullset")==0){
        return front->next;
    }
    int u[300];
    for (int j = 0; j <300 ; ++j) {
        u[j]=0;
    }
    for (int i = 0; k[i]!='\0' ; ++i) {
        u[k[i]]=1;
    }
    int num=0;
    for (int l = 0; l <300 ; ++l) {
        if(u[l]==1){
            k[num++]=l;
        }
    }
    k[num]='\0';
    for (int i = 0; k[i]!='\0'; ++i) {
        len++;
    }
    qsort(k,len, sizeof(k[0]),comp);
    for (int j = 0; j <len ; ++j) {
        LNode* node=(LNode*)malloc(sizeof(LNode));
        if(!node){
            exit(ERROR);
        }
        node->data=k[j];
        node->next=NULL;
        rear->next=node;
        rear=node;
    }
    return front->next;
}
void PrintSet(LinkList front){
    printf("{ ");
    LNode* p=front;
    while (p!=NULL){
        printf("%c ",p->data);
        p=p->next;
    }
    printf("}\n");
}
LinkList Union(LinkList p1,LinkList p2){
    LinkList front=(LinkList)malloc(sizeof(LNode));
    if(!front){
        exit(ERROR);
    }
    front->next=NULL;
    LNode   *rear=front;
    LNode   *t1=p1;
    LNode   *t2=p2;
    while (t1&&t2){
        switch (compare(t1->data,t2->data)){
            case 1:{
                LNode   *node=new(t2->data);
                rear->next=node;
                rear=node;
                t2=t2->next;
                break;
            }
            case 0:{
                LNode   *node=new(t1->data);
                rear->next=node;
                rear=node;
                t1=t1->next;
                t2=t2->next;
                break;
            }
            case -1:{
                LNode   *node=new(t1->data);
                rear->next=node;
                rear=node;
                t1=t1->next;
                break;
            }
        }
    }
    while (t1){
        LNode   *node=new(t1->data);
        rear->next=node;
        rear=node;
        t1=t1->next;
    }
    while (t2){
        LNode   *node=new(t2->data);
        rear->next=node;
        rear=node;
        t2=t2->next;
    }
    front=front->next;
    return front;
}
LinkList Mix(LinkList p1,LinkList p2){
    LinkList front=(LinkList)malloc(sizeof(LNode));
    if(!front){
        exit(ERROR);
    }
    front->next=NULL;
    LNode   *rear=front;
    LNode   *t1=p1;
    LNode   *t2=p2;
    while (t1&&t2){
        switch (compare(t1->data,t2->data)){
            case 1:{
                t2=t2->next;
                break;
            }
            case 0:{
                LNode   *node=new(t1->data);
                rear->next=node;
                rear=node;
                t1=t1->next;
                t2=t2->next;
                break;
            }
            case -1:{
                t1=t1->next;
                break;
            }
        }
    }
    front=front->next;
    return front;
}
LinkList Subtraction(LinkList p1,LinkList p2){
    LinkList front=(LinkList)malloc(sizeof(LNode));
    if(!front){
        exit(ERROR);
    }
    front->next=NULL;
    LNode   *rear=front;
    LNode   *t1=p1;
    LNode   *t2=p2;
    while (t1&&t2){
        switch (compare(t1->data,t2->data)){
            case 1:{
                t2=t2->next;
                break;
            }
            case 0:{
                t1=t1->next;
                t2=t2->next;
                break;
            }
            case -1:{
                LNode   *node=new(t1->data);
                rear->next=node;
                rear=node;
                t1=t1->next;
                break;
            }
        }
    }
    while (t1){
        LNode   *node=new(t1->data);
        rear->next=node;
        rear=node;
        t1=t1->next;
    }
    front=front->next;
    return front;
}
//p1?p2???
int Subset(LinkList p1,LinkList p2){
    LNode   *t1=p1;
    LNode   *t2=p2;
    while (t1&&t2){
        switch (compare(t1->data,t2->data)){
            case 1:{
                t2=t2->next;
                break;
            }
            case 0:{
                t1=t1->next;
                t2=t2->next;
                break;
            }
            case -1:{
                return 0;
            }
        }
    }
    if(t1){
        return 0;
    }
    return 1;
}
//p1?p2????,????p1?p2??
LinkList Complement(LinkList p1,LinkList p2){
    return Subtraction(p2,p1);
}
void Clear(LinkList p){
    LNode   *t;
    while (p){
        t=p->next;
        free(p);
        p=t;
    }
}
int main(){
    while (1){
        printf("welcome\n");
        printf("1 Union\n");
        printf("2 Mix\n");
        printf("3 Subtraction\n");
        printf("4 Subset\n");
        printf("5 Complement\n");
        printf("6 Exit\n");
        int a;
        scanf("%d",&a);
        switch (a){
            case 1:{
                LinkList front1;
                LinkList front2;
                LinkList front3;
                front1=ReadSet();
                front2=ReadSet();
                front3=Union(front1,front2);
                printf("Result\n");
                PrintSet(front3);
                Clear(front1);
                Clear(front2);
                Clear(front3);
                break;
            }
            case 2:{
                LinkList front1;
                LinkList front2;
                LinkList front3;
                front1=ReadSet();
                front2=ReadSet();
                front3=Mix(front1,front2);
                printf("Result\n");
                PrintSet(front3);
                break;
            }
            case 3:{
                LinkList front1;
                LinkList front2;
                LinkList front3;
                front1=ReadSet();
                front2=ReadSet();
                front3=Subtraction(front1,front2);
                printf("Result\n");
                PrintSet(front3);
                Clear(front1);
                Clear(front2);
                Clear(front3);
                break;
            }
            case 4:{
                LinkList front1;
                LinkList front2;
                int flag=0;
                front1=ReadSet();
                front2=ReadSet();
                flag=Subset(front1,front2);
                if(flag==0){
                    printf("not subset\n");
                } else{
                    printf("subset\n");
                }
                Clear(front1);
                Clear(front2);
                break;
            }
            case 5:{
                LinkList front1;
                LinkList front2;
                LinkList front3;
                int flag=0;
                front1=ReadSet();
                front2=ReadSet();
                flag=Subset(front1,front2);
                if(flag==0){
                    printf("not subset\n");
                } else{
                    front3=Complement(front1,front2);
                    printf("Result\n");
                    PrintSet(front3);
                    Clear(front3);
                }
                Clear(front1);
                Clear(front2);
                break;
            }
            case 6:{
               exit(0);
            }
            default:{
                printf("error\n");
                continue;
            }
        }
    }
    return 0;
}