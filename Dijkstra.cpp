#include<cstdio>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 65535
#define MaxSize 50
typedef int PathMatrix[MaxSize][MaxSize];
typedef int ShortPathLength[MaxSize];
typedef enum{DG,DN,UG,UN}GraphKind;
typedef struct
{
    VRType adj;
    InfoPtr *info;
}ArcNode,AdjMatrix[MaxSize][MaxSize];
typedef struct
{
    VertexType vex[MaxSize];
    AdjMatrix arc;
    int vexnum,arcnum;
    GraphKind kind;
}MGraph;
typedef struct
{
    int row;
    int col;
    int weight;
}GNode;
void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch);
void DisplayGraph(MGraph *N);
void Dijkstra(MGraph *N,int v0,PathMatrix path,ShortPathLength dist);
int main()
{
    int i,vnum=6,arcnum=8;
    MGraph N;
    GNode value[]={{0,2,15},{0,4,30},{0,5,100},{1,2,10},
    {2,3,50},{3,5,10},{4,3,20},{5,4,60}};
    VertexType ch[]={"v0","v1","v2","v3","v4","v5"};
    PathMatrix path;
    ShortPathLength dist;
    CreateGraph(&N,value,vnum,arcnum,ch);
    DisplayGraph(&N);
    Dijkstra(&N,0,path,dist);
    printf("%s到各顶点的最短路径长度为:\n",N.vex[0]);
    for(i=0;i<N.vexnum;i++)
        if(i!=0)
             printf("%s-%s:%d\n",N.vex[0],N.vex[i],dist[i]);
}
void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch)
{
    int i,j,k;
    N->vexnum=vnum;
    N->arcnum=arcnum;
    for(i=0;i<vnum;i++)
        strcpy(N->vex[i],ch[i]);
    for(i=0;i<vnum;i++)
        for(j=0;j<vnum;j++)
    {
        N->arc[i][j].adj=INFINITY;
        N->arc[i][j].info=NULL;
    }
    for(k=0;k<vnum;k++)
    {
        i=value[k].row;
        j=value[k].col;
        N->arc[i][j].adj=value[k].weight;
    }
    N->kind=DN;
}
void DisplayGraph(MGraph *N)
{
    int i,j;
    printf("有向网具有%d个顶点%d条弧,顶点依次是:");
    for(i=0;i<N->vexnum;i++)
        printf("%s ",N->vex[i]);
    printf("\n有向网N的:\n");
    printf("序号i=");
    for(i=0;i<N->vexnum;i++)
        printf("%8d",i);
    printf("\n");
    for(i=0;i<N->vexnum;i++)
    {
        printf("%8d",i);
        for(j=0;j<N->vexnum;j++)
            printf("%8d",N->arc[i][j].adj);
        printf("\n");
    }
}
void Dijkstra(MGraph *N,int v0,PathMatrix path,ShortPathLength dist)
{
    int i,j,w,k,v,min;
    int final[MaxSize];
    for(v=0;v<N->vexnum;v++)
    {
        dist[v]=N->arc[v0][v].adj;
        final[v]=0;
        for(w=0;w<N->vexnum;w++)
            path[v][w]=0;
        if(dist[v]<INFINITY)
        {
            path[v][v0]=1;
            path[v][v]=1;
        }
    }
    final[v0]=1;
    dist[v0]=0;
    for(i=1;i<N->vexnum;i++)
    {
        min=INFINITY;
        for(w=0;w<N->vexnum;w++)
            if(!final[w]&&dist[w]<min)
        {
            v=w;
            min=dist[w];
        }
        final[v]=1;
        for(w=0;w<N->vexnum;w++)
            if(!final[w]&&min<INFINITY&&N->arc[v][w].adj<INFINITY&&(dist[v]+N->arc[v][w].adj<dist[w]))
            {
                dist[w]=min+N->arc[v][w].adj;
                for(k=0;k<N->vexnum;k++)
                    path[w][k]=path[v][k];
                path[w][w]=1;
            }
    }
}
