#include <stdio.h>
#include <string.h>
/*根据符号判断和与差的输出，矩阵行数0代表第一个数符号为+行数1代表第一个数符号为-
 * 矩阵列数0代表第二个数符号为+列数1代表第二个数符号为-*/
const int rule[2][2]={0,1,-1,2};
/*得到输入数字的符号*/
int finalgetmark(char  *num){
    char mark=*num;
    int flag=0;
    if(mark=='-'){
        flag=1;
    }
    return flag;
}
/*将数字的符号移出*/
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
/*将没有符号的数按照最低位对齐，不足的高位补0*/
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
/*根据每一位的数字和进位计算每一位的和，返回进位*/
int asum(char   *num1, char *num2, int  i, int  carry){
    int sum=0;
    int mycarry=0;
    sum=*(num1+i)-'0'+*(num2+i)-'0'+carry;
    mycarry=sum/10;
    sum=sum%10;
    *(num1+i)='0'+sum;
    return mycarry;
}
/*计算已经对齐的无符号的数字的和*/
void    finalsum(char   *num1, char *num2){
    int i=strlen(num1)-1;
    int carry=0;//代表低位的进位
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
/*根据每一位的数字和借位位计算每一位的差，返回借位*/
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
/*计算已经对齐的无符号的数字的差*/
void finaldif(char  *num1, char *num2){
    int i=strlen(num1)-1;
    int difcarry=0;
    for(;i>=0;i--){
        difcarry=adif(num1,num2,i,difcarry);
    }
}
/*计算和*/
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
/*计算差*/
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
/*运算*/
void    evaluate(char    *num1, char *num2){
    int mark1=finalgetmark(num1);//得到数字的符号
    int mark2=finalgetmark(num2);
    char twonum1[250];//因为要计算两个值，每计算一次原来的操作数被改变
    char twonum2[250];//所以事先将两个操作数拷贝，进行第二次计算
    char zero[250];//定义一个0的字符串
    strcpy(zero,"0");
    strcpy(twonum1,num1);
    strcpy(twonum2,num2);
    moveout(twonum1);//移出符号
    moveout(twonum2);
    moveout(num1);
    moveout(num2);
    mark1=rule[mark1][mark2];//根据符号选择输出的值
    switch (mark1){
        case 0:{
            printf("和为%s\n",sum(num1,num2));
            printf("差为%s\n",dif(twonum1,twonum2));
            break;
        }
        case 1:{
            printf("和为%s\n",dif(num1,num2));
            printf("差为%s\n",sum(twonum1,twonum2));
            break;
        }
        case -1:{
            printf("和为%s\n",dif(num2,num1));
            printf("差为%s\n",dif(zero,sum(twonum1,twonum2)));
            break;
        }
        case 2:{
            printf("和为%s\n",dif(zero,sum(num1,num2)));
            printf("差为%s\n",dif(twonum2,twonum1));
            break;

        }

    }

}
int main() {
    char num1[250];
    char num2[250];
    printf("请输入第一个数（换行表示结束）：");
    gets(num1);
    printf("请输入第二个数（换行表示结束）：");
    gets(num2);
    evaluate(num1,num2);
    return 0;
}

