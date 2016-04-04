/**
 * @author Wang1997 
 * 2016年04月05日
 *
 *                    并查集-is it a tree
 *输入n组数据，每组中成对两两输入数据，以 0 0 结束，每对数据表示 父结点->子结点
 *如样例表示结点6指向结点8，结点5指向结点3.。。判断是否为一棵树 
 *输入：                  输出： Case 1 is a tree.
 *6 8 5 3 5 2 6 4                Case 2 is not a tree.
 *5 6 0 0
 *3 8 6 8 6 4
 *5 3 5 6 5 2 0 0
 *-1 -1
 * 
 *空树也为数 
 *森林不为树，不存在环 
 *根节点只有出度，叶结点只有入度，其他结点只有1入度，n出度 
 */
#include<stdio.h>
#include<string.h>
int f[1000010];//存放父结点 
int getf(int v)//并查集
{//查找祖先，即根节点 
    if(v == f[v])//表示查找到根结点 
       return v;
    else
    {
        f[v]=getf(f[v]);//继续查找父结点，及路径压缩 
        return f[v];
    }
}
int main()
{
    int a,b,tree_num,t=0,fa_a,fa_b,flag;
    while(scanf("%d %d",&a,&b) != EOF)
    {
        if(a == -1)//输入 -1 结束输入 
          break;
        tree_num=flag=1;//设置开始树的数量1，flag为1表示标志此时为一棵树 
        if(a == 0)//空树 
        {
            printf("Case %d is a tree.\n",++t);
        }
        else if( a == b)//自己指向自己，相当于环 
        {
            flag=0;//更换标志，表示已不会构成树 
        }
        else
        {
            memset(f,0,sizeof(f));
            f[a]=f[b]=a;//设置b的父结点为a,a当然为自己 
        }
        while(scanf("%d %d",&a,&b) != EOF)
        {
            if(a == 0)//0 0 结束 
              break;
            if(flag == 0)//表示已经不为树 
              continue;
            if(f[b] != 0)//说明b之前肯定出现过 
            {
                fa_b = getf(f[b]);//获取b的根节点 
                if(fa_b != b)
                {//此时说明b的入度>=2了，不构成树 
                    flag=0;
                    continue;
                }
                else
                {
                    fa_a = getf(f[a]);//获取a的根结点 
                    if(f[a] == 0)
                    {//说明之前 a没出现过，因为b出现过，将b的根节点换为a 
                        f[a]=f[b]=a;
                    }
                    else
                    {//如果都出现过，树数量减1 
                        tree_num--;
                        f[b]=fa_a;//将b的根节点换为a的根节点 
                    }
                }
            }
            else
            {
                if(f[a] == 0)
                {//如果a b都没有出现过，设置b的父结点为a，树的个数+1 
                    f[a]=f[b]=a;
                    tree_num++;
                }
                else//否则将b的根节点换为a的根节点
                   f[b]=getf(f[a]);
            }
        }
        printf("Case %d ",++t);
        if(flag==0)//如果标志为0，说明不是树 
        {
            printf("is not a tree.\n");
            continue;
        }
        if(tree_num==1)//如果树个数为1，为树 
            printf("is a tree.\n");
        else
            printf("is not a tree.\n");
    }
}
