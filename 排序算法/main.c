#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <math.h>

int a[100];
int b[1000];
int c[10000];
int d[100000];
int e[1000000];
/*冒泡排序，n代表需要排序个数*/
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
/*插入排序，n代表需要排序个数*/
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
/*快速排序，一次调用*/
int partition(int a[],int p, int    r){
    int temp;
    while (p<r){
        //进行右侧扫描
        while(p<r&&a[p]<a[r]){
            r--;
        }
        if (p<r){
            temp= a[p];
            a[p] = a[r];
            a[r] = temp;
            p++;
        }
        //进行左侧扫描
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
/*快速排序*/
void    quick(int   a[], int    p, int  r){
    if(p<r){
       int q=partition(a,p,r);
       quick(a,p,q-1);
       quick(a,q+1,r);
    } else{
        return;
    }
}
/*产生随机数组*/
void    product(int a[],int n){
    srand((unsigned)time(NULL));
    for(int i=0;i<n;i++){
        a[i]=rand();
    }
}
/*任意交换数组中的两个值得到基本有序的数组*/
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
    double  start,finish;//开始和结束时间
   start=clock();
    Bubble(a,100);
    finish=clock();
    printf( "气泡排序对规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);//任意交换排好序的数组中的两个值得到基本有序数组
    start=clock();
    Bubble(a,100);
    finish=clock();
    printf( "气泡排序对排序后的规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    Bubble(b,1000);
    finish=clock();
    printf( "气泡排序对规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    Bubble(b,1000);
    finish=clock();
    printf( "气泡排序对排序后的规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(c,10000);
    finish=clock();
    printf( "气泡排序对规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    Bubble(c,10000);
    finish=clock();
    printf( "气泡排序对排序后的规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(d,100000);
    finish=clock();
    printf( "气泡排序对规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    Bubble(d,100000);
    finish=clock();
    printf( "气泡排序对排序后的规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    Bubble(e,1000000);
    finish=clock();
    printf( "气泡排序对规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    Bubble(e,1000000);
    finish=clock();
    printf( "气泡排序对排序后的规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    product(a,100);
    product(b,1000);
    product(c,10000);
    product(d,100000);
    product(e,1000000);
    start=clock();
    insertion(a,100);
    finish=clock();
    printf( "插入排序对规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);
    start=clock();
    insertion(a,100);
    finish=clock();
    printf( "插入排序对排序后的规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    insertion(b,1000);
    finish=clock();
    printf( "插入排序对规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    insertion(b,1000);
    finish=clock();
    printf( "插入排序对排序后的规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(c,10000);
    finish=clock();
    printf( "插入排序对规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    insertion(c,10000);
    finish=clock();
    printf( "插入排序对排序后的规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(d,100000);
    finish=clock();
    printf( "插入排序对规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    insertion(d,100000);
    finish=clock();
    printf( "插入排序对排序后的规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    insertion(e,1000000);
    finish=clock();
    printf( "插入排序对规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    insertion(e,1000000);
    finish=clock();
    printf( "插入排序对排序后的规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    product(a,100);
    product(b,1000);
    product(c,10000);
    product(d,100000);
    product(e,1000000);
    start=clock();
    quick(a,0,99);
    finish=clock();
    printf( "快速排序对规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(a,100);
    start=clock();
    quick(a,0,99);
    finish=clock();
    printf( "快速排序对排序后的规模100的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    /*for(int i=0;i<100;i++){
        printf("%d ",a[i]);
    }*/
    start=clock();
    quick(b,0,999);
    finish=clock();
    printf( "快速排序对规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(b,1000);
    start=clock();
    quick(b,0,999);
    finish=clock();
    printf( "快速排序对排序后的规模1000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(c,0,9999);
    finish=clock();
    printf( "快速排序对规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(c,10000);
    start=clock();
    quick(c,0,9999);
    finish=clock();
    printf( "快速排序对排序后的规模10000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(d,0,99999);
    finish=clock();
    printf( "快速排序对规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(d,100000);
    start=clock();
    quick(d,0,99999);
    finish=clock();
    printf( "快速排序对排序后的规模100000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    start=clock();
    quick(e,0,999999);
    finish=clock();
    printf( "快速排序对规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    swap(e,1000000);
    start=clock();
    quick(e,0,999999);
    finish=clock();
    printf( "快速排序对排序后的规模1000000的数组所需时间为%f 秒\n",(finish - start) / CLOCKS_PER_SEC);
    return  0;
    int a=1,b=2,c=3;
    int area=sqrt((1/16)*(a-3));
    int *ak=(int     *)malloc(sizeof(int)*2);
    ak[1]=1;
    *(ak+1)=3;
}
