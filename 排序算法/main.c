#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>

int a[100];
int b[1000];
int c[10000];
int d[100000];
int e[1000000];
/*ð������n������Ҫ�������*/
void    Bubble(int   a[],int n){
    int i=0;
    int j=0;
    int temp=0;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}
/*��������n������Ҫ�������*/
void    insertion(int   a[],int n){
    int key;
    int i;
    for(int j=1;j<n;j++){
        i=j-1;
        key=a[j];
        while(i>=0&&a[i]>key){
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=key;
    }
}
/*��������һ�ε���*/
int partition(int a[],int p, int    r){
    int temp;
    while (p<r){
        //�����Ҳ�ɨ��
        while(p<r&&a[p]<a[r]){
            r--;
        }
        if (p<r){
            temp= a[p];
            a[p] = a[r];
            a[r] = temp;
            p++;
        }
        //�������ɨ��
        while(p < r&&a[p] <= a[r]){
            p++;
        }
        if(p<r){
            temp = a[p];
            a[p] = a[r];
            a[r] = temp;
            r--;
        }
    }
    return p;
}
/*��������*/
void    quick(int   a[], int    p, int  r){
    if(p<r){
       int q=partition(a,p,r);
       quick(a,p,q-1);
       quick(a,q+1,r);
    } else{
        return;
    }
}
/*�����������*/
void    product(int a[],int n){
    srand((unsigned)time(NULL));
    for(int i=0;i<n;i++){
        a[i]=rand();
    }
}
/*���⽻�������е�����ֵ�õ��������������*/
void swap(int   a[], int    n){
    srand((unsigned)time(NULL));
    int temp1=rand()%n;
    int temp2=rand()%n;
    int temp=0;
    temp=a[temp1];
    a[temp1]=a[temp2];
    a[temp2]=temp;

}
int main()
{   product(a,100);
    product(b,1000);
    product(c,10000);
    product(d,100000);
    product(e,1000000);
    double  start,finish;//��ʼ�ͽ���ʱ��
   start=clock();
    Bubble(a,100);
    finish=clock();
    printf( "��������Թ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);//���⽻���ź���������е�����ֵ�õ�������������
    start=clock();
    Bubble(a,100);
    finish=clock();
    printf( "��������������Ĺ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    Bubble(b,1000);
    finish=clock();
    printf( "��������Թ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    Bubble(b,1000);
    finish=clock();
    printf( "��������������Ĺ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(c,10000);
    finish=clock();
    printf( "��������Թ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    Bubble(c,10000);
    finish=clock();
    printf( "��������������Ĺ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(d,100000);
    finish=clock();
    printf( "��������Թ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    Bubble(d,100000);
    finish=clock();
    printf( "��������������Ĺ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(e,1000000);
    finish=clock();
    printf( "��������Թ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    Bubble(e,1000000);
    finish=clock();
    printf( "��������������Ĺ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    product(a,100);
    product(b,1000);
    product(c,10000);
    product(d,100000);
    product(e,1000000);
    start=clock();
    insertion(a,100);
    finish=clock();
    printf( "��������Թ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);
    start=clock();
    insertion(a,100);
    finish=clock();
    printf( "��������������Ĺ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    insertion(b,1000);
    finish=clock();
    printf( "��������Թ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    insertion(b,1000);
    finish=clock();
    printf( "��������������Ĺ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(c,10000);
    finish=clock();
    printf( "��������Թ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    insertion(c,10000);
    finish=clock();
    printf( "��������������Ĺ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(d,100000);
    finish=clock();
    printf( "��������Թ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    insertion(d,100000);
    finish=clock();
    printf( "��������������Ĺ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(e,1000000);
    finish=clock();
    printf( "��������Թ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    insertion(e,1000000);
    finish=clock();
    printf( "��������������Ĺ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    product(a,100);
    product(b,1000);
    product(c,10000);
    product(d,100000);
    product(e,1000000);
    start=clock();
    quick(a,0,99);
    finish=clock();
    printf( "��������Թ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);
    start=clock();
    quick(a,0,99);
    finish=clock();
    printf( "��������������Ĺ�ģ100����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    quick(b,0,999);
    finish=clock();
    printf( "��������Թ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    quick(b,0,999);
    finish=clock();
    printf( "��������������Ĺ�ģ1000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(c,0,9999);
    finish=clock();
    printf( "��������Թ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    quick(c,0,9999);
    finish=clock();
    printf( "��������������Ĺ�ģ10000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(d,0,99999);
    finish=clock();
    printf( "��������Թ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    quick(d,0,99999);
    finish=clock();
    printf( "��������������Ĺ�ģ100000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(e,0,999999);
    finish=clock();
    printf( "��������Թ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    quick(e,0,999999);
    finish=clock();
    printf( "��������������Ĺ�ģ1000000����������ʱ��Ϊ%f ��\n",(finish - start) / CLOCKS_PER_SEC);
    return  0;
    int a=1,b=2,c=3;
    int area=sqrt((1/16)*(a-3));
    int *ak=(int     *)malloc(sizeof(int)*2);
    ak[1]=1;
    *(ak+1)=3;
}
