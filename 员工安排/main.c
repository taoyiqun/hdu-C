#include <stdio.h>
struct name{//����Ա�������Ľṹ��
    char a[20];
};
struct name staff[1000];
void combine(struct name a[], int n, int m, int b[], int M)
{
    int i, j;
    for (i = n; i >= m; i--)
    {
        b[m - 1] = i - 1;//�ȴ�n������ȡһ��
        if (m > 1){//�Դ����ƣ�ֱ��ֻ��ȡһ����
            combine(a, i - 1, m - 1, b, M);//�ٴ�ȡ�������������ǰ�������ȡһ��
        }
        else
        {
            for (j = M - 1; j >= 0; j--){
                printf("%s ", a[b[j]].a);//��ӡ���
            }
            printf("\n");
        }
    }
}
int main(){
    int n,m;
    printf("������Ա������(���к�����Ա������):");
    scanf("%d",&n);
    getchar();//���ջ���
    for(int i=0;i<n;i++){
        gets(staff[i].a);
    }
    int b[n];
    printf("�����빤����Ҫ����:");
    scanf("%d",&m);
    combine(staff,n,m,b,m);
}