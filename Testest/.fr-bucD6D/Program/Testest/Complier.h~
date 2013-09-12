/**
 * Testest 编译模块 V0.1
 * 2010-06-01
 * By yuzeming
 */
#ifndef __Complier_t
#define __Complier_t 1

#define __CTE 10	// 10S		最长编译时限
#define __CRE (128*1024*1024) //128M	最大占用内存

class Complier_t
{
	public:
		Complier_t()
		{
			memset(Src,0,sizeof(Src));
			memset(Exe,0,sizeof(Exe));
			memset(Res,0,sizeof(Res));
		}
		char Src[255];
		char Exe[255];
		char Res[4096];
		bool Complie();
		int CpPID;
}	;

bool Complier_t::Complie()
{
	int St;
	if (CpPID=fork())
	{	//父进程
		if (CpPID==-1)
		{
			sprintf(Res,"无法创建子进程\n");
			return false;
		}
		wait(&St);
		FILE *FIN=fopen("Complie.log","r");
		char *p=Res;
		while (fscanf(FIN,"%c",p)!=EOF)
			++p;
		remove("Complie.log");
		if (St!=0)
			return false;
		return true;
	}
	else
	{
		//子进程
		int tmp=creat("Complie.log",S_IRWXO|S_IRWXG|S_IRWXU);
		dup2(tmp,STDOUT_FILENO);
		dup2(tmp,STDERR_FILENO);
		struct rlimit CPU_R;
		CPU_R.rlim_cur=__CTE;
		CPU_R.rlim_max=__CTE+1;
		setrlimit(RLIMIT_CPU,&CPU_R);
		struct rlimit RAM_R;
		RAM_R.rlim_cur=__CRE;
		RAM_R.rlim_max=__CRE+1024*1024;
		setrlimit(RLIMIT_AS,&RAM_R);
		exit(execlp("g++","g++",Src,"-o",Exe,(char *)(NULL)));
	}
}

#endif