#include <bits/stdc++.h>
using namespace std;
#define  ERROR  0
typedef struct PolyNode*    Polynomial;
typedef struct PolyNode{
    double coef;//系数
    int expon;//指数
    Polynomial   link;

}PolyNode;
void    Attach(double c,int e,Polynomial *rear){
    Polynomial node=(Polynomial)malloc(sizeof(PolyNode));
    node->coef=c;
    node->expon=e;
    node->link=NULL;
    (*rear)->link=node;
    (*rear)=node;
}
Polynomial ReadPloy(){
    int N;
    cout<<"Please input N"<<endl;
    cin>>N;
    Polynomial front=(Polynomial)malloc(sizeof(PolyNode));
    if(!front){
        exit(ERROR);
    }
    front=NULL;
    cout<<"Please input"<<N<<"nodes"<<endl;
    for (int i = 0; i <N ; ++i) {
        double  c;
        int e;
        PolyNode  *  p=(PolyNode *)malloc(sizeof(PolyNode));
        cin>>c;
        cin>>e;
        p->coef=c;
        p->expon=e;
        p->link=NULL;
        if(front==NULL||front->expon<e){
            p->link=front;
            front=p;
        } else{
            PolyNode   *q=NULL;
            for (q=front;(q->link)&&(q->link->expon>e);q=q->link);
            if(q->link==NULL){
                q->link=p;
            } else{
                if(q->link->expon==e){
                    q->link->coef+=c;
                } else{
                    if(q->expon==e){
                        q->coef+=c;
                    } else{
                        p->link=q->link;
                        q->link=p;
                    }
                }
            }
        }
    }
    return front;

}
void PrintPoly(Polynomial   p){
    if(!p){
        cout<<"0";
    }
    if(p->coef<0){
        if(p->coef==-1){
            if(p->expon!=0){
                cout<<"-x^"<<p->expon;
            } else{
                cout<<p->coef;
            }
        } else{
            if(p->expon!=0){
                cout<<p->coef<<"x^"<<p->expon;
            } else{
                cout<<p->coef;
            }
        }
        p=p->link;
    } else{
        if(p->coef==1){
            if(p->expon!=0){
                cout<<"x^"<<p->expon;
            } else{
                cout<<p->coef;
            }
        } else{
            if(p->expon!=0){
                cout<<p->coef<<"x^"<<p->expon;
            } else{
                cout<<p->coef;
            }
        }
        p=p->link;
    }
    while (p){
        if(p->coef<0){
            if(p->coef==-1){
                if(p->expon!=0){
                    cout<<"-x^"<<p->expon;
                } else{
                    cout<<p->coef;
                }
            } else{
                if(p->expon!=0){
                    cout<<p->coef<<"x^"<<p->expon;
                } else{
                    cout<<p->coef;
                }
            }
            p=p->link;
        }else{
            if(p->coef==1){
                if(p->expon!=0){
                    cout<<"+x^"<<p->expon;
                } else{
                    cout<<'+'<<p->coef;
                }
            } else{
                if(p->expon!=0){
                    cout<<'+'<<p->coef<<"x^"<<p->expon;
                } else{
                    cout<<'+'<<p->coef;
                }
            }
            p=p->link;
        }
    }
    cout<<endl;
}
Polynomial AddPoly(Polynomial   p1,Polynomial   p2){
    Polynomial front,rear,t;
    front=(Polynomial)malloc(sizeof(PolyNode));
    front->link=NULL;
    rear=front;
    while(p1&&p2){
        if(p1->expon>p2->expon){
            Attach(p1->coef,p1->expon,&rear);
            p1=p1->link;
        } else{
            if(p1->expon<p2->expon){
                Attach(p2->coef,p2->expon,&rear);
                p2=p2->link;
            } else{
                double sum=p1->coef+p2->coef;
                if(sum){
                    Attach(sum,p1->expon,&rear);
                }
                p1=p1->link;
                p2=p2->link;
            }
        }
    }
    while (p1){
        Attach(p1->coef,p1->expon,&rear);
        p1=p1->link;
    }
    while (p2){
        Attach(p2->coef,p2->expon,&rear);
        p2=p2->link;
    }
    t=front;
    front=front->link;
    free(t);
    return front;
}
Polynomial Subtraction(Polynomial   p1,Polynomial   p2){
    Polynomial t;
    t=p2;
    while (t){
        t->coef=-t->coef;
        t=t->link;
    }
    return AddPoly(p1,p2);
}
Polynomial MutiPoly(Polynomial  p1,Polynomial   p2){
    Polynomial front,rear,t,t1,t2;
    front=(Polynomial )malloc(sizeof(PolyNode));
    front->link=NULL;
    rear=front;
    t1=p1;
    t2=p2;
    while (t2){
        double c=t1->coef*t2->coef;
        int e=t1->expon+t2->expon;
        Attach(c,e,&rear);
        t2=t2->link;
    }
    t1=t1->link;
    while (t1){
        t2=p2;
        while (t2){
            double c=t1->coef*t2->coef;
            int e=t1->expon+t2->expon;
            rear=front;
            while (rear->link&&rear->link->expon>e){
                rear=rear->link;
            }
            if(rear->link&&rear->link->expon==e){
                double sum=rear->link->coef+c;
                if(sum){
                    rear->link->coef=sum;
                } else{
                    t=rear->link;
                    rear->link=rear->link->link;
                    free(t);
                }
                t2=t2->link;
            }else {
                Polynomial node=(Polynomial)malloc(sizeof(PolyNode));
                node->coef=c;
                node->expon=e;
                node->link=rear->link;
                rear->link=node;
                t2=t2->link;
            }
        }
        t1=t1->link;

    }
    t=front;
    front=front->link;
    free(t);
    return front;
}
Polynomial Differentiate(Polynomial p){
    Polynomial t;
    t=p;
    Polynomial pr,front;
    front=(Polynomial)malloc(sizeof(PolyNode));
    front->link=NULL;
    pr=front;
    while (t){
        PolyNode* res=(PolyNode *) malloc(sizeof(PolyNode));
        res->coef=t->coef*t->expon;
        res->expon=t->expon-1;
        res->link=NULL;
        if(res->coef==0){
           free(res);
           t=t->link;
        } else{
            pr->link=res;
            pr=res;
            t=t->link;
        }
    }
    t=front;
    front=front->link;
    free(t);
    return front;
}

int main(){
    Polynomial p1,p2,p3,p4;
    p1=ReadPloy();
    p2=ReadPloy();
    PrintPoly(p1);
    PrintPoly(p2);
    p3=AddPoly(p1,p2);
    PrintPoly(p3);
    return 0;
}