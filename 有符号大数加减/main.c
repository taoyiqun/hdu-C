#include <stdio.h>
#include <string.h>
/*���ݷ����жϺ������������������0�����һ��������Ϊ+����1�����һ��������Ϊ-
 * ��������0����ڶ���������Ϊ+����1����ڶ���������Ϊ-*/
const int rule[2][2]={0,1,-1,2};
/*�õ��������ֵķ���*/
int finalgetmark(char  *num){
    char mark=*num;
    int flag=0;
    if(mark=='-'){
        flag=1;
    }
    return flag;
}
/*�����ֵķ����Ƴ�*/
void moveout(char  *num){
    int i=0;
    int j=0;
    while(*(num+i)=='-'){
        i++;
    }
    while (1){
        *(num+j)=*(num+i);
        i++;
        j++;
        if(*(num+i)=='\0'){
            break;
        }
    }
    *(num+j)='\0';
}
/*��û�з��ŵ����������λ���룬����ĸ�λ��0*/
void myalign(int count, char    *num){
    int j=strlen(num);
    for(;j>=0;j--){
        *(num+count)=*(num+j);
        count--;
    }
    for(;count>=0;count--){
        *(num+count)='0';
    }
}
/*����ÿһλ�����ֺͽ�λ����ÿһλ�ĺͣ����ؽ�λ*/
int asum(char   *num1, char *num2, int  i, int  carry){
    int sum=0;
    int mycarry=0;
    sum=*(num1+i)-'0'+*(num2+i)-'0'+carry;
    mycarry=sum/10;
    sum=sum%10;
    *(num1+i)='0'+sum;
    return mycarry;
}
/*�����Ѿ�������޷��ŵ����ֵĺ�*/
void    finalsum(char   *num1, char *num2){
    int i=strlen(num1)-1;
    int carry=0;//�����λ�Ľ�λ
    for(;i>=0;i--){
        carry=asum(num1,num2,i,carry);
    }
    if(carry!=0){
        char  temp[2];
        temp[0]=carry+'0';
        temp[1]='\0';
        strcpy(num2,temp);
        strcat(num2,num1);
        strcpy(num1,num2);
    }


}
/*����ÿһλ�����ֺͽ�λλ����ÿһλ�Ĳ���ؽ�λ*/
int adif(char   *num1, char *num2, int  i, int  difcarry){
    int dif=0;
    int mycarry=0;
    dif=*(num1+i)-*(num2+i)-difcarry;
    if(dif<0){
        dif=dif+10;
        mycarry=1;
    }
    *(num1+i)='0'+dif;
    return mycarry;
}
/*�����Ѿ�������޷��ŵ����ֵĲ�*/
void finaldif(char  *num1, char *num2){
    int i=strlen(num1)-1;
    int difcarry=0;
    for(;i>=0;i--){
        difcarry=adif(num1,num2,i,difcarry);
    }
}
/*�����*/
char *sum(char  *num1, char*num2){
    int i=0;
    int j=0;
    i=strlen(num1);
    j=strlen(num2);
    if(i>j){
        myalign(i,num2);
        finalsum(num1,num2);
        return num1;
    } else{
        myalign(j,num1);
        finalsum(num2,num1);
        return num2;
    }
}
/*�����*/
char *dif(char  *num1, char*num2){
    int i=0;
    int j=0;
    i=strlen(num1);
    j=strlen(num2);
    if(i>j){
        myalign(i,num2);
        finaldif(num1,num2);
        return num1;
    } else{
        if(i<j){
            myalign(j,num1);
            finaldif(num2,num1);
            char temp[250];
            strcpy(temp,"-");
            strcat(temp,num2);
            strcpy(num2,temp);
            return num2;
        } else{
            myalign(j,num1);
            for (int    k=0;k<i;k++){
                if(*(num1+k)>*(num2+k)){
                    finaldif(num1,num2);
                    return num1;
                } else{
                    if(*(num1+k)<*(num2+k)){
                        finaldif(num2,num1);
                        char temp[250];
                        strcpy(temp,"-");
                        strcat(temp,num2);
                        strcpy(num2,temp);
                        return num2;
                    }
                }
            }
            strcpy(num1,"0");
            return num1;
        }
    }
}
/*����*/
void    evaluate(char    *num1, char *num2){
    int mark1=finalgetmark(num1);//�õ����ֵķ���
    int mark2=finalgetmark(num2);
    char twonum1[250];//��ΪҪ��������ֵ��ÿ����һ��ԭ���Ĳ��������ı�
    char twonum2[250];//�������Ƚ��������������������еڶ��μ���
    char zero[250];//����һ��0���ַ���
    strcpy(zero,"0");
    strcpy(twonum1,num1);
    strcpy(twonum2,num2);
    moveout(twonum1);//�Ƴ�����
    moveout(twonum2);
    moveout(num1);
    moveout(num2);
    mark1=rule[mark1][mark2];//���ݷ���ѡ�������ֵ
    switch (mark1){
        case 0:{
            printf("��Ϊ%s\n",sum(num1,num2));
            printf("��Ϊ%s\n",dif(twonum1,twonum2));
            break;
        }
        case 1:{
            printf("��Ϊ%s\n",dif(num1,num2));
            printf("��Ϊ%s\n",sum(twonum1,twonum2));
            break;
        }
        case -1:{
            printf("��Ϊ%s\n",dif(num2,num1));
            printf("��Ϊ%s\n",dif(zero,sum(twonum1,twonum2)));
            break;
        }
        case 2:{
            printf("��Ϊ%s\n",dif(zero,sum(num1,num2)));
            printf("��Ϊ%s\n",dif(twonum2,twonum1));
            break;

        }

    }

}
int main() {
    char num1[250];
    char num2[250];
    printf("�������һ���������б�ʾ��������");
    gets(num1);
    printf("������ڶ����������б�ʾ��������");
    gets(num2);
    evaluate(num1,num2);
    return 0;
}

