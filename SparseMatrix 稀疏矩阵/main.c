#include <stdio.h>
#include <search.h>
#include <stdlib.h>

typedef struct OLNode{      //ʮ������ڵ�
    int row;               //������
    int column;            //������
    int e;                 //��ֵ
    struct OLNode  *right,*down;      //rightָ��ýڵ�ͬһ�е���һ���ڵ㣬downָ��ýڵ�ͬһ�е���һ���ڵ�
}OLNode,*OLink;
typedef struct CrossList{           //ʮ������
    int mu,nu,tu;                   //mu�������� nuΪ������ tuΪ����Ԫ������
    OLink *rhead,*chead;            //rheadָ����нڵ��ͷ��cheadָ����нڵ��ͷ
}CrossList;
typedef struct Triple{              //��Ԫ��ڵ�
    int row;      //������
    int column;   //������
    int e;       //����
}Triple;
typedef struct RLSMatrix{         //��Ԫ��
    Triple  data[410];          //�������Ԫ�����ݵ�����
    int rpos[25];                //���߼����� rops[i]�����i�з���Ԫ����data�����д�����±�
    int mu,nu,tu;                  //mu�������� nuΪ������ tuΪ����Ԫ������
}RLSMatrix;
/*��Ԫ��ת��Ϊʮ������*/
void CreateSMatrix_OL(RLSMatrix r,CrossList *t){
    if(t){
        free(t);
    }
    t->mu=r.mu;
    t->nu=r.nu;
    t->tu=r.tu;
    if(!(t->rhead=(OLink*)malloc((t->mu*(sizeof(OLink)))))){
        exit(-1);
    }
    if(!(t->chead=(OLink*)malloc((t->nu*(sizeof(OLink)))))){
        exit(-1);
    }
    for (int j = 0; j <t->mu ; ++j) {
        t->rhead[j]=NULL;
    }
    for (int k = 0; k < t->nu; ++k) {
        t->chead[k]=NULL;
    }
    for (int i = 0; i <t->tu ; ++i) {
        OLNode*  p; //�����µĽڵ�
        if(!(p=(OLNode *)malloc(sizeof(OLNode)))){
            exit(-1);
        }
        p->column=r.data[i].column;
        p->row=r.data[i].row;
        p->e=r.data[i].e;
        int crow=r.data[i].row;     //crowΪ������
        int cbrow=r.data[i].column; //cbrowΪ������
        if(t->rhead[crow] == NULL||t->rhead[crow]->column > p->column){  //ά����
            p->right=t->rhead[crow];        //�ڵ�һ���ڵ�ǰ�����½ڵ�
            t->rhead[crow]=p;
        } else{             //��ÿһ���ڵ�֮������½ڵ�
            OLNode*   q=t->rhead[crow];
            while (q->right!=NULL&&q->right->column < p->column){       //�ҵ�����λ��
                q=q->right;
            }
            p->right=q->right;
            q->right=p;
        }
        if(t->chead[cbrow] == NULL||t->chead[cbrow]->row > p->row){         //ά����
            p->down=t->chead[cbrow];
            t->chead[cbrow]=p;
        } else{
            OLNode*   q=t->chead[cbrow];
            while (q->down!=NULL&&q->down->row < p->row){
                q=q->down;
            }
            p->down=q->down;
            q->down=p;
        }
    }
}
/*��ӡʮ������*/
void PrintSMatrix_OL(CrossList  t){
    for (int i = 0; i < t.mu; ++i) {    //������
        printf("[");
        OLNode  *p=t.rhead[i];
        for (int j = 0; j < t.nu-1; ++j) {      //Ϊ��֤û�ж���ո�ֻ��ӡ����nu-2�У��ӵ�0�м�����
            if(p==NULL){        //��ǰ�ڵ�ΪNULL��ӡ0
                printf("0 ");
            } else{
                printf("%d ",p->e);     //��NULL��ӡֵ�����ͷŸýڵ㣬p������һ���ڵ�
                OLNode  *gc=p;
                p=p->right;
                free(gc);
            }

        }
        if(p==NULL){    //��ӡÿһ�е����һ����
            printf("0]\n");
        } else{
            printf("%d]\n",p->e);
            free(p);
        }
    }

}
/*��Ԫ������߼�ά��*/
void   located(RLSMatrix *r){
    int j = 0;
    for (int i = 0; i < r->mu; ++i) {       //ÿһ��
        for (; j < r->tu; ++j) {
            if(r->data[j].row>=i){       //�ҵ�ÿһ�е�һ��Ԫ����data�����е��±꣬����һ��ȫΪ0�ҵ��ľ�����һ������Ԫ����data�����е��±꣬���Ϊtu-1
                break;
            }
        }
        r->rpos[i] = j;

    }
}
/*��ӡ��Ԫ��*/

void PrintMatrix(RLSMatrix  *r){
    for (int i = 0; i < r->mu; ++i) {           //��ÿһ��
        int p = r->rpos[i];         //�ҵ����е�һ������Ԫ����data�����е��±�
        printf("[");
        int t;
        if(i<r->mu-1){          //�ҵ���һ�е�һ������Ԫ����data�����е��±�
            t=r->rpos[i+1];
        } else{
            t=r->tu;            //�����һ�����ӡ������
        }
        for (int j = 0; j < r->nu-1; ++j) {     //Ϊ��֤û�ж���ո�ֻ��ӡ����nu-2�У��ӵ�0�м�����
            if( p < t && r->data[p].column == j) {      //����Ԫ��������Ӧ���ӡ
                printf("%d ",r->data[p].e);
                p++;
            } else{
                printf("0 ");               //��������Ӧ���߷���Ԫ�ش�ӡ������ӡ0
            }
        }
        if( p < t && r->data[p].column == r->nu-1) {       //��ӡ���һλ
            printf("%d",r->data[p].e);
        } else{
            printf("0");
        }
        printf("]\n");
    }
}

int comp(int    a,int b){       //�ȽϺ���
    if(a==b){
        return 0;
    }
    if(a<b){
        return -1;
    }
    if(a>b){
        return 1;
    }
}
/*��Ԫ���(û��ά�����߼�)*/
void add (RLSMatrix r1,RLSMatrix r2,RLSMatrix *r3){
    r3->mu=r1.mu;
    r3->nu=r1.nu;
    r3->tu=0;
    int i,j;
    i=j=0;
    while (i<r1.tu && j<r2.tu){         //r1,r2û�б�������
        switch (comp(r1.data[i].row,r2.data[j].row)){
            case -1:{
                r3->data[r3->tu]=r1.data[i];//������С���ȸ�ֵ
                r3->tu++;
                i++;
                break;
            }
            case 0:{
                switch (comp(r1.data[i].column,r2.data[j].column)){
                    case -1:{
                        r3->data[r3->tu]=r1.data[i];//����С���ȸ�ֵ
                        r3->tu++;
                        i++;
                        break;
                    }
                    case 0:{
                        int sum=r1.data[i].e+r2.data[j].e;
                        if(sum!=0){
                            r3->data[r3->tu].e=sum; //������ͬ���
                            r3->data[r3->tu].row=r1.data[i].row;
                            r3->data[r3->tu].column=r1.data[i].column;
                            r3->tu++;
                        }
                        i++;
                        j++;
                        break;

                    }
                    case 1:{
                        r3->data[r3->tu]=r2.data[j];
                        r3->tu++;
                        j++;
                        break;
                    }
                }
                break;
            }
            case 1:{
                r3->data[r3->tu]=r2.data[j];
                r3->tu++;
                j++;
                break;
            }
        }
    }
    while (i<r1.tu){    //û�м���ӽ���
        r3->data[r3->tu]=r1.data[i];
        i++;
        r3->tu++;
    }
    while (j<r2.tu){
        r3->data[r3->tu]=r2.data[j];
        j++;
        r3->tu++;
    }
}
/*�����ͼӷ��㷨����*/
void sub (RLSMatrix r1,RLSMatrix r2,RLSMatrix *r3){
    r3->mu=r1.mu;
    r3->nu=r1.nu;
    r3->tu=0;
    int i,j;
    i=j=0;
    while (i<r1.tu && j<r2.tu){
        switch (comp(r1.data[i].row,r2.data[j].row)){
            case -1:{
                r3->data[r3->tu]=r1.data[i];
                r3->tu++;
                i++;
                break;
            }
            case 0:{
                switch (comp(r1.data[i].column,r2.data[j].column)){
                    case -1:{
                        r3->data[r3->tu]=r1.data[i];
                        r3->tu++;
                        i++;
                        break;
                    }
                    case 0:{
                        int cha=r1.data[i].e-r2.data[j].e;
                        if(cha!=0){     //�жϲ��0
                            r3->data[r3->tu].e=cha;
                            r3->data[r3->tu].row=r1.data[i].row;
                            r3->data[r3->tu].column=r1.data[i].column;
                            r3->tu++;
                        }
                        i++;
                        j++;
                        break;

                    }
                    case 1:{
                        r3->data[r3->tu].e=-r2.data[j].e;
                        r3->data[r3->tu].row=r2.data[j].row;
                        r3->data[r3->tu].column=r2.data[j].column;
                        r3->tu++;
                        j++;
                        break;
                    }
                }
                break;
            }
            case 1:{
                r3->data[r3->tu].e=-r2.data[j].e;
                r3->data[r3->tu].row=r2.data[j].row;
                r3->data[r3->tu].column=r2.data[j].column;
                r3->tu++;
                j++;
                break;
            }
        }
    }
    while (i<r1.tu){
        r3->data[r3->tu]=r1.data[i];
        i++;
        r3->tu++;
    }
    while (j<r2.tu){
        r3->data[r3->tu].e=-r2.data[j].e;
        r3->data[r3->tu].row=r2.data[j].row;
        r3->data[r3->tu].column=r2.data[j].column;
        j++;
        r3->tu++;
    }
}
/*��Ԫ��˷�*/
void multiplied(RLSMatrix   r1,RLSMatrix r2,RLSMatrix   *r3){
    r3->mu=r1.mu;
    r3->nu=r2.nu;
    r3->tu=0;
    if(r1.tu*r2.tu != 0){
        int tp;
        int t;
        for (int arow = 0; arow < r3->mu; ++arow) {
            int ctemp[r3->nu];      //��ʱ�洢ÿһ�е�������
            for (int j = 0; j < r3->nu; ++j) {
                ctemp[j]=0;         //����
            }
            r3->rpos[arow]=r3->tu;//ά�����߼�
            if(arow<r1.mu-1){
                tp=r1.rpos[arow+1];       //�ҵ���һ�еĵ�һ��Ԫ����data�����е��±�
            } else{
                tp=r1.tu;
            }
            for (int p = r1.rpos[arow]; p < tp; ++p) {
                int brow=r1.data[p].column;
                if(brow<r2.mu-1){
                    t=r2.rpos[brow+1];
                } else{
                    t=r2.tu;
                }
                for (int q = r2.rpos[brow]; q < t; ++q) {
                    int cool=r2.data[q].column;
                    ctemp[cool]=r1.data[p].e*r2.data[q].e+ctemp[cool];//���г˷�����
                }
            }
            for (int i = 0; i < r3->nu; ++i) {
                if(ctemp[i]!=0){        //����������
                    r3->data[r3->tu].row=arow;
                    r3->data[r3->tu].column=i;
                    r3->data[r3->tu].e=ctemp[i];
                    r3->tu++;
                }
            }
        }
    }
}
int main() {
        while (1){
        printf("Please input Matrix1 row , column and counts(not zero)\n");
        RLSMatrix   R1;
        scanf("%d%d%d",&R1.mu,&R1.nu,&R1.tu);
        printf("Please input Matrix1's datas and row and column by row\n");
        for (int i = 0; i < R1.tu; ++i) {
            scanf("%d%d%d",&R1.data[i].row,&R1.data[i].column,&R1.data[i].e);
        }
        located(&R1);
        PrintMatrix(&R1);
        printf("Please input Matrix2 row , column and counts(not zero)\n");
        RLSMatrix   R2;
        scanf("%d%d%d",&R2.mu,&R2.nu,&R2.tu);
        printf("Please input Matrix2's datas and row and column by row\n");
        CrossList   R4,R5,R6,R7;
        for (int i = 0; i < R2.tu; ++i) {
            scanf("%d%d%d",&R2.data[i].row,&R2.data[i].column,&R2.data[i].e);
        }
        located(&R2);
        PrintMatrix(&R2);
        int menu;
        while (1){
            printf("Please input calculation: 1:+ 2:- 3:* 4:out 5:OL_CrossList \n");
            scanf("%d",&menu);
            RLSMatrix   R3;
            switch (menu){
                case 1:{
                    if(R1.mu == R2.mu&&R1.nu == R2.nu){
                        add(R1,R2,&R3);
                        located(&R3);
                        PrintMatrix(&R3);
                    }else{
                        printf("The Matrixs can't be added");
                    };
                    break;
                }
                case 2:{
                    if(R1.mu == R2.mu&&R1.nu == R2.nu){
                        sub(R1,R2,&R3);
                        located(&R3);
                        PrintMatrix(&R3);
                    }else{
                        printf("The Matrixs can't be subctruted");
                    };
                    break;
                }
                case 3:{
                    if(R1.nu != R2.mu){
                        printf("The Matrixs can't be multoplied");
                    } else{
                        multiplied(R1,R2,&R3);
                        PrintMatrix(&R3);
                    }
                    break;

                }
                case 4:{
                    continue;
                }
                case 5:{
                    CreateSMatrix_OL(R1,&R4);
                    CreateSMatrix_OL(R2,&R5);
                    PrintSMatrix_OL(R4);
                    PrintSMatrix_OL(R5);
                    break;
                }
                default:{
                    printf("input error\n");
                    continue;
                }
            }
        }

    }
    return 0;

}