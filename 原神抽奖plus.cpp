#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define N 90
char juese1[16]="八重神子";
char juese2[16]="托马";
char juese3[16]="迪奥娜";
char juese4[16]="菲谢尔";
int yue=1000;
int n,i,j,m[10],x=0,k,v;
int baodi=0;
int sixing=0;
int dabaodi=0;
int P=100;
void caidan();
void zhiling();
void yici();
void shici();
void chongzhi();
void shuaxin();
void clean();
void choujiang(int x);
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}
void clean()
{
    for(int i=0;i<11;i++)
    {
        printf("                                       \n");
    }
    gotoxy(0,9);
}
void zhiling()
{
    system("cls");
    color(240);
    printf("-----------------------------------------------------\n");
    color(244);
    printf("【派蒙提醒您：理智消费，逝度氪金！】\n\n");
    color(240);
    printf("本期up池角色为");
    color(246);
    printf("【%s】",juese1);
    color(253);
    printf("【%s】【%s】【%s】\n",juese2,juese3,juese4);
    color(240);
    printf("祈愿1次-------1\n");
    printf("祈愿10次-------2\n");
    printf("充值648-------3\n");
    printf("请输入指令（1.单抽；2.十连；3.充值；m.更多）：\n");
    caidan();
}
void caidan()
{
    gotoxy(62,20);
    color(242);
    printf("纠缠之缘:%5d",yue);
    gotoxy(64,21);
    printf("幸运值:%5d\n",baodi);
    
xuanze:
    gotoxy(0,8);
    color(240);
    printf("                           ");
    gotoxy(0,8);
    char xz;
    scanf("%c",&xz);
    
    switch(xz)
    {
        case '1':
        yici();
        break;
        case '2':
        shici();
        break;
        case '3':
        chongzhi();
        break;
        case 'm':
        clean();
        printf("敬请期待...\n");
        goto xuanze;
        break;
        default:
        goto xuanze;
    }
}
void yici()
{
    clean();
    if(yue==0)printf("余额不足，请充值！\n");
    else {
        x=rand()%P;
        printf("恭喜您获得：\n");
        shuaxin();
        choujiang(x);
    }
    
    caidan();
}
void shuaxin()
{
    srand((unsigned)time(NULL));
    
}
void choujiang(int x)
{
    P=100-baodi;
    k=rand()%P;
    v=rand()%10;
    sixing++;
    baodi++;
    if(k==x||baodi==N)
    {
        color(246);
        n=rand()%2;
        if(n==1||dabaodi==1){
            printf("【%s】",juese1);
            dabaodi=0;
        }
        else 
        {
            n=rand()%3+1;
            if(n==1)printf("【七七】");
            else if(n==2)printf("【琴】");
            else if(n==3)printf("【迪卢克】");
            dabaodi++;
        }
        baodi=0;
        sixing=0;
    }
    else {    
        if(v==x%10||sixing%10==0)
        {
            color(253);
            n=rand()%2;
            if(n==1){
                n=rand()%3+1;
                if(n==1)printf("【%s】",juese2);
                else if(n==2)printf("【%s】",juese3);
                else if(n==3)printf("【%s】",juese4);
            }
            else {
                n=rand()%5+1;
                if(n==1)printf("【芭芭拉】");
                else if(n==2)printf("【班尼特】");
                else if(n==3)printf("【凝光】");
                else if(n==4)printf("【行秋】");
                else printf("【辛焱】");
            }
            sixing=0;
        }
        else {
            color(243);
            n=rand()%5+1;
            if(n==1)printf("【飞天御剑】");
        else if(n==2)printf("【白铁大剑】");
        else if(n==3)printf("【鸦羽弓】");
        else if(n==4)printf("【白缨枪】");
        else printf("【魔导绪论】");
        }
        
    }
    printf("%d  %d %d\n",P,x,k);
    
    yue--;
    color(240);
}
void shici()
{
    clean();
    if(yue<10)printf("余额不足，请充值！\n");
    else {
        
        printf("恭喜您获得：\n");
        shuaxin();
        for(i=0;i<10;i++){
            x=rand()%P;
            choujiang(x);
        }
        
    }
    caidan();
}
void chongzhi()
{
    yue+=50;
    clean();
    printf("充值成功！\n");
    color(242);
    printf("纠缠之缘+50\n");
    caidan();
}
int main()
{
    srand((unsigned)time(NULL));
    zhiling();
    return 0;
}