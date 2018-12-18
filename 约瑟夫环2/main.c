#include <stdio.h>
#include <malloc.h>
/*节点结构体*/
struct list{
    int node;
    struct list *next;
};
/*地址结构体，含头地址和尾地址*/
struct location{
    struct list*head;
    struct list*tail;
};
/*产生n个节点的循环单链表,返回它的头结点和尾节点*/
struct location*    product(int n){
    struct list *head=NULL;
    struct list *pnew;
    struct list *p;
    struct location*    result=(struct    location*)malloc(sizeof(struct  location));
    pnew=(struct    list*)malloc(sizeof(struct  list));
    pnew->node=1;
    head=pnew;
    p=pnew;
    for(int i=2;i<=n;i++) {
        pnew=(struct    list*)malloc(sizeof(struct   list));
        pnew->node=i;
        p->next=pnew;
        p=pnew;
    }
    p->next=head;
    result->tail=p;
    result->head=head;
    return result;
}
/*模拟游戏过程，将链表重排，返回重排后头地址和尾地址*/
struct location*    run1(struct location    *site, int  n){
    struct location *newsite=NULL;
    struct list *p=site->head;
    struct list *pa=site->tail;
    struct list *newhead=NULL;
    struct list *newp=NULL;
    newsite=(struct    location*)malloc(sizeof(struct   location));
    for(int i=1;i<n;i++){
        pa=p;
        p=p->next;
    }
    pa->next=p->next;
    newp=newhead=p;
    p=pa->next;
    while (p->next!=p){
        for(int i=1;i<n;i++){
            pa=p;
            p=p->next;
        }
        pa->next=p->next;
        newp->next=p;
        newp=newp->next;
        p=pa->next;
    }
    newp->next=p;
    newp=newp->next;
    newp->next=newhead;
    //for(p=newhead;p->next!=newhead;p=p->next){
    //   printf("%d ",p->node);
    //}
    //printf("\n");

    newsite->head=newhead;
    newsite->tail=newp;
    return newsite;
}
/*打印链表*/
void run2(struct list *head){
    struct list *p=head;
    struct list *pa=NULL;
    while(p->next!=head){
        printf("%-4d",p->node);
        pa=p;
        p=p->next;
        free(pa);
    }
    printf("%-4d\n",p->node);
    free(p);
}
int main() {
    int a=0;
    int b=0;
    scanf("%d",&a);
    struct location *p=product(a);
    while ((scanf("%d",&b))!=EOF){
        p=run1(p,b);//不断将链表重排
    }
    run2(p->head);
}