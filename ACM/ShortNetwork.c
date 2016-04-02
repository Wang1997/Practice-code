/**
 * @author Wang1997 
 * 2016年04月02日
 *
 *                    最短网络-最小生成树
 *N个农场，农场间需要建立互联网，输入每个农场与其他农场之间的距离，
 *找出连接所有农场所用光纤的最短方案 
 *输入：                  输出： 28 
 *4
 *0 4 9 21
 *4 0 8 17
 *9 8 0 16
 *21 17 16 0 
 *思路： 
 *每个农场为每个节点，从第一个节点开始寻找最短路线
 *使用一个数组标记节点，以防节点重复寻找
 *求出所有最短距离的总和 
 */
 
#include <stdio.h>
#define MAXFARM 105//设置最大农场数 
int main()
{
    int nfarm;//农场个数 
    int dist[MAXFARM][MAXFARM]={0};//农场间距离 
    int isconn[MAXFARM]={0};//用来标记农场 
    int i, j, nnode, mindist,minnode,total=0;
    scanf("%d", &nfarm);//nfarm为农场个数 
    for(i=0; i<nfarm; i++)//输入每个农场间距离 
       for(j=0; j<nfarm; j++) 
          scanf("%d",&dist[i][j]);
    isconn[0] = 1;//将第一个农场标记 
    for(nnode=1; nnode < nfarm; nnode++)//n个农场，需要寻找n-1条路线 
    {
       mindist = 0;
       for(i=0; i<nfarm; i++)
       {//枚举 i农场 到 j农场 
          for(j=0; j<nfarm; j++)
          {
             //如果i农场到j农场距离不为0，且第i个农场已标记，且其他农场未标记  
             if(dist[i][j] && isconn[i] && !isconn[j]) 
             {//mindist为0表示第一个合理解，后面条件表示目前最优解 
                if(mindist == 0 || dist[i][j] < mindist)
                {
                   mindist = dist[i][j];//记录最短距离 
                   minnode = j;//记录最短路径的农场编号 
                }   
             } 
          } 
       }
       isconn[minnode] = 1;//将该农场标记，防止重复记录 
       total += mindist;//将最短距离相加 
    }
     printf("%d\n",total); //输出最短方案 
}
