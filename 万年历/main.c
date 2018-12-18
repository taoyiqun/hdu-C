#include <stdio.h>
#include <math.h>
/*判断润年*/
int run(int year){
    return ((year%4==0&&year%100!=0)||year%400==0);
}
/*返回一年有多少天*/
int days(int    year){
    if(run(year)){
        return 366;
    }
    else{
        return 365;
    }
}
/*返回要打印年份1月1日到1900年1月1日的天数*/
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
/*返回要打印那一年1月1日是星期几*/
int start(int   year){
    int key[]={1,2,3,4,5,6,0};//0代表星期日
    int realsum=0;
    realsum=sum(year);
    realsum=realsum%7;
    return key[realsum];
}
/*返回月份的天数*/
int monthdays(int   month, int  year){
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(run(year)){
        a[1]=29;
    }
    return a[month-1];
};
/*返回每一个月份第一天是星期几*/
int monstart(int    month, int  start, int  year){
    int realsum=monthdays(month,year)%7;
    int key[]={1,2,3,4,5,6,0,1,2,3,4,5,6,0};
    return key[realsum+start-1];
}
/*打印一行，并返回打印到当月哪一天*/
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
/*显示*/
void visual(int year){
    int realstart1=start(year);
    int realstart2=0;
    int linestart1=0;
    int linestart2=0;
    linestart1=realstart1;
    int day1=1;
    int day2=1;
    printf("----------------------%d年年历---------------------------\n",year);
    for(int i=1;i<=11;i=i+2){
        printf("%d月                            %d月\n",i,i+1);
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
    printf("你想看的年份");
    scanf("%d",&year);
    visual(year);
    return 0;
}