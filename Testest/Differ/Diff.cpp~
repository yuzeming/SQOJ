/**
 * Testest V0.1
 * 默认校验器
 */
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
// 标准输入文件 , 选手输出文件 , 标准输出文件 , 结果文件
int main(int argv,char **arge)
{
	if (argv!=5)
	{
		printf("参数不正确!\n");
		return 1;
	}
	FILE * RET =fopen(arge[4],"w");
	char CMD[1000];
	CMD[0]=0;
	sprintf(CMD,"diff %s %s -w --speed-large-files -q >>/dev/null",arge[2],arge[3]);
	if (system(CMD)==0)
		fprintf(RET,"1.00 正确\n");
	else
		fprintf(RET,"0.00 错误\n");
	return 0;
}
