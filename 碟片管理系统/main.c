#include <stdio.h>
#include <string.h>
#include <io.h>
#include <stdlib.h>
#include <math.h>
//��Ƭ����ϵͳ
struct date{
    int year;
    int month;
    int day;
};
struct location{
    struct cd*  head;
    struct cd*  tail;
};
struct cd{
    char film_name[100];
    char country[100];
    char    type[100];
    int flag;
    char day[100];
    char vip[100];
    struct cd   *next;
};
FILE    *productone( struct cd  *pnew,FILE  *fp){
    char temp[500];
    char myflag[100];
    int i=0;
    int j=0;
    fgets(temp,500,fp);
    while(temp[i]!=' '){
        pnew->film_name[j++]=temp[i];
        i++;
    }
    pnew->film_name[j]='\0';
    j=0;
    while (temp[i]==' '){
        i++;
    }
    while(temp[i]!=' '){
        pnew->country[j++]=temp[i];
        i++;
    }
    pnew->country[j]='\0';
    j=0;
    while (temp[i]==' '){
        i++;
    }
    while(temp[i]!=' '){
        pnew->type[j++]=temp[i];
        i++;
    }
    pnew->type[j]='\0';
    j=0;
    while (temp[i]==' '){
        i++;
    }
    while(temp[i]!=' '){
        myflag[j++]=temp[i];
        i++;
    }
    myflag[j]='\0';
    j=0;
    if(!(strcmp(myflag,"δ��"))){
        pnew->flag=0;
    } else{
        pnew->flag=1;
    }
    if(pnew->flag==0){
        strcpy(pnew->day,"");
        strcpy(pnew->vip,"");
        return fp;
    } else{
        while (temp[i]==' '){
            i++;
        }
        while(temp[i]!=' '){
            pnew->day[j++]=temp[i];
            i++;
        }
        pnew->day[j]='\0';
        j=0;
        while (temp[i]==' '){
            i++;
        }
        while(temp[i]!='\n'){
            pnew->vip[j++]=temp[i];
            i++;
        }
        pnew->vip[j]='\0';
        return fp;
    }


}
struct location   *myread(){
    struct cd   *p=NULL;
    struct cd   *head=NULL;
    struct cd *pnew=NULL;
    struct location *ret=NULL;
    FILE  *fp=NULL;
    ret=(struct    location*)malloc(sizeof(struct  location));
    ret->head=head;
    ret->tail=p;
    if(access("c:\\yingdie\\film.txt",F_OK)){
        if(!(fp=fopen("c:\\yingdie\\film.txt","w"))){
            printf("error");
            exit(1);
        }
        return ret;
    }
    if(!(fp=fopen("c:\\yingdie\\film.txt","r"))){
        printf("error");
        exit(1);
    }
    pnew=(struct    cd*)malloc(sizeof(struct  cd));
    fseek(fp, 0L, SEEK_END );
    int length=ftell(fp);
    if(length==0){
        return  ret;
    }
    fseek(fp,0L,SEEK_SET);
    fp=productone(pnew,fp);
    head=pnew;
    p=pnew;
    while (!(feof(fp))){
        pnew=(struct    cd*)malloc(sizeof(struct  cd));
        fp=productone(pnew,fp);
        p->next=pnew;
        p=pnew;
    }
    p->next=NULL;
    ret->head=head;
    ret->tail=p;
    return ret;

}

struct  cd  *newfilm(struct cd *tail){
    struct cd   *pnew=NULL;
    pnew=(struct    cd*)malloc(sizeof(struct  cd));
    printf("�������Ƭ����:");
    scanf("%s",pnew->film_name);
    printf("�������Ƭ����:");
    scanf("%s",pnew->country);
    printf("�������Ƭ����:");
    scanf("%s",pnew->type);
    printf("�������Ƭ�Ƿ񱻽裨����0����δ�����1����������");
    scanf("%d",&(pnew->flag));
    getchar();
    if(pnew->flag==1){
        printf("�����������ڣ���ʽΪxxxx��xx��xx�գ�:");
        scanf("%s",pnew->day);
        printf("����������Ա��:");
        scanf("%s",pnew->vip);
    } else{
        strcpy(pnew->day,"");
        strcpy(pnew->vip,"");
    }
    pnew->next=NULL;
    if(tail==NULL){
        tail=pnew;
        return  tail;
    }else{
        tail->next=pnew;
        pnew->next=NULL;
        return pnew;

    }
}

struct  cd     *find(struct cd  *head,char  name[]){
    struct cd  *p=NULL;
    p=head;
    while (p!=NULL){
        if(strcmp(p->film_name,name)==0){
            return p;
        }
        p=p->next;
    }
    return NULL;
}
int sum(int y,int m,int d)
{
    unsigned char x[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int i,s=0;
    for(i=1;i<y;i++)
        if((i%4==0 && i%100!=0 )||( i%400==0))
            s+=366;//����
        else
            s+=365;//ƽ��
    if((y%4==0 && y%100!=0 )|| (y%400==0))
        x[2]=29;
    for(i=1;i<m;i++)
        s+=x[i];//���µ�����
    s+=d;//�յ�����
    return s;//����������,��Թ�Ԫ1��
}
int toint(char   temp[]){
    int i=0;
    int sum=0;
    int count=0;
    while (temp[i]!='\0'){
        count++;
        i++;
    }
    i=0;
    while (temp[i]!='\0'){
        sum=sum+(temp[i]-'0')*pow(10,count-i-1);
        i++;
    }
    return sum;
}
void    mywrite(struct  cd*head){
    struct cd*p=NULL;
    FILE    *fp=NULL;
    if(!(fp=fopen("c:\\yingdie\\film.txt","w"))){
        printf("error");
        exit(1);
    }
    p=head;
    while(p!=NULL){
        char temp[500];
        strcpy(temp,p->film_name);
        strcat(temp,"     ");
        strcat(temp,p->country);
        strcat(temp,"     ");
        strcat(temp,p->type);
        strcat(temp,"     ");
        if(p->flag==0){
            strcat(temp,"δ��");
        } else{
            strcat(temp,"���");
        }
        strcat(temp,"     ");
        strcat(temp,p->day);
        strcat(temp,"     ");
        strcat(temp,p->vip);
        if(p->next!=NULL){
            strcat(temp,"\n");
        }
        fputs(temp,fp);
        p=p->next;
        free(head);
        head=p;
    }
}
struct  date  num (char    day[]){
    int i=0;
    struct date date1;
    char temp[100];
    int j=0;
    while(day[i]!='\0'){
        if(day[i]>='0'&&day[i]<='9'){
            temp[j++]=day[i];
            i++;
        } else{
            temp[j]='\0';
            i++;
            j=0;
            break;
        }
    }
    date1.year=toint(temp);
    while(!(day[i]>='0'&&day[i]<='9')){
        i++;
    }
    while(day[i]!='\0'){
        if(day[i]>='0'&&day[i]<='9'){
            temp[j++]=day[i];
            i++;
        } else{
            temp[j]='\0';
            i++;
            j=0;
            break;
        }
    }
    date1.month=toint(temp);
    while(!(day[i]>='0'&&day[i]<='9')){
        i++;
    }
    while(day[i]!='\0'){
        if(day[i]>='0'&&day[i]<='9'){
            temp[j++]=day[i];
            i++;
        } else{
            temp[j]='\0';
            i++;
            j=0;
            break;
        }
    }
    date1.day=toint(temp);
    return date1;
}
void    borrow(struct   cd*head){
    char name[100];
    char diepian[100];
    char day[100];
    struct cd*p=NULL;
    char a;
    printf("�������Ա����");
    scanf("%s",name);
    while (1){
        printf("��������(Y/N):");
        getchar();
        scanf("%c",&a);
        if(a=='N'){
            break;
        }
        printf("�������Ƭ���֣�");
        scanf("%s",diepian);
        p=find(head,diepian);
        if(p==NULL){
            printf("�޴�Ƭ\n");
        } else{
            if(p->flag==1){
                printf("�ѽ��\n");
            } else{
                printf("�����������ڣ���ʽΪxxxx��xx��xx�գ�:");
                scanf("%s",day);
                p->flag=1;
                strcpy(p->day,day);
                strcpy(p->vip,name);
                printf("����ɹ�\n");
            }
        }
    }

}
void    myreturn(struct  cd *head){
    char name[100];
    char diepian[100];
    char day[100];
    struct cd*p=NULL;
    char a;
    int expense=0;
    printf("�������Ա����");
    scanf("%s",name);
    while (1){
        printf("��������(Y/N):");
        getchar();
        scanf("%c",&a);
        if(a=='N'){
            break;
        }
        printf("�������Ƭ���֣�");
        scanf("%s",diepian);
        printf("������黹���ڣ���ʽΪxxxx��xx��xx�գ�:");
        scanf("%s",day);
        p=find(head,diepian);
        if(p==NULL){
            printf("�޴�Ƭ\n");
        } else{
            if(p->flag==0){
                printf("�˵�δ�����������\n");
            } else{
                if(strcmp(p->vip,name)==0){
                    struct date d1=num(p->day);
                    struct date d2=num(day);
                    int sum1=sum(d1.year,d1.month,d1.day);
                    int sum2=sum(d2.year,d2.month,d2.day);
                    int y=sum2-sum1;
                    if(y%3==0){
                        expense=expense+y/3;
                    } else{
                        expense=expense+y/3+1;
                    }
                    strcpy(p->day,"");
                    p->flag=0;
                    strcpy(p->vip,"");
                    printf("�����ɹ�\n");
                } else{
                    printf("�˵�Ƭ����������ģ���������\n");
                }
            }
        }
    }
    printf("һ����Ҫ֧��%dԪ\n",expense);

}

int main() {
    struct location   *sum=myread();
    struct cd   *head=sum->head;
    struct cd   *tail=sum->tail;
    int menu=0;
    printf("---------------------Ӱ����Ϣ����ϵͳ-----------------------\n");
    printf("�����б�\n1.��Ƭ�ϼ�\n2.��Ƭ��ѯ\n3.��Ƭ����\n4.��Ƭ�黹\n5.��ctrl+Z��������д���ļ�\n");
    while ((scanf("%d",&menu))!=EOF){
        switch(menu){
            case 1:{
                tail=newfilm(tail);
                if(head==NULL){
                    head=tail;
                }
                break;
            }
            case 2:{
                char name[100];
                struct cd*p=NULL;
                printf("������Ҫ��ѯ�ĵ�Ƭ���֣�");
                scanf("%s",name);
                p=find(head,name);
                if(p==NULL){
                    printf("�޴�Ƭ\n");
                } else{
                    if(p->flag==1){
                        printf("�ѽ��\n");
                    } else{
                        printf("�ɽ���\n");
                    }
                }
                break;
            }
            case 3:{
                borrow(head);
                break;
            }
            case 4:{
                myreturn (head);
                break;
            }
        }
    }
    mywrite(head);
    return 0;
}


