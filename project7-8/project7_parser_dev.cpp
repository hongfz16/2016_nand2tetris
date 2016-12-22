#include <stdio.h>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
/*inline void _get_string(char *scr,char *obj)
{
	for (int i=0;scr[i]!='\0';++i) obj[i]=scr[i];
}*/ 
int main()//int argc,char *argv[])
{
	map<string,int> map_instr;
	char namein[100],nameout[100];
	scanf("%s",namein);
	scanf("%s",nameout);
	//_get_string(argv[1],namein);
	//_get_string(argv[2],nameout);
	freopen(namein,"r",stdin);
	freopen(nameout,"w",stdout);
	char a;
	string instr1,instr2,instr3,instrcom;
	map_instr["push"]=2;
	map_instr["pop"]=2;
	map_instr["add"]=1;
	map_instr["sub"]=1;
	map_instr["lt"]=1;
	map_instr["eq"]=1;
	map_instr["gt"]=1;
	map_instr["or"]=1;
	map_instr["and"]=1; 
	map_instr["neg"]=1;
	map_instr["not"]=1;
	map_instr["label"]=3;
	map_instr["if-goto"]=3;
	map_instr["goto"]=3;
	map_instr["function"]=4;
	map_instr["call"]=4;
	map_instr["return"]=1;
	a=getchar();
	while(a!=EOF)
	{
		instr1.clear();
		instr2.clear();
		instr3.clear();
		instrcom.clear();
		while(a==' ') a=getchar();
		while(a=='\n') a=getchar();
		while(a!=' '&&a!='\n'&&a!=EOF)
		{
			instr1+=a;
			a=getchar();
		}



		switch(map_instr[instr1])
		{
			case 2:a=getchar();
				while(a!=' ')
			{
				instr2+=a;
				a=getchar();
			}
			a=getchar();
			while(a!='\n'&&a!=' ')
			{
				instr3+=a;
				a=getchar();
			}
			instrcom=instr1+'_'+instr2+' '+instr3;
			break;
			case 1:instrcom=instr1+' '+"null";
			break;
			case 3:
				a=getchar();
				while(a!=' '&&a!='\n')
				{
					instr2+=a;
					a=getchar(); 
				} 
				 
				instrcom=instr1+' '+instr2;
				break;
			case 4:
				a=getchar();
				while (a!=' ')
				{
					instr2+=a;
					a=getchar();	
				}
				a=getchar();
				while (a!=' '&&a!='\n')
				{
					instr3+=a;
					a=getchar();
				}
				instrcom=instr1+'_'+instr2+'_'+instr3+' '+"null";

		}
		cout << instrcom << endl;
		a=getchar();
	}
	printf("end end\n");
	fclose(stdin);
	return 0;
}
