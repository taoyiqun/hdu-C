#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define productsize 10     //储存空间初始分配量
#define pulssize    2       //储存空间分配增量
typedef struct Go {
    int x;
    int y;
    int a;
}Go;
typedef struct Stack{             //栈的结构体
    Go *base;        //栈底指针指向头元素起始位置
    Go *top;         //栈顶指针指向尾元素起始位置
    int stacksize;
}Stack;
/*构造一个栈*/
int ProductStack(Stack   *S){
    (*S).base=(int    *)malloc(productsize* sizeof(Go));
    if(!(*S).base){
        printf("构造栈失败");
        exit(0);
    }
    (*S).top=(*S).base;
    (*S).stacksize=productsize;
    return 1;
}
/*压栈*/
int Push(Stack   *S, Go e){
    if((*S).top - (*S).base >= (*S).stacksize) // 栈满，追加存储空间
    {
        (*S).base = (Stack    *)realloc((*S).base, ((*S).stacksize + pulssize) * sizeof(Go));
        if( !(*S).base ){
            exit(0); // 存储分配失败
        }
        (*S).top = (*S).base+(*S).stacksize;
        (*S).stacksize +=pulssize;
    }
    *((*S).top)=e;          //赋值
    (*S).top++;          //栈顶指针往后移一位
    return 1;
}
/*出栈*/
int Pop(Stack *S, Go *e) {
    if((*S).top == (*S).base){//栈为空
        printf("Stack is null\n");
        return 0;
    }

    ((*S).top)--;          //栈顶指针往前移一位
    *e=*((*S).top);          //出栈
    return 1;
}
int StackEmpty(Stack S){
    if(S.base == S.top) {
         return 1;	//空
    }
    else{
        return 0;
    }
}
void DestroyStack(Stack *S){
    S->base=S->top;
    S->stacksize=0;
}
int num[8][8] = {
        {2,3,4,4,4,4,3,2},//初始化棋盘权值，标记为每个位置所能跳的方向
        {3,4,6,6,6,6,4,3},
        {4,6,8,8,8,8,6,4},
        {4,6,8,8,8,8,6,4},
        {4,6,8,8,8,8,6,4},
        {4,6,8,8,8,8,6,4},
        {3,4,6,6,6,6,4,3},
        {2,3,4,4,4,4,3,2},};
int broad[8][8];
const int HTryx[]={-2,-1,1,2,2,1,-1,-2};
const int HTryy[]={1,2,2,1,-1,-2,-2,-1};
void print() {
    for(int i = 0; i < 8; i++)  {
        for(int j = 0; j < 8; j++){
            printf("%3d",broad[i][j]);
        }
        printf("\n");
    }
}
Go Next(Go *now){
    Go next,temp;
    next.x = -1;
    next.y = -1;
    temp.a=0;
    int i;
    for(i=now->a;i < 8; i++) {
        temp.x = now->x + HTryx[i];
        temp.y = now->y + HTryy[i];
        if(temp.x < 0 || temp.x > 7 || temp.y < 0 || temp.y > 7 || broad[temp.x][temp.y]) continue;
        if(next.x == -1 && next.y == -1) {
            next = temp;
            now->a=i;
        }
        else if( num[next.x][next.y] > num[ temp.x][temp.y]) {
            next= temp;
            now->a=i;
        }
    }
    if(next.x == -1 && next.y == -1){
        now->a=8;
        return *now;
    }
    return next;

}
void Try(Go start){
    Stack   S;
    Go now,next;
    int step=1;
    now=start;
    ProductStack(&S);
    memset(broad,0, sizeof(broad));
    do{
        if(!broad[now.x][now.y]){
           printf("step %d (%d,%d)successfully\n",step,now.x,now.y);
            broad[now.x][now.y]=step;
            next=Next(&now);
            Push(&S,now);
            if(step==64){
                print();
                DestroyStack(&S);
                return;
            }
            now=next;
            step++;
        } else{
            step--;
            printf("step %d (%d,%d) need return\n",step,now.x,now.y);
            broad[now.x][now.y]=0;
            Pop(&S,&now);
            while (Pop(&S,&now)&&now.a>=7) {
                step--;
                broad[now.x][now.y]=0;
                printf("step %d need return\n", step);
            }
            now.a++;
            next=Next(&now);
            Push(&S,now);
            now=next;

        }
    }while (!StackEmpty(S));
}

int main() {
    Go    start;
    printf("Please input the start\n");
    scanf("%d%d",&start.x,&start.y);
    start.a=0;
    Try(start);
}