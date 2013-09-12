/**
 * Testest 评测模块 V0.1
 * 2010-06-01
 * By yuzeming
 */
#ifndef __JUDGE
#define __JUDGE 1

void Judge(Runner_t RNT,Prob_t PBT,char Dir[])
{
	printf("开始评测...\n");
	Test_t *pt;
	pt=PBT.Test;
	char IN_FILE[256];IN_FILE[0]=0;
	char OUT_FILE[256];OUT_FILE[0]=0;
	char RET_FILE[256];RET_FILE[0]=0;
	strcpy(IN_FILE,Dir);
	strcat(IN_FILE,PBT.InputFileName);
	strcpy(OUT_FILE,Dir);
	strcat(OUT_FILE,PBT.OutputFileName);
	strcpy(RNT.RootDir,Dir);
	strcpy(RET_FILE,Dir);
	strcpy(RET_FILE,"RetTmp.txt");
	while (pt!=NULL)
	{
		printf("测试点 %d : ",pt->TID);
		RNT.ResetRet();
		CopyFile(IN_FILE,pt->Input);
		RNT.MaxRAM=pt->MAXRAM;
		RNT.MaxTime=pt->MAXTime;
		RNT.Run();
		if (RNT.ExeRet)
			printf("%s",RNT.Res);
		else
		{
			PBT.RunJudge(pt->Input,OUT_FILE,pt->Output,RET_FILE);
			PrintFile(RET_FILE);
		}
		printf("\t内存:%d KB 用时: %d MS\n",RNT.RAMUsed,RNT.TimeUsed);
		remove(IN_FILE);
		remove(OUT_FILE);
		pt=pt->Next;
	}
	printf("评测结束。\n");
}

#endif