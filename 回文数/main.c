#include<stdio.h>
#include <string.h>
int panduan(char    x[]){
    int len=strlen(x);
    for (int i = 0; i <len/2; i++) {
        if(x[i]!=x[len-i-1]){
            return 0;
        }
    }
    return 1;
}
void    change(char   x[], char   y[]){
    int len=strlen(y);
    x[len]='\0';
    for (int i = 0; i <len ; i++) {
        x[i]=y[len-i-1];
    }
}
void jia(char   x[], char   y[], char   z[]){
    int len=strlen(x);
    int sum=0;
    int carry=0;
    int j=0;
    char k[1010];
    for (int i = 0; i <len ; i++) {
        sum=x[len-i-1]-'0'+y[len-i-1]-'0';
        if(carry+sum%10!=10){
            k[j++]=carry+sum%10+'0';
        } else{
            k[j++]='0';
            sum=sum+1;
        }
        carry=sum/10;
    }
    k[j]=carry+'0';
    if(k[j]!='0'){
        j++;
        k[j]='\0';
    } else{
        k[j]='\0';
    }
    change(z,k);

}
int main(){
    char c[1010];
    char d[1010];
    char r[1010];
    scanf("%s",c);
    int flag=0;
    for (int i = 0; i <10 ; i++) {
        flag=panduan(c);
        if(flag!=1){
            change(d,c);
            jia(c,d,r);
            printf("%s + %s = %s\n",c,d,r);
            strcpy(c,r);
        } else{
            printf("%s is a palindromic number.\n",c);
            break;
        }
    }
    if(flag==0){
        printf("Not found in 10 iterations.\n");
    }
    return 0;
}