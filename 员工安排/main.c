#include <stdio.h>
struct name{//储存员工姓名的结构体
    char a[20];
};
struct name staff[1000];
void combine(struct name a[], int n, int m, int b[], int M)
{
    int i, j;
    for (i = n; i >= m; i--)
    {
        b[m - 1] = i - 1;//先从n个数中取一个
        if (m > 1){//以此类推，直到只用取一个数
            combine(a, i - 1, m - 1, b, M);//再从取出的这个数序列前面的数中取一个
        }
        else
        {
            for (j = M - 1; j >= 0; j--){
                printf("%s ", a[b[j]].a);//打印结果
            }
            printf("\n");
        }
    }
}
int main(){
    int n,m;
    printf("请输入员工数量(换行后输入员工姓名):");
    scanf("%d",&n);
    getchar();//接收换行
    for(int i=0;i<n;i++){
        gets(staff[i].a);
    }
    int b[n];
    printf("请输入工作需要人数:");
    scanf("%d",&m);
    combine(staff,n,m,b,m);
}