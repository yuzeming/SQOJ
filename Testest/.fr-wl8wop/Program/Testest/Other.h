/**
 * Testest 文件操作/其他模块 V0.1
 * 2010-06-01
 * By yuzeming
 */
#ifndef __OTHER
#define __OTHER 1

#define BUFFER_SIZE 1024

bool CopyFile(char ToFile[],char FormFile[])
{
	FILE *IN=fopen(FormFile,"r");
	FILE *OUT=fopen(ToFile,"w");
	char BUFF[BUFFER_SIZE];
	int byte=1;
	while (byte)
	{
		byte=0;
		while (byte<BUFFER_SIZE&&fscanf(IN,"%c",&BUFF[byte])!=EOF)
			++byte;
		for (int i=0;i<byte;++i)
			fprintf(OUT,"%c",BUFF[i]);
	}
	fclose(IN);
	fclose(OUT);
	return true;
}

void GetDir(char Path[],char Dir[])
{
	int len=strlen(Path);
	while (Path[len-1]!='/')
		--len;
	strncpy(Dir,Path,len);
	Dir[len]=0;
}

void GetMainFileName(char Path[],char MFN[])
{
	int len1=strlen(Path);
	int len2=len1;
	while (Path[len1-1]!='/'&&len1)
		--len1;
	while (Path[len2-1]!='.'&&len2>len1)
		--len2;
	if (len1==len2)
		len2=strlen(Path);
	strncpy(MFN,&Path[len1],len2-len1-1);
	MFN[len2-len1-1]=0;
}

void GetExtFileName(char Path[],char EFN[])
{
	int len=strlen(Path);
	while (Path[len-1]!='/'&&Path[len-1]!='.')
		--len;
	EFN[0]=0;
	strcat(EFN,&Path[len]);
}

void FixFileName(char Root[],char Path[],char Ret[])
{
	if (Path[0]=='/')
	{
		strcpy(Ret,Path);
		return ;
	}
	char *p=Path;
	if (Path[0]=='.')	p+=2;
	Ret[0]=0;
	strcat(Ret,Root);
	if (Root[strlen(Root)-1]!='/')
		strcat(Ret,"/");
	strcat(Ret,p);
}

void PrintFile(char File[])
{
	FILE * F=fopen(File,"r");
	char Tmp[256];
	fgets(Tmp,255,F);
	int Len=strlen(Tmp);
	if (Tmp[Len-1]=='\n')
		Tmp[Len-1]=0;
	printf("%s",Tmp);
	fclose(F);
}

#endif