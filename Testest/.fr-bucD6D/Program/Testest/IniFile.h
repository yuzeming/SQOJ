/**
 * Testest 配置文件模块 V0.1
 * 2010-06-01
 * By yuzeming
 */
#ifndef __INIFILE
#define __INIFILE 1

#define __DefaultJudger "DefDiff"


const char INI_EXT[]=".ini";

class Test_t
{
	public:
		Test_t()
		{
			Next=NULL;
		}
		~Test_t()
		{
			if (Next!=NULL)
				delete(Next);
		}
		char Input[255];
		char Output[255];
		int TID;
		int MAXTime,MAXRAM; // S  K
		Test_t *Next;
}	;

class Prob_t
{
	public:
		Prob_t()
		{
			Test=NULL;
		}
		char InputFileName[255];
		char OutputFileName[255];
		char ProbName[255];
		// ComplieSet_t * Cs;
		// DiffSet_t	* Ds;
		char Judger[256];
		int TestTot;
		Test_t * Test;
		bool Load(char IniFile[]);
		void RunJudge(char Input[],char Output[],char Stdout[],char Ret[]);
}	;
void Prob_t::RunJudge(char Input[],char Output[],char Stdout[],char Ret[])
{
	if (fork())
	{
		wait(NULL);
		return ;
	}
	else
		execl(Judger,Judger,Input,Output,Stdout,Ret,(char *)NULL);
}

bool Prob_t::Load(char IniFile[])
{
	if (Test!=NULL)
		delete(Test);
	FILE *FINI=fopen(IniFile,"r");
	fscanf(FINI,"%s",ProbName);
	fscanf(FINI,"%s",InputFileName);
	fscanf(FINI,"%s",OutputFileName);
	fscanf(FINI,"%s",Judger);
	fscanf(FINI,"%d",&TestTot);
	if (strcmp(Judger,"(Default)")==0)
		strcpy(Judger,__DefaultJudger);
	char DIR[256];
	char Tmp[256];
	DIR[0]=0;
	GetDir(IniFile,DIR);
	if (TestTot<=0)	return false;
	Test=new Test_t;
	Test_t * ptr=Test;
	FixFileName(DIR,Judger,Tmp);
	strcpy(Judger,Tmp);
	for (int i=1;i<=TestTot;++i)
	{
		fscanf(FINI,"%s%s%d%d",ptr->Input,ptr->Output,&(ptr->MAXTime),&(ptr->MAXRAM));
		FixFileName(DIR,ptr->Input,Tmp);
		strcpy(ptr->Input,Tmp);
		FixFileName(DIR,ptr->Output,Tmp);
		strcpy(ptr->Output,Tmp);
		ptr->TID=i;
		if (i!=TestTot)
		{
			ptr->Next=new Test_t;
			ptr=ptr->Next;
		}
	}
	return true;
}

bool FindIniFile(char _Name[],char _Dir[],char Ret[])
{
	char Dir[255];
	char Name[255];

	Ret[0]=0;
	strcpy(Name,_Name);
	strcat(Name,INI_EXT);
	strcpy(Dir,_Dir);
	DIR * dir;
	struct dirent * ptr;
	while (true)
	{
		Dir[strlen(Dir)-1]=0;
		if (Dir[0]==0)	break;
		dir=opendir(Dir);
		while((ptr = readdir(dir))!=NULL)
		{

			if (strcmp(ptr->d_name,Name)==0)
			{
				strcat(Ret,Dir);
				strcat(Ret,"/");
				strcat(Ret,Name);
				return true;
			}
		}
		GetDir(Dir,Dir);
		closedir(dir);
	}
	return false;
}

#endif