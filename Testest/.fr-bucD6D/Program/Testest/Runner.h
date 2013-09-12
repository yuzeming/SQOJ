/**
 * Testest 运行模块 V0.1
 * 2010-06-01
 * By yuzeming
 */
#ifndef __RUNNER_T
#define __RUNNER_T 1

class Runner_t
{
	public:
		void ResetRet();
		char Exe[255];
		//char **Avge;
		char RootDir[255];
		char Res[255];
		int MaxTime,MaxRAM;
		int TimeUsed,RAMUsed;	//Ms K
		int ExeRet;
		void Run();
}	;

void Runner_t::ResetRet()
{
	TimeUsed=RAMUsed=0;
	ExeRet=0;
	Res[0]=0;
}

void Runner_t::Run()
{
	if (int RPID=fork())
	{
		int State;
		struct rusage Use;
		wait4(RPID,&State,WUNTRACED,&Use);
		ExeRet=State;
		RAMUsed=int(Use.ru_minflt/1024.0*sysconf(_SC_PAGESIZE));
		TimeUsed=Use.ru_utime.tv_sec*1000+Use.ru_utime.tv_usec/1000
				+Use.ru_stime.tv_sec*1000+Use.ru_stime.tv_usec/1000;
		switch(State)
		{
			case SIGKILL:		//超出内存限制 会被判这个
				sprintf(Res,"程序被终止");
				break;
			case SIGSEGV:
				sprintf(Res,"非法访问");
				break;
			case SIGFPE:
				sprintf(Res,"被零除");
				break;
			case SIGSTKFLT:
				sprintf(Res,"堆栈溢出");
				break;
			case SIGXCPU:
				sprintf(Res,"超时");
				break;
			case 0:
				//正常
				break;
			default :
				sprintf(Res,"未知错误");
				break;
		}
	}
	else
	{
		struct rlimit CPU_R;
		CPU_R.rlim_cur=MaxTime;
		CPU_R.rlim_max=MaxTime+1;
		setrlimit(RLIMIT_CPU,&CPU_R);
		struct rlimit RAM_R;
		RAM_R.rlim_cur=MaxRAM*1024;
		RAM_R.rlim_max=MaxRAM*1024+1024*1024;
		setrlimit(RLIMIT_AS,&RAM_R);
		chdir(RootDir);
		if (execl(Exe,Exe,(char *)NULL)!=0)
		{
			sprintf(Res,"执行 %s 失败\n",Exe);
			return ;
		}
		//Run
	}
}
#endif
