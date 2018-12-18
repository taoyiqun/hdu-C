#include <stdio.h>
#include <string.h>
//二进制十进制八进制使用int型保存
//十六进制使用字符串保存
/*字符串转置函数*/
void reverse(char   *result){
    int i=strlen(result)-1;
    int j=0;
    int count=strlen(result);
    while(i>=j){
        char temp=result[i];
        result[i]=result[j];
        result[j]=temp;
        i--;
        j++;
    }
    result[count]='\0';
}
/*十进制转二，八进制*/
int tento(int num, int    key){
    int flag=0;
    int result=0;
    int per=1;//位权
    if(num<0){//负数变成正数
        num=-num;
        flag=1;
    }
    while (num!=0){
        result=result+num%key*per;//除以进制再取余
        per=per*10;
        num=num/key;
    }
    if(flag==1){
        result=-result;
    }
    return result;
}
/*十转十六进制*/
char    *    tentosixteen(int    num, char    *result){
    int flag=0;
    int per=0;//位权
    char presult='0';//储存一位转换结果
    if(num<0){//负数变正数
        num=-num;
        flag=1;
    }
    while (num!=0){
        presult=num%16+48;//+48用ASCII码存
        if(num%16>9){
            presult=87+num%16;//大于9变成字母
        }
        result[per]=presult;
        per++;
        num=num/16;
    }
    if(flag==1){
        result[per]='-';
        result[per+1]='\0';
    } else{
        result[per]='\0';
    }
    reverse(result);//字符串转置
    return result;
}
/*二，八转十进制*/
int toten(int   num, int    key){
    int flag=0;
    int result=0;
    int per=1;//位权
    if(num<0){//变成正数
        num=-num;
        flag=1;
    }
    while (num!=0){
        result=result+num%10*per;
        per=per*key;
        num=num/10;
    }
    if(flag==1){
        result=-result;
    }
    return result;
}
/*十六进制转十进制*/
int sixteentoten(char   *result){
    int j=0;
    char myresult[200];
    strcpy(myresult,result);
    int i=strlen(myresult)-1;
    for(;i>=0;i--){
        if(myresult[i]>='A'&&myresult[i]<='F'){//大写字母全部变成小写
            myresult[i]=myresult[i]-'A'+'a';
        }
    }

    if(myresult[0]=='-'){
        j=1;//负数变正数
    }
   i=strlen(myresult)-1;
   int per=1;//位权
   int num=0;
   for(;i>=j;i--){
       if(myresult[i]>'9'){
           num=num+per*(myresult[i]-'a'+10);//对字母处理
       } else{
           num=num+per*(myresult[i]-'0');//对数字处理
       }
       per=per*16;
   }
   if(j==1){
       num=-num;
   }
    return num;
}
int main(){
    char result[200];
    int key;
    int num;
    printf("请输入想要转换的数制：");
    scanf("%d",&key);
    switch (key){
        case 2:{
            printf("请输入这个二进制数：");
            scanf("%d",&num);
            printf("该数的十进制表示为：%d\n",toten(num,2));
            printf("该数的八进制表示为:%d\n",tento(toten(num,2),8));
            printf("该数的十六进制表示为:%s\n",tentosixteen(toten(num,2),result));
            break;
        }
        case 8:{
            printf("请输入这个八进制数：");
            scanf("%d",&num);
            printf("该数的十进制表示为：%d\n",toten(num,8));
            printf("该数的二进制表示为:%d\n",tento(toten(num,8),2));
            printf("该数的十六进制表示为:%s\n",tentosixteen(toten(num,8),result));
            break;
        }
        case 10:{
            printf("请输入这个十进制数：");
            scanf("%d",&num);
            printf("该数的二进制表示为：%d\n",tento(num,2));
            printf("该数的八进制表示为:%d\n",tento(num,8));
            printf("该数的十六进制表示为:%s\n",tentosixteen(num,result));
            break;
        }
        case 16:{
            printf("请输入这个十六进制数：");
            scanf("%s",result);
            printf("该数的二进制表示为：%d\n",tento(sixteentoten(result),2));
            printf("该数的八进制表示为:%d\n",tento(sixteentoten(result),8));
            printf("该数的十进制表示为:%d\n",sixteentoten(result));
            break;
        }
        default:{
            printf("输入错误\n");
        }
    }
    return 0;
}