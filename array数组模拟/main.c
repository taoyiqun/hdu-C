#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define MaxDim 5        //����ά�����ֵ
#define ElemType int
#define ERROR -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define OK 1

typedef struct {
    ElemType    *base;      //����Ԫ�ػ���ַ
    int dim;                //ά��
    int *bounds;            //����ά���ַ
    int *constants;         //ӳ����������ַ
    int count;
}Array;
int InitArray(Array *A){
    int dim;
    printf("����������ά��\n");
    scanf("%d",&dim);
    while (dim<1||dim>MaxDim){
        printf("ά��������������\n");
        scanf("%d",&dim);
    }
    A->dim=dim;
    A->bounds=(int*)malloc(dim* sizeof(int));
    if(!A->bounds)  {
        printf("ά���ڴ����ʧ��\n");
        exit(OVERFLOW);

    }
    //����ά���ȺϷ�������A.bounds�������Ԫ�ظ���elemtotal
    int elemtotal=1;
    printf("�������ά����\n");
    for (int i = 0; i < dim; ++i) {
        scanf("%d",&A->bounds[i]);
        if(A->bounds[i]<0){
            printf("ά���������\n");
            return UNDERFLOW;
        }
        elemtotal=elemtotal*A->bounds[i];
    }
    A->count=elemtotal;
    A->base=(ElemType*)malloc(elemtotal* sizeof(ElemType));
    if(!A->base){
        printf("����Ԫ���ڴ����ʧ��\n");
        exit(OVERFLOW);
    }
    printf("����Ϊ��������%d��Ԫ��\n",A->count);
    for (int j = 0; j <A->count ; ++j) {
        scanf("%d",&A->base[j]);
    }
    //��ӳ�����ĳ���ci��������A.constants[i-1],i=1,...,dim
    A->constants=(int   *)malloc(dim* sizeof(int));
    if(!A->constants)exit(OVERFLOW);
    A->constants[dim-1]=1;          //L=1,ָ���������Ԫ�صĴ�СΪ��λ
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
    //��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff
    *off=0;

    printf("������Ҫ������λ��\n");
    for (int i = 0; i < A.dim; ++i) {
        int ind;
        scanf("%d",&ind);
        if(ind<0||ind>=A.bounds[i]){
            printf("�±�Խ��\n");
            return OVERFLOW;
        }
        *off=*off+A.constants[i]*ind;
    }
    return OK;
}
int Vaule(Array A, ElemType *e){
    //A��nά���飬eΪԪ�ر����������n���±�ֵ��
    //�������±겻���磬��e��ֵΪָ����A��Ԫ��ֵ��������OK��
    int  off;
    int result=Locate(A,&off);
    if(result<=0){
        return result;
    }
    *e=*(A.base+off);
    return OK;
}
int Assign(Array    *A,ElemType e){
    //A��nά���飬eΪԪ�ر����������n���±�ֵ
    //���±겻Խ�磬��e��ֵ������ָ����A��Ԫ�أ�������OK

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
    printf("����һ��%dά����\n",A.dim);
    for (int i = 0; i < A.dim; ++i) {
        printf("��%dά��%d��Ԫ��\n",i+1,A.bounds[i]);
    }
    printf("����Ϊ�������\n");
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
                printf("������Ҫ����ֵ\n");
                ElemType    k;
                scanf("%d",&k);
                if(Assign(&array,k)==1){
                    printf("�޸ĺ������\n");
                    print(array);
                } else{
                    fflush(stdin);
                }
                break;
            }
            case 3:{
                printf("��ȡĳ��λ�õ�ֵ\n");
                ElemType    e;
                if(Vaule(array,&e)==1){
                    printf("ֵΪ%d\n",e);
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