#include <stdio.h>
#include <math.h>
/*�ж�����*/
int run(int year){
    return ((year%4==0&&year%100!=0)||year%400==0);
}
/*����һ���ж�����*/
int days(int    year){
    if(run(year)){
        return 366;
    }
    else{
        return 365;
    }
}
/*����Ҫ��ӡ���1��1�յ�1900��1��1�յ�����*/
int sum(int year) {
    int sum = 0;
    if (year > 1900) {
        for (int i = 1900; i < year; i++) {
            sum = sum + days(i);
        }
    } else {
        if (year < 1900) {
            for (int i = year; i < 1900; i++) {
                sum = sum + days(i);
            }
        } else {
            return 0;
        }
    }
    return sum;
}
/*����Ҫ��ӡ��һ��1��1�������ڼ�*/
int start(int   year){
    int key[]={1,2,3,4,5,6,0};//0����������
    int realsum=0;
    realsum=sum(year);
    realsum=realsum%7;
    return key[realsum];
}
/*�����·ݵ�����*/
int monthdays(int   month, int  year){
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(run(year)){
        a[1]=29;
    }
    return a[month-1];
};
/*����ÿһ���·ݵ�һ�������ڼ�*/
int monstart(int    month, int  start, int  year){
    int realsum=monthdays(month,year)%7;
    int key[]={1,2,3,4,5,6,0,1,2,3,4,5,6,0};
    return key[realsum+start-1];
}
/*��ӡһ�У������ش�ӡ��������һ��*/
int print(int  start, int  day, int month, int  year){
    int count=0;
    for(int i=0;i<start;i++){
        printf("    ");
        count++;
    }
    for(;(count<7)&&(day<=monthdays(month,year));day++){
        printf("%2d  ",day);
        count++;
    }
    for(;count<7;count++){
        printf("    ");
    }
    return day;
}
/*��ʾ*/
void visual(int year){
    int realstart1=start(year);
    int realstart2=0;
    int linestart1=0;
    int linestart2=0;
    linestart1=realstart1;
    int day1=1;
    int day2=1;
    printf("----------------------%d������---------------------------\n",year);
    for(int i=1;i<=11;i=i+2){
        printf("%d��                            %d��\n",i,i+1);
        printf("Sum Mon Tue Wed Thu Fri Sat    Sum Mon Tue Wed Thu Fri Sat\n");
        realstart2=linestart2=monstart(i,realstart1,year);
        while(day1<=monthdays(i,year)||day2<=monthdays(i+1,year)){
            day1=print(linestart1,day1,i,year);
            linestart1=0;
            printf("    ");
            day2=print(linestart2,day2,i+1,year);
            linestart2=0;
            printf("\n");
        }
        linestart1=realstart1=monstart(i+1,realstart2,year);
        day1=1;
        day2=1;
    }
}
int main() {
    int year=0;
    printf("���뿴�����");
    scanf("%d",&year);
    visual(year);
    return 0;
}