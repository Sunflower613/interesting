#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#define U 1
#define D 2
#define L 3
#define R 4
typedef struct snake
{
    int x;
    int y;
    struct snake *next;
}snake;
int score=0,add=10;
int foodnum=0;
int Highscore=0;
int status,sleeptime=200;
snake *head,*food;
snake *q;
int endgamestatus=0;
HANDLE hOut;
void gotoxy(int x,int y);
int color(int c);
void welcometogame();
void createMap();
void initsnake();
void createfood();
void cantcrosswall();
void snakemove();
void keyboardControl();
void endgame();
void choose();
void scoreandtips();
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

void welcometogame()
{
    int n;
    int i,j=1;
    gotoxy(23,2);
    color(14);
    printf("贪 吃 蛇 大 作 战");
    color(15);
    for(i=6;i<=12;i++)
    {
        for(j=7;j<=54;j++)
        {
            gotoxy(j,i);
            if(i==6||i==12)printf("-");
            else if(j==7||j==54)printf("|");
        }
    }
    color(11);
    gotoxy(15,8);
    printf("1.开始游戏");
    gotoxy(35,8);
    printf("2.游戏说明");
    gotoxy(15,10);
    printf("3. 退出游戏");
    gotoxy(19,13);
    color(12);
    printf("请选择[1 2 3]:[ ]\b\b");
    color(14);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
            system("cls");
            createMap();
            initsnake();
            createfood();
            keyboardControl();
            break;
        case 2:
            system("cls");
            printf("上下左右控制移动就不用我说了吧.\n\n");
            printf("吃一个食物是10分.\n\n");
            printf("下面隆重介绍本游戏的bug，哦不，特性：\n\n\n");
            printf("当按↓键的时候，小蛇会拉下一坨‘奥里给’（\n\n");
            printf("不用担心，因为这坨‘奥里给’与食物长得一样，所以是可以吃的!\n\n");
            printf("但是根据能量守恒原则，你吃下之后并不会长长.\n\n");
            printf("那么如何区分‘奥里给’与真正的食物呢？\n\n");
            printf("小编也很疑惑，快来和小编一起看一看吧！\n\n");
            printf("按enter返回：");
            getch();
            system("cls");
            welcometogame();
        case 3:
            exit(0);
            break;
        default:
            color(12);
            gotoxy(40,28);
            printf("请输入1~3之间的数!");
            getch();
            system("cls");
            welcometogame();
    }
}
void createMap()
{
    int i,j;
    for(i=0;i<58;i+=2)
    {
        gotoxy(i,0);
        color(63);
        printf("口");
        gotoxy(i,26);
        printf("口");
    }
    for(i=1;i<26;i++)
    {
        gotoxy(0,i);
        printf("口");
        gotoxy(56,i);
        printf("口");
    }
    for(i=2;i<56;i++)
    {
        for(j=1;j<26;j++)
        {
            gotoxy(i,j);
            color(33);
            printf(" ");
        }
    }
}
void initsnake()
{
    snake *tail;
    int i;
    tail=(snake*)malloc(sizeof(snake));
    tail->x=24;
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)
    {
        head=(snake*)malloc(sizeof(snake));
        head->next=tail;
        head->x=24+2*i;
        head->y=5;
        tail=head;
    }
    while(tail!=NULL)
    {
        gotoxy(tail->x,tail->y);
        color(14);
        printf("◆");
        tail=tail->next;
    }
}
void createfood()
{
    snake *food_1;
    srand((unsigned)time(NULL));
    food_1=(snake*)malloc(sizeof(snake));
    while((food_1->x%2)!=0)
    {
        food_1->x=rand()%52+2;
    }
    food_1->y=rand()%24+1;
    q=head;
    while(q->next==NULL)
    {
        if(q->x==food_1->x&&q->y==food_1->y)
        {
            free(food_1);
            createfood();
        }
        q=q->next;
    }
    gotoxy(food_1->x,food_1->y);
    food=food_1;
    color(36);
    printf("%c",3);
    foodnum++;
}
void cantcrosswall()
{
    if(head->x==0||head->x==56||head->y==0||head->y==26)
    {
        endgamestatus=1;
        endgame();
    }
}
void snakemove()
{
    snake * nexthead;
    cantcrosswall();
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x&&nexthead->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            score=score+add;
            foodnum--;
            createfood();
        }
        else
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            gotoxy(q->next->x,q->next->y);
            color(33);
            printf(" ");
            gotoxy(q->next->x+1,q->next->y);
            color(33);
            printf(" ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==D)
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x&&nexthead->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            score=score+add;
            foodnum--;
            createfood();
        }
        else
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            gotoxy(q->next->x,q->next->y);
            color(33);
            printf(" ");
            gotoxy(q->next->x+1,q->next->y);
            color(33);
            printf(" ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==L)
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x&&nexthead->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            score=score+add;
            foodnum--;
            createfood();
        }
        else
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            gotoxy(q->next->x,q->next->y);
            color(33);
            printf(" ");
            gotoxy(q->next->x+1,q->next->y);
            color(33);
            printf(" ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==R)
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
        nexthead->next=head;
        head=nexthead;
        q=head;
        if(nexthead->x==food->x&&nexthead->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            score=score+add;
            foodnum--;
            createfood();
        }
        else
        {
            while(q->next->next!=NULL)
            {
                gotoxy(q->x,q->y);
                color(46);
                printf("◆");
                q=q->next;
            }
            gotoxy(q->next->x,q->next->y);
            color(33);
            printf(" ");
            gotoxy(q->next->x+1,q->next->y);
            color(33);
            printf(" ");
            free(q->next);
            q->next=NULL;
        }
    }
}
void keyboardControl()
{
    status=R;
    while(1)
    {
        if(GetAsyncKeyState(VK_UP)&&status!=D)
        {
            status=U;
        }
        else if(GetAsyncKeyState(VK_DOWN)&&status!=U)
        {
            status=D;
            if(foodnum!=0)createfood();
        }
        else if(GetAsyncKeyState(VK_LEFT)&&status!=R)
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&&status!=L)
        {
            status=R;
        }
        if(GetAsyncKeyState(VK_SPACE))
        {
            while(1)
            {
                Sleep(300);
                if(GetAsyncKeyState(VK_SPACE))
                {
                    break;
                }            
            }
        }
                else if(GetAsyncKeyState(VK_ESCAPE))
                {
                    endgamestatus=3;
                    break;
                }
            Sleep(sleeptime);
            snakemove();
    }
}
void endgame()
{
    system("cls");
    if(endgamestatus==1)
    {
        gotoxy(13,3);
        color(12);
        printf("对不起，您撞到墙了。游戏结束!");
    }
    gotoxy(23,7);
    color(15);
    printf("您的得分是%d",score);
    gotoxy(23,9);
    printf("您一共拉了%d坨奥里给",foodnum);
    choose();
}
void choose()
{
    int m;
    gotoxy(8,11);
    color(14);
    printf("我要重新玩一局-------1");
    gotoxy(35,11);
    printf("毁灭吧，我累了-------2");
    gotoxy(29,13);
    color(11);
    printf("选择；");
    scanf("%d",&m);
    switch (m)
    {
    case 1:
        system("cls");
        score=0;
        sleeptime=200;
        add=10;
        initsnake();
        welcometogame();
        break;
    case 2:
        exit(0);
        break;
    default:
            color(12);
            gotoxy(40,28);
            printf("请输入1~2之间的数!");
            getch();
            system("cls");
            endgame();
    }
}
int main()
{
    system("mode con cols=100 lines=30");
    welcometogame();
    keyboardControl();
    endgame();
    return 0;
}