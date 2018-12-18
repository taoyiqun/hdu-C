#include <stdio.h>
#include <search.h>
#include <stdlib.h>

typedef struct OLNode{      //十字链表节点
    int row;               //所在行
    int column;            //所在列
    int e;                 //数值
    struct OLNode  *right,*down;      //right指向该节点同一行的下一个节点，down指向该节点同一列的下一个节点
}OLNode,*OLink;
typedef struct CrossList{           //十字链表
    int mu,nu,tu;                   //mu是总行数 nu为总列数 tu为非零元素总数
    OLink *rhead,*chead;            //rhead指向各行节点的头，chead指向各列节点的头
}CrossList;
typedef struct Triple{              //三元组节点
    int row;      //所在行
    int column;   //所在列
    int e;       //数据
}Triple;
typedef struct RLSMatrix{         //三元组
    Triple  data[410];          //储存非零元素数据的数组
    int rpos[25];                //行逻辑数组 rops[i]储存第i行非零元素在data数组中储存的下标
    int mu,nu,tu;                  //mu是总行数 nu为总列数 tu为非零元素总数
}RLSMatrix;
/*三元组转换为十字链表*/
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
        OLNode*  p; //生成新的节点
        if(!(p=(OLNode *)malloc(sizeof(OLNode)))){
            exit(-1);
        }
        p->column=r.data[i].column;
        p->row=r.data[i].row;
        p->e=r.data[i].e;
        int crow=r.data[i].row;     //crow为所在行
        int cbrow=r.data[i].column; //cbrow为所在列
        if(t->rhead[crow] == NULL||t->rhead[crow]->column > p->column){  //维护行
            p->right=t->rhead[crow];        //在第一个节点前插入新节点
            t->rhead[crow]=p;
        } else{             //在每一个节点之后插入新节点
            OLNode*   q=t->rhead[crow];
            while (q->right!=NULL&&q->right->column < p->column){       //找到插入位置
                q=q->right;
            }
            p->right=q->right;
            q->right=p;
        }
        if(t->chead[cbrow] == NULL||t->chead[cbrow]->row > p->row){         //维护列
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
/*打印十字链表*/
void PrintSMatrix_OL(CrossList  t){
    for (int i = 0; i < t.mu; ++i) {    //所有行
        printf("[");
        OLNode  *p=t.rhead[i];
        for (int j = 0; j < t.nu-1; ++j) {      //为保证没有多余空格只打印到第nu-2列（从第0列计数）
            if(p==NULL){        //当前节点为NULL打印0
                printf("0 ");
            } else{
                printf("%d ",p->e);     //非NULL打印值并且释放该节点，p移向下一个节点
                OLNode  *gc=p;
                p=p->right;
                free(gc);
            }

        }
        if(p==NULL){    //打印每一行的最后一个数
            printf("0]\n");
        } else{
            printf("%d]\n",p->e);
            free(p);
        }
    }

}
/*三元组的行逻辑维护*/
void   located(RLSMatrix *r){
    int j = 0;
    for (int i = 0; i < r->mu; ++i) {       //每一行
        for (; j < r->tu; ++j) {
            if(r->data[j].row>=i){       //找到每一行第一个元素在data数组中的下标，若这一行全为0找到的就是下一个非零元素在data数组中的下标，最大为tu-1
                break;
            }
        }
        r->rpos[i] = j;

    }
}
/*打印三元组*/

void PrintMatrix(RLSMatrix  *r){
    for (int i = 0; i < r->mu; ++i) {           //对每一行
        int p = r->rpos[i];         //找到该行第一个非零元素在data数组中的下标
        printf("[");
        int t;
        if(i<r->mu-1){          //找到下一行第一个非零元素在data数组中的下标
            t=r->rpos[i+1];
        } else{
            t=r->tu;            //是最后一行则打印到结束
        }
        for (int j = 0; j < r->nu-1; ++j) {     //为保证没有多余空格只打印到第nu-2列（从第0列计数）
            if( p < t && r->data[p].column == j) {      //非零元素列数对应则打印
                printf("%d ",r->data[p].e);
                p++;
            } else{
                printf("0 ");               //列数不对应或者非零元素打印完毕则打印0
            }
        }
        if( p < t && r->data[p].column == r->nu-1) {       //打印最后一位
            printf("%d",r->data[p].e);
        } else{
            printf("0");
        }
        printf("]\n");
    }
}

int comp(int    a,int b){       //比较函数
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
/*三元组加(没有维护行逻辑)*/
void add (RLSMatrix r1,RLSMatrix r2,RLSMatrix *r3){
    r3->mu=r1.mu;
    r3->nu=r1.nu;
    r3->tu=0;
    int i,j;
    i=j=0;
    while (i<r1.tu && j<r2.tu){         //r1,r2没有遍历结束
        switch (comp(r1.data[i].row,r2.data[j].row)){
            case -1:{
                r3->data[r3->tu]=r1.data[i];//行数最小的先赋值
                r3->tu++;
                i++;
                break;
            }
            case 0:{
                switch (comp(r1.data[i].column,r2.data[j].column)){
                    case -1:{
                        r3->data[r3->tu]=r1.data[i];//列数小的先赋值
                        r3->tu++;
                        i++;
                        break;
                    }
                    case 0:{
                        int sum=r1.data[i].e+r2.data[j].e;
                        if(sum!=0){
                            r3->data[r3->tu].e=sum; //行列相同相加
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
    while (i<r1.tu){    //没有加完加结束
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
/*减法和加法算法类似*/
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
                        if(cha!=0){     //判断差不是0
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
/*三元组乘法*/
void multiplied(RLSMatrix   r1,RLSMatrix r2,RLSMatrix   *r3){
    r3->mu=r1.mu;
    r3->nu=r2.nu;
    r3->tu=0;
    if(r1.tu*r2.tu != 0){
        int tp;
        int t;
        for (int arow = 0; arow < r3->mu; ++arow) {
            int ctemp[r3->nu];      //暂时存储每一行的运算结果
            for (int j = 0; j < r3->nu; ++j) {
                ctemp[j]=0;         //清零
            }
            r3->rpos[arow]=r3->tu;//维护行逻辑
            if(arow<r1.mu-1){
                tp=r1.rpos[arow+1];       //找到下一行的第一个元素在data数组中的下标
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
                    ctemp[cool]=r1.data[p].e*r2.data[q].e+ctemp[cool];//进行乘法运算
                }
            }
            for (int i = 0; i < r3->nu; ++i) {
                if(ctemp[i]!=0){        //非零则置入
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