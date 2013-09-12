/**
 * Testest 主程序
 * 2010-06-1
 * By yuzeming
 */
#include "main.h"

Complier_t Cpr;
Prob_t Pbt;
Runner_t Rnt;
char SRC[256];		//源文件
char NAME[256];		//主文件名
char SDIR[256];		//目录
char EXE[256];		//可执行文件
char TMPDIR[256];	//临时目录
char INI[256];
char MyDir[256];
char Tmp[256];
int main(int argc, char **argv)
{
	if (argc!=2)
	{
		//PrintHelp();
		printf("错误的参数\n");
		return 255;
	}
	strcpy(SRC,argv[1]);
	getcwd(MyDir,255);
	FixFileName(MyDir,SRC,Tmp);
	strcpy(SRC,Tmp);

	GetMainFileName(SRC,NAME);
	GetDir(SRC,SDIR);

	if (!FindIniFile(NAME,SDIR,INI))
	{
		printf("没有找到配置文件 %s",NAME);
		return 0;
	}

	strcpy(Cpr.Src,SRC);
	strcpy(TMPDIR,SDIR);
	strcat(TMPDIR,"TEST_TMP_DIR");
	mkdir(TMPDIR,0777);
	strcat(TMPDIR,"/");
	strcpy(EXE,TMPDIR);
	strcat(EXE,NAME);
	strcat(EXE,".tmpexe");
	strcpy(Cpr.Exe,EXE);

	if (!Cpr.Complie())
	{
		printf("编译源文件 %s 失败！\n",Cpr.Src);
		printf("%s\n",Cpr.Res);
		return 0;
	}

	if (!Pbt.Load(INI))
	{
		printf("读取配置文件 %s 失败\n",INI);
		return 0;
	}
	strcpy(Rnt.Exe,EXE);
	Rnt.ResetRet();
	Judge(Rnt,Pbt,TMPDIR);
	TMPDIR[strlen(TMPDIR)-1]=0;
	remove(EXE);
	remove(TMPDIR);
	return 0;
}
