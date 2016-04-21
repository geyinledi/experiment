#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
typedef struct
{
    int x;
    int y;
}PosType;
typedef struct
{
    int ord;
    PosType seat;
    int di;
}DataType;
class stack
{
    struct node
    {
        DataType d;
        node *next;
    };
    node *topNode=NULL;
    int sum=0;
public:
    void init()
    {
        topNode=NULL;
    }
    bool empty()
    {
        return sum==0;
    }
    void push(DataType e)
    {
        node *s=new(node);
        s->d=e;
        s->next=NULL;
        if(topNode==NULL)
        {
            topNode=s;
        }
        else
        {
            s->next=topNode;
            topNode=s;
        }
        sum++;
    }
    void pop()
    {
        node *s;
        s=topNode;
        topNode=topNode->next;
        sum--;
        delete(s);
    }
    node front()
    {
        return *topNode;
    }
    int size()
    {
        return sum;
    }
};
#define maxle 40
typedef int MazeType[maxle][maxle];

MazeType m;
int x,y;
PosType begin,end;
int curstep=1;
void Print()
{
    int i,j;
    for(i=0;i<x;i++)
    {
        for(j=0;j<y;j++)
           printf("%3d",m[i][j]);
        printf("\n");
    }
}
void Init(int k)
{
    int i,j,x1,y1;
    printf("请输入迷宫的行数和列数（包括外墙）:");
    scanf("%d,%d",&x,&y);
    for(i=0;i<x;i++)
    {
        m[i][0]=0;
        m[i][y-1]=0;
    }
    for(i=0;i<y;i++)
    {
        m[0][i]=0;
        m[x-1][i]=0;
    }
    for(i=1;i<x-1;i++)
        for(j=1;j<y-1;j++)
            m[i][j]=k;
    printf("请输入迷宫的内墙单元数：");
    scanf("%d",&j);
    printf("请依次输入迷宫内墙每个单元的行数和列数：\n");
    for(i=1;i<=j;i++)
    {
        scanf("%d,%d",&x1,&y1);
        m[x1][y1]=0;
    }
    printf("迷宫的结构如下:\n");
    Print();
    printf("请输入入口的行数,列数:");
    scanf("%d,%d",&begin.x,&begin.y);
    printf("请输入出口的行数，列数:");
    scanf("%d,%d",&end.x,&end.y);
}
int Pass(PosType b)
{
    if(m[b.x][b.y]==1)
        return 1;
    else
        return 0;
}
void FootPrint(PosType a)
{
    m[a.x][a.y]=curstep;
}
void NextPos(PosType *c,int di)
{
    PosType dir[4]={{0,1},{1,0},{0,-1},{-1,0}};
    (*c).x=(*c).x+dir[di].x;
    (*c).y=(*c).y+dir[di].y;
}
void MarkPrint(PosType b)
{
    m[b.x][b.y]=-1;
}
int MazePath(PosType start,PosType end)
{
    stack S;
    PosType curpos;
    DataType e;
    S.init();
    curpos=start;
    do
    {
        if(Pass(curpos))
        {
            FootPrint(curpos);
            e.ord=curstep;
            e.seat=curpos;
            e.di=0;
            S.push(e);
            curstep++;
            if(curpos.x==end.x&&curpos.y==end.y)
                return 1;
            NextPos(&curpos,e.di);
        }
        else
        {
            if(!S.empty())
            {
                e=S.front().d;
                S.pop();
                curstep--;
                while(e.di==3&&!S.empty())
                {
                    MarkPrint(e.seat);
                    e=S.front().d;
                    S.pop();
                    curstep--;
                }
                if(e.di<3)
                {
                    e.di++;
                    S.push(e);
                    curstep++;
                    curpos=e.seat;
                    NextPos(&curpos,e.di);
                }
            }
        }
    }while(!S.empty());
    return 0;
}
int main()
{
    freopen("test.txt","r",stdin);
    Init(1);
    if(MazePath(begin,end))
    {
        printf("此迷宫从入口到出口的一条路径如下:\n");
        Print();
    }
    else
        printf("此迷宫没有从入口到出口的路径\n");
}
