#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define MaxDim 5        //数组维数最大值
#define ElemType int
#define ERROR -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define OK 1

typedef struct {
    ElemType    *base;      //数组元素基地址
    int dim;                //维数
    int *bounds;            //数组维界基址
    int *constants;         //映像函数常量基址
    int count;
}Array;
int InitArray(Array *A){
    int dim;
    printf("请输入数组维数\n");
    scanf("%d",&dim);
    while (dim<1||dim>MaxDim){
        printf("维数错误，重新输入\n");
        scanf("%d",&dim);
    }
    A->dim=dim;
    A->bounds=(int*)malloc(dim* sizeof(int));
    if(!A->bounds)  {
        printf("维界内存分配失败\n");
        exit(OVERFLOW);

    }
    //若各维长度合法，存入A.bounds，算出总元素个数elemtotal
    int elemtotal=1;
    printf("请输入各维长度\n");
    for (int i = 0; i < dim; ++i) {
        scanf("%d",&A->bounds[i]);
        if(A->bounds[i]<0){
            printf("维数输入错误\n");
            return UNDERFLOW;
        }
        elemtotal=elemtotal*A->bounds[i];
    }
    A->count=elemtotal;
    A->base=(ElemType*)malloc(elemtotal* sizeof(ElemType));
    if(!A->base){
        printf("数组元素内存分配失败\n");
        exit(OVERFLOW);
    }
    printf("按行为主序输入%d个元素\n",A->count);
    for (int j = 0; j <A->count ; ++j) {
        scanf("%d",&A->base[j]);
    }
    //求映象函数的常数ci，并存入A.constants[i-1],i=1,...,dim
    A->constants=(int   *)malloc(dim* sizeof(int));
    if(!A->constants)exit(OVERFLOW);
    A->constants[dim-1]=1;          //L=1,指针的增减以元素的大小为单位
    for(int i=dim-2;i>=0;--i){
        A->constants[i]=A->bounds[i+1]*A->constants[i+1];
    }
    return OK;
}
int DestroyArray(Array  *A){
    if(!A->base){
        return ERROR;
    }
    free(A->base);
    A->base=NULL;
    if(!A->bounds){
        return ERROR;
    }
    free(A->bounds);
    A->bounds=NULL;
    if(A->constants){
        return ERROR;
    }
    free(A->constants);
    A->constants=NULL;
    return OK;
}
int Locate(Array    A, int *off){
    //若ap指示的各下标值合法，则求出该元素在A中的相对地址off
    *off=0;

    printf("请输入要操作的位置\n");
    for (int i = 0; i < A.dim; ++i) {
        int ind;
        scanf("%d",&ind);
        if(ind<0||ind>=A.bounds[i]){
            printf("下标越界\n");
            return OVERFLOW;
        }
        *off=*off+A.constants[i]*ind;
    }
    return OK;
}
int Vaule(Array A, ElemType *e){
    //A是n维数组，e为元素变量，随后是n个下标值。
    //若各个下标不超界，则e赋值为指定的A的元素值，并返回OK。
    int  off;
    int result=Locate(A,&off);
    if(result<=0){
        return result;
    }
    *e=*(A.base+off);
    return OK;
}
int Assign(Array    *A,ElemType e){
    //A是n维数组，e为元素变量，随后是n个下标值
    //若下标不越界，则将e的值赋给所指定的A的元素，并返回OK

    int  off;
    int result=Locate(*A,&off);
    if(result<=0){
        return result;
    }
    *(A->base+off)=e;
    return OK;

}
int Copy(Array A,Array *B){
    B->dim=A.dim;
    B->count=A.count;
    B->base=(ElemType*)malloc(A.count*sizeof(ElemType));
    B->constants=(int*)malloc(A.dim* sizeof(int));
    B->bounds=(int*)malloc(A.dim* sizeof(int));
    memcpy(B->base,A.base, A.count*sizeof(ElemType));
    memcpy(B->constants,A.constants,A.dim* sizeof(int));
    memcpy(B->bounds,A.bounds,A.dim* sizeof(int));
    return OK;
}
int print(Array A){
    printf("这是一个%d维数组\n",A.dim);
    for (int i = 0; i < A.dim; ++i) {
        printf("第%d维有%d个元素\n",i+1,A.bounds[i]);
    }
    printf("按行为主序输出\n");
    for (int j = 0; j < A.count; ++j) {
        printf("%d ",A.base[j]);
    }
    printf("\n");
    return  OK;
}
int main(){
    Array   array;
    while (1){
        printf("welcome\n1.InitArray\n2.Assign\n3.Vaule\n4.Copy\n5.exit\n");
        int a;
        scanf("%d",&a);
        switch (a){
            case 1:{
                InitArray(&array);
                print(array);
                break;
            }
            case 2:{
                printf("输入想要赋的值\n");
                ElemType    k;
                scanf("%d",&k);
                if(Assign(&array,k)==1){
                    printf("修改后的数组\n");
                    print(array);
                } else{
                    fflush(stdin);
                }
                break;
            }
            case 3:{
                printf("获取某个位置的值\n");
                ElemType    e;
                if(Vaule(array,&e)==1){
                    printf("值为%d\n",e);
                }

                break;
            }
            case 4:{
                Array   b;
                Copy(array,&b);
                print(b);
                DestroyArray(&b);
                break;
            }
            case 5:{
                DestroyArray(&array);
                return 0;
            }
            default:{
                continue;
            }
        }
    }
}