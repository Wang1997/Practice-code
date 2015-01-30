/**
 * @author CLD
 * 2015年1月30日
 * 					动态规划——钢条切割
 * 给定一个长度为n的钢条和一个价格表P_i(i=1,2,3,···,n),求钢条切割方案，使得利润r_i(i=1,2,3,···,n)最大
 * 					给定价格表如下：
 *				i： 1, 2, 3, 4, 5, 6, 7, 8, 9,10
 * 				p： 1, 5, 8, 9,10,17,17,20,24,30
 */

#include <cstdio>//继承与C的输入输出标准库
#include <algorithm>//算法标准库
using namespace std;//此代码没用到,习惯性附加.

int main() {
	const int LEN=10;//钢条的长度，也即价格表和利润表的长度
	int p[LEN+1]={0,1, 5, 8, 9,10,17,17,20,24,30};//价格表
	int r[LEN+1]={0};//初始化利润表,长度为零的钢条利润为零.
	for (int len = 1; len <= LEN; ++len) {
		//计算长度为len的钢条的利润
		int temp = -1;//暂时保存最大利润
		for (int index = 1; index <= len; ++index) {
			//选出最优方案,依靠已经计算出来的利润来计算当前利润
			temp = max(temp,p[index]+r[len-index]);
		}
		r[len] = temp;//将当前长度的结果保存供下次计算使用.
	}
	printf("%d\n",r[LEN+1]);//打印出题目要求长度的最大利润
	return 0;
}
