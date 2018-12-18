#include <stdio.h>
#include <string.h>
//������ʮ���ư˽���ʹ��int�ͱ���
//ʮ������ʹ���ַ�������
/*�ַ���ת�ú���*/
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
/*ʮ����ת�����˽���*/
int tento(int num, int    key){
    int flag=0;
    int result=0;
    int per=1;//λȨ
    if(num<0){//�����������
        num=-num;
        flag=1;
    }
    while (num!=0){
        result=result+num%key*per;//���Խ�����ȡ��
        per=per*10;
        num=num/key;
    }
    if(flag==1){
        result=-result;
    }
    return result;
}
/*ʮתʮ������*/
char    *    tentosixteen(int    num, char    *result){
    int flag=0;
    int per=0;//λȨ
    char presult='0';//����һλת�����
    if(num<0){//����������
        num=-num;
        flag=1;
    }
    while (num!=0){
        presult=num%16+48;//+48��ASCII���
        if(num%16>9){
            presult=87+num%16;//����9�����ĸ
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
    reverse(result);//�ַ���ת��
    return result;
}
/*������תʮ����*/
int toten(int   num, int    key){
    int flag=0;
    int result=0;
    int per=1;//λȨ
    if(num<0){//�������
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
/*ʮ������תʮ����*/
int sixteentoten(char   *result){
    int j=0;
    char myresult[200];
    strcpy(myresult,result);
    int i=strlen(myresult)-1;
    for(;i>=0;i--){
        if(myresult[i]>='A'&&myresult[i]<='F'){//��д��ĸȫ�����Сд
            myresult[i]=myresult[i]-'A'+'a';
        }
    }

    if(myresult[0]=='-'){
        j=1;//����������
    }
   i=strlen(myresult)-1;
   int per=1;//λȨ
   int num=0;
   for(;i>=j;i--){
       if(myresult[i]>'9'){
           num=num+per*(myresult[i]-'a'+10);//����ĸ����
       } else{
           num=num+per*(myresult[i]-'0');//�����ִ���
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
    printf("��������Ҫת�������ƣ�");
    scanf("%d",&key);
    switch (key){
        case 2:{
            printf("�������������������");
            scanf("%d",&num);
            printf("������ʮ���Ʊ�ʾΪ��%d\n",toten(num,2));
            printf("�����İ˽��Ʊ�ʾΪ:%d\n",tento(toten(num,2),8));
            printf("������ʮ�����Ʊ�ʾΪ:%s\n",tentosixteen(toten(num,2),result));
            break;
        }
        case 8:{
            printf("����������˽�������");
            scanf("%d",&num);
            printf("������ʮ���Ʊ�ʾΪ��%d\n",toten(num,8));
            printf("�����Ķ����Ʊ�ʾΪ:%d\n",tento(toten(num,8),2));
            printf("������ʮ�����Ʊ�ʾΪ:%s\n",tentosixteen(toten(num,8),result));
            break;
        }
        case 10:{
            printf("���������ʮ��������");
            scanf("%d",&num);
            printf("�����Ķ����Ʊ�ʾΪ��%d\n",tento(num,2));
            printf("�����İ˽��Ʊ�ʾΪ:%d\n",tento(num,8));
            printf("������ʮ�����Ʊ�ʾΪ:%s\n",tentosixteen(num,result));
            break;
        }
        case 16:{
            printf("���������ʮ����������");
            scanf("%s",result);
            printf("�����Ķ����Ʊ�ʾΪ��%d\n",tento(sixteentoten(result),2));
            printf("�����İ˽��Ʊ�ʾΪ:%d\n",tento(sixteentoten(result),8));
            printf("������ʮ���Ʊ�ʾΪ:%d\n",sixteentoten(result));
            break;
        }
        default:{
            printf("�������\n");
        }
    }
    return 0;
}