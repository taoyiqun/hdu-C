#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1   //不可执行
#define MAX_NAME 10    //顶点字符串的最大长度;
#define MAX_CLASS_NUM 100
#define MAX_VERTEX_NUM 100  //最多能存的课程名
typedef int Status; // Status是函数的返回类型；
typedef int InfoType;
typedef char VertexType[MAX_NAME]; //字符串类型;


typedef struct ArcNode{      //弧结构；
    int adjvex;       //该弧所指向的顶点的位置;
    struct ArcNode * nextarc;     //指向下一条弧的指针;
    InfoType * info;     //网的权值指针;
}ArcNode;      //表结点;
typedef struct VNode{
    VertexType data; //顶点信息;
    ArcNode *firstarc; //第一个表结点的地址,指向第一条依附该顶点的弧的指针;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertices,vertices2;    //分别存课程名和学分；
    int vexnum,arcnum;
    int kind;
}ALGraph;
Status LocateVex(ALGraph G,VertexType u){

    int i;
    for(i=0;i<G.vexnum;++i){
        if(strcmp(u, G.vertices[i].data)==0){
            return i;
        }
    }
    return INFEASIBLE;
}
Status CreateGraph(ALGraph *G){
    int i,j,k;
    VertexType v1,v2;  //顶点信息；
    ArcNode * p;        //指向第一条依附某顶点的弧的指针；

    printf("请输入教学计划的课程数: ");
    scanf("%d",&G->vexnum);
    printf("请输入课程先修关系数（弧的数目）: ");
    scanf("%d",&G->arcnum);
    printf("请输入%d个课程的代表值(如:c01):\n",G->vexnum);
    for(i=0;i<G->vexnum;++i) {
        scanf("%s",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;
    }
    printf("请输入%d个课程的学分值:\n",G->vexnum);
    for(i=0;i<G->vexnum;++i) {
        scanf("%s",&G->vertices2[i].data);
    }
    printf("请顺序输入每条弧的弧尾和弧头(以空格作为间隔):\n");
    for(k=0;k<G->arcnum;++k) {
        scanf("%s%s",v1,v2);
        i=LocateVex(*G,v1);
        j=LocateVex(*G,v2);
        p = (ArcNode*)malloc(sizeof(ArcNode));  //新建一个节点；
        p->adjvex = j;
        p->info = NULL;
        p->nextarc = G->vertices[i].firstarc;
        G->vertices[i].firstarc = p;
    }
    return OK;
}
void Display(ALGraph G){
    int i;
    ArcNode * p;
    printf("有向图\n");
    printf("%d个顶点：\n",G.vexnum);
    for(i=0;i<G.vexnum;++i){
        printf("%s\n",G.vertices[i].data);
    }
    printf("\n%d条弧:\n",G.arcnum);
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            printf("%s→%s\n",G.vertices[i].data,G.vertices[p->adjvex].data);
            p=p->nextarc;
        }
        printf("\n");
    }
}


typedef int SElemType;
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
        printf("Stack is null\n");
        return 0;
    }

    ((*S).top)--;          //栈顶指针往前移一位
    *e=*((*S).top);          //出栈
    return TRUE;
}
int StackEmpty(Stack S){
    if(S.base == S.top) {
        return 1;	//空
    }
    else{
        return 0;
    }
}
void ClearStack(Stack *S) { //清空栈的操作
    S->top=S->base;
}


typedef int pathone[MAX_CLASS_NUM];
typedef int pathtwo[MAX_CLASS_NUM];
//求出节点的入度
void FindInDegree(ALGraph G,int indegree[]){
    int i;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++){
        indegree[i]=0;
    }
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}
Status zxf(ALGraph G){
    int z=0;
    for(int i=0; i < G.vexnum; i++){
        z += atoi(G.vertices2[i].data);//atoi是一个可以将字符串转成int型的库函数
    }
    return z;
}
Status TopologicalSort(ALGraph G, int   term_num,int credit_lim){
    FILE* fout;
    fout = fopen("data.out","w");
    int i,k,count,indegree[MAX_VERTEX_NUM];
    int has = 0;//是否是拓扑序列
    Stack S;
    pathone a;
    pathtwo b;
    ArcNode * p;
    FindInDegree(G,indegree);
    ProductStack(&S);
    for(i=0;i<G.vexnum;++i){
        if(!indegree[i]){
            Push(&S,i); //入度为0进栈，就是没有前驱
        }
    }
    count = 0;
    while(!StackEmpty(S)){
        Pop(&S,&i);
        a[i]=*G.vertices[i].data;  //课程名；
        b[i]=*G.vertices2[i].data;  //学分；
        printf("课程%s→学分%s  ",G.vertices[i].data,G.vertices2[i].data);

        ++count;
        for(p=G.vertices[i].firstarc; p; p=p->nextarc){
            k=p->adjvex;
            indegree[k]--;//该顶点的领接点入度减去1
            if(!(indegree[k])){
                Push(&S,k);//入度减为0入栈
            }
        }
    }
    if(count<G.vexnum){
        printf("此有向图有回路\n");
        return ERROR;
    } else{
        printf("为一个拓扑序列。\n\n");
        has=TRUE;
    }
    printf("请问您想使学生在各学期中的学习负担尽量均匀（输入1）\n");
    printf("还是想使课程尽可能地集中在前几个学期中（输入2）？\n");
    int pattern;
    printf("请选择(1 or 2):");
    scanf("%d",&pattern);
    fprintf(fout,"选择模式为%d\n",pattern);

    FindInDegree(G,indegree); //对各顶点求入度indegree[0..vernum-1] ;
    ClearStack(&S);
    printf("=====================================================\n");
    printf("教学计划如下：\n");
    int xq = 1; //学期数;
    int xfh;  //学分和；
    int now=0;
    int top = G.vexnum / term_num ;  //平均每学期课程数；
    int pjxf = zxf(G) / term_num ;  //每学期平均学分；
    while(xq <= term_num + 1){//多循环一学期判断是否所有课程安排完毕
        int result[20]; //某个学期的课程；
        int m = 0;
        xfh = 0;
        now=0;   //当前学期课程数 ；
        for(i=0;i<G.vexnum;++i){
            if(indegree[i]==0)
                Push(&S,i);
        }
        if(xq == term_num+1 && !StackEmpty(S)){
            printf("还有课程未安排！\n");
            fprintf(fout,"还有课程未安排！\n");
        }
        while(!StackEmpty(S) && xq <= term_num){
            int xf;
            Pop(&S,&i);  //弹出栈顶元素；
            xf = atoi(G.vertices2[i].data); //atoi:字符串转换成整型数, xf:学分;
            xfh = xfh+xf;
            now++;
            if(xfh > credit_lim){//超过学分限制
                ClearStack(&S);
                break;
            }
            if(pattern == 1){
                if(xq!=term_num&&now>top){
                    ClearStack(&S);
                    now = 0;
                    break;
                }
            }
            indegree[i]--; //减为-1,避免被再次计入；
            for(p=G.vertices[i].firstarc; p; p=p->nextarc){
                k=p->adjvex;
                indegree[k]--;
                if(indegree[k]==0){
                    Push(&S,k);
                }
            }
            result[m]=i;
            m++;
        }
        if(xq <= term_num){
            printf("第%d个学期的课程为：",xq);
            fprintf(fout,"第%d个学期的课程为：",xq);
            for(int j=0; j<m; j++){
                printf("课程%s ",G.vertices[result[j]].data);
                fprintf(fout,"课程%s ",G.vertices[result[j]].data);
            }
        }
        printf("\n");
        xq++;
        ClearStack(&S);
    }
    printf("=====================================================\n");
    fclose(fout);
    return OK;
}
int main(){
    printf("教学计划编制问题\n");
    while (1){
        ALGraph f;
        printf("请输入学期总数\n");
        int term;
        scanf("%d",&term);
        int credit_lim;
        printf("请输入每学期学分上限\n");
        scanf("%d",&credit_lim);
        CreateGraph(&f);
        Display(f);
        TopologicalSort(f,term,credit_lim);
        break;
    }
}
