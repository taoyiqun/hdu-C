#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1   //����ִ��
#define MAX_NAME 10    //�����ַ�������󳤶�;
#define MAX_CLASS_NUM 100
#define MAX_VERTEX_NUM 100  //����ܴ�Ŀγ���
typedef int Status; // Status�Ǻ����ķ������ͣ�
typedef int InfoType;
typedef char VertexType[MAX_NAME]; //�ַ�������;


typedef struct ArcNode{      //���ṹ��
    int adjvex;       //�û���ָ��Ķ����λ��;
    struct ArcNode * nextarc;     //ָ����һ������ָ��;
    InfoType * info;     //����Ȩֵָ��;
}ArcNode;      //����;
typedef struct VNode{
    VertexType data; //������Ϣ;
    ArcNode *firstarc; //��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ��;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct{
    AdjList vertices,vertices2;    //�ֱ��γ�����ѧ�֣�
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
    VertexType v1,v2;  //������Ϣ��
    ArcNode * p;        //ָ���һ������ĳ����Ļ���ָ�룻

    printf("�������ѧ�ƻ��Ŀγ���: ");
    scanf("%d",&G->vexnum);
    printf("������γ����޹�ϵ����������Ŀ��: ");
    scanf("%d",&G->arcnum);
    printf("������%d���γ̵Ĵ���ֵ(��:c01):\n",G->vexnum);
    for(i=0;i<G->vexnum;++i) {
        scanf("%s",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;
    }
    printf("������%d���γ̵�ѧ��ֵ:\n",G->vexnum);
    for(i=0;i<G->vexnum;++i) {
        scanf("%s",&G->vertices2[i].data);
    }
    printf("��˳������ÿ�����Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
    for(k=0;k<G->arcnum;++k) {
        scanf("%s%s",v1,v2);
        i=LocateVex(*G,v1);
        j=LocateVex(*G,v2);
        p = (ArcNode*)malloc(sizeof(ArcNode));  //�½�һ���ڵ㣻
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
    printf("����ͼ\n");
    printf("%d�����㣺\n",G.vexnum);
    for(i=0;i<G.vexnum;++i){
        printf("%s\n",G.vertices[i].data);
    }
    printf("\n%d����:\n",G.arcnum);
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            printf("%s��%s\n",G.vertices[i].data,G.vertices[p->adjvex].data);
            p=p->nextarc;
        }
        printf("\n");
    }
}


typedef int SElemType;
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
        printf("Stack is null\n");
        return 0;
    }

    ((*S).top)--;          //ջ��ָ����ǰ��һλ
    *e=*((*S).top);          //��ջ
    return TRUE;
}
int StackEmpty(Stack S){
    if(S.base == S.top) {
        return 1;	//��
    }
    else{
        return 0;
    }
}
void ClearStack(Stack *S) { //���ջ�Ĳ���
    S->top=S->base;
}


typedef int pathone[MAX_CLASS_NUM];
typedef int pathtwo[MAX_CLASS_NUM];
//����ڵ�����
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
        z += atoi(G.vertices2[i].data);//atoi��һ�����Խ��ַ���ת��int�͵Ŀ⺯��
    }
    return z;
}
Status TopologicalSort(ALGraph G, int   term_num,int credit_lim){
    FILE* fout;
    fout = fopen("data.out","w");
    int i,k,count,indegree[MAX_VERTEX_NUM];
    int has = 0;//�Ƿ�����������
    Stack S;
    pathone a;
    pathtwo b;
    ArcNode * p;
    FindInDegree(G,indegree);
    ProductStack(&S);
    for(i=0;i<G.vexnum;++i){
        if(!indegree[i]){
            Push(&S,i); //���Ϊ0��ջ������û��ǰ��
        }
    }
    count = 0;
    while(!StackEmpty(S)){
        Pop(&S,&i);
        a[i]=*G.vertices[i].data;  //�γ�����
        b[i]=*G.vertices2[i].data;  //ѧ�֣�
        printf("�γ�%s��ѧ��%s  ",G.vertices[i].data,G.vertices2[i].data);

        ++count;
        for(p=G.vertices[i].firstarc; p; p=p->nextarc){
            k=p->adjvex;
            indegree[k]--;//�ö������ӵ���ȼ�ȥ1
            if(!(indegree[k])){
                Push(&S,k);//��ȼ�Ϊ0��ջ
            }
        }
    }
    if(count<G.vexnum){
        printf("������ͼ�л�·\n");
        return ERROR;
    } else{
        printf("Ϊһ���������С�\n\n");
        has=TRUE;
    }
    printf("��������ʹѧ���ڸ�ѧ���е�ѧϰ�����������ȣ�����1��\n");
    printf("������ʹ�γ̾����ܵؼ�����ǰ����ѧ���У�����2����\n");
    int pattern;
    printf("��ѡ��(1 or 2):");
    scanf("%d",&pattern);
    fprintf(fout,"ѡ��ģʽΪ%d\n",pattern);

    FindInDegree(G,indegree); //�Ը����������indegree[0..vernum-1] ;
    ClearStack(&S);
    printf("=====================================================\n");
    printf("��ѧ�ƻ����£�\n");
    int xq = 1; //ѧ����;
    int xfh;  //ѧ�ֺͣ�
    int now=0;
    int top = G.vexnum / term_num ;  //ƽ��ÿѧ�ڿγ�����
    int pjxf = zxf(G) / term_num ;  //ÿѧ��ƽ��ѧ�֣�
    while(xq <= term_num + 1){//��ѭ��һѧ���ж��Ƿ����пγ̰������
        int result[20]; //ĳ��ѧ�ڵĿγ̣�
        int m = 0;
        xfh = 0;
        now=0;   //��ǰѧ�ڿγ��� ��
        for(i=0;i<G.vexnum;++i){
            if(indegree[i]==0)
                Push(&S,i);
        }
        if(xq == term_num+1 && !StackEmpty(S)){
            printf("���пγ�δ���ţ�\n");
            fprintf(fout,"���пγ�δ���ţ�\n");
        }
        while(!StackEmpty(S) && xq <= term_num){
            int xf;
            Pop(&S,&i);  //����ջ��Ԫ�أ�
            xf = atoi(G.vertices2[i].data); //atoi:�ַ���ת����������, xf:ѧ��;
            xfh = xfh+xf;
            now++;
            if(xfh > credit_lim){//����ѧ������
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
            indegree[i]--; //��Ϊ-1,���ⱻ�ٴμ��룻
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
            printf("��%d��ѧ�ڵĿγ�Ϊ��",xq);
            fprintf(fout,"��%d��ѧ�ڵĿγ�Ϊ��",xq);
            for(int j=0; j<m; j++){
                printf("�γ�%s ",G.vertices[result[j]].data);
                fprintf(fout,"�γ�%s ",G.vertices[result[j]].data);
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
    printf("��ѧ�ƻ���������\n");
    while (1){
        ALGraph f;
        printf("������ѧ������\n");
        int term;
        scanf("%d",&term);
        int credit_lim;
        printf("������ÿѧ��ѧ������\n");
        scanf("%d",&credit_lim);
        CreateGraph(&f);
        Display(f);
        TopologicalSort(f,term,credit_lim);
        break;
    }
}
