#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
/*储存学生信息的结构体*/
struct  student{
    char    name[100];
    char score1[6];//采用字符串表示成绩
    char score2[6];
    char score3[6];
    int sum;//总分
}stu1[10000],stu2[10000];
/*插入排序*/
void    insertion(struct    student a[],int n){
    struct student temp;
    int key;
    int i;
    for(int j=1;j<n;j++){
        i=j-1;
        key=a[j].sum;
        temp=a[j];
        while(i>=0&&a[i].sum>key){
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=temp;
    }
}
/*按照字符写入程序，ctrl+Z表示结束*/
void    txtwrite(){
    FILE    *fp=NULL;
    if(!(fp=fopen("c:\\ceshi\\students.txt","w"))){//文件在C盘下的ceshi文件夹
        printf("error");
        exit(1);
    }
    char ch=getchar();
    while(ch!=EOF){
        fputc(ch,fp);
        ch=getchar();
    }
    fclose(fp);
}
/*按照字符读入文件信息，
 * 根据读到的空格确定读入数据是什么，
 * 读到换行表示下一个学生信息，返回读入学生总数
*/
int txtread(){
    FILE    *fp=NULL;
    int flag=0;
    int i=0;
    int j=0;
    int k1=0;
    int k2=0;
    int k3=0;
    if(!(fp=fopen("c:\\ceshi\\students.txt","r"))){
        printf("error");
        exit(1);
    }
    char ch=fgetc(fp);
    while (ch!=EOF){
        if(ch==' '){
            flag++;
        }
        if(flag==0){//读入学生姓名
            stu1[i].name[j++]=ch;
        }
        if(flag==1){//读入学生第一个成绩
            stu1[i].name[j]='\0';//在读入的上一个字符串后写入'\0'
            if(ch>='0'&&ch<='9'){
                stu1[i].score1[k1++]=ch;
            }
        }
        if(flag==2){//读入学生第二个成绩
            stu1[i].score1[k1]='\0';
            if(ch>='0'&&ch<='9'){
                stu1[i].score2[k2++]=ch;
            }
        }
        if(flag==3){//读入学生第三个成绩
            stu1[i].score2[k2]='\0';
            if(ch>='0'&&ch<='9'){
                stu1[i].score3[k3++]=ch;
            }
        }
        if(ch=='\n'){
            stu1[i].score3[k3]='\0';
            i++;//读下一个学生数据
            flag=j=k1=k2=k3=0;
        }
        ch=fgetc(fp);
    }
    fclose(fp);
    return i;


}
/*将字符串表示的成绩转换成int型并返回*/
int num(char    score[]){
    int i=0;
    int sum=0;
    while(score[i]!='\0'){
        i++;
    }
    for(int j=0;j<i;j++){
        sum=sum+(score[j]-'0')*(int)(pow(10,(double)(i-j-1)));
    }
    return sum;

}
/*求每一个学生的总分*/
int sum(struct student    stu1){
    int score1=num(stu1.score1);
    int score2=num(stu1.score2);
    int score3=num(stu1.score3);
    return (score1+score2+score3);
}
/*二进制写入*/
void    datwrite(){
    FILE    *fp=NULL;
    if(!(fp=fopen("c:\\ceshi\\students.dat","w"))){
        printf("error");
        exit(1);
    }
    struct student  stu1;
    struct student  *p;
    p=&stu1;
    while((scanf("%s %s %s %s",stu1.name,stu1.score1,stu1.score2,stu1.score3))!=EOF){
        stu1.sum=sum(stu1);
        fwrite(p, sizeof(stu1),1,fp);
    }
    fclose(fp);
}
/*二进制读入文件，返回读入学生总数*/
int datread(){
    struct student  stu1;
    struct student  *p;
    p=&stu1;
    int i=0;
    FILE    *fp=NULL;
    if(!(fp=fopen("c:\\ceshi\\students.dat","r"))){
        printf("error");
        exit(1);
    }
    while(fread(p, sizeof(stu1),1,fp)!=0){
        stu2[i++]=stu1;
    }
    return i;
}
int main() {
    txtwrite();
    int i=txtread();
    for(int j=0;j<i;j++){
        stu1[j].sum=sum(stu1[j]);
    }
    insertion(stu1,i);
    printf("姓名 英语 数学 程序设计 总分\n");
    for(int j=0;j<i;j++){
        printf("%s %s %s %s %d\n",stu1[j].name,stu1[j].score1,stu1[j].score2,stu1[j].score3,stu1[j].sum);
    }
    datwrite();
    i=datread();
    insertion(stu2,i);
    printf("姓名 英语 数学 程序设计 总分\n");
    for(int j=0;j<i;j++){
        printf("%s %s %s %s %d\n",stu2[j].name,stu2[j].score1,stu2[j].score2,stu2[j].score3,stu2[j].sum);
    }

    return 0;
}
