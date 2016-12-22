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
	int functioncount; 
	map<string,string>	map_simp;
	map<string,string>  map_lib;
	map<string,int> map_nvars;
	map<string,int> map_nargs;
	char namein[100],nameout[100];
	char ins[100]={'\0'};
	char poi;
	string instr,instr1,instr2;
	string functionname1,functionname2;
	int num=0,count;
	int labelcount=0;
	scanf("%s",namein);
	scanf("%s",nameout);
//	_get_string(argv[1],namein);
//	_get_string(argv[2],nameout);
	FILE *fp1,*fp2;
	fp1=fopen(namein,"r");
	if(fp1==NULL)
	printf("null\n");
	
	freopen(nameout,"w",stdout);
	map_simp["push_local"]="LCL";
	map_simp["push_this"]="THIS";
	map_simp["push_that"]="THAT";
	map_simp["push_argument"]="ARG";
	map_simp["push_temp"]="5";
	map_simp["pop_local"]="LCL";
	map_simp["pop_this"]="THIS";
	map_simp["pop_that"]="THAT";
	map_simp["pop_argument"]="ARG";
	map_simp["pop_temp"]="5";
	map_simp["push_pointer"]="3";
	map_simp["pop_pointer"]="3";
	map_simp["pop_static"]="16";
	map_simp["push_static"]="16";
	map_simp["eq"]="JEQ";
	map_simp["gt"]="JLT";
	map_simp["lt"]="JGT";
	map_lib["push_constant"]="push_constant.asm"; 
	map_lib["push_local"]="push.asm";
	map_lib["push_this"]="push.asm";
	map_lib["push_that"]="push.asm";
	map_lib["push_argument"]="push.asm";
	map_lib["push_temp"]="push_temp.asm";
	map_lib["pop_local"]="pop.asm";
	map_lib["pop_this"]="pop.asm";
	map_lib["pop_that"]="pop.asm";
	map_lib["pop_argument"]="pop.asm";
	map_lib["pop_temp"]="pop_temp.asm";
	map_lib["add"]="add.asm";
	map_lib["sub"]="sub.asm";
	map_lib["pop_pointer"]="pop_temp.asm";
	map_lib["push_pointer"]="push_temp.asm";
	map_lib["pop_static"]="pop_temp.asm";
	map_lib["push_static"]="push_temp.asm";
	map_lib["eq"]="eq.asm";
	map_lib["lt"]="eq.asm";
	map_lib["gt"]="eq.asm";
	map_lib["not"]="not.asm";
	map_lib["neg"]="neg.asm";
	map_lib["and"]="and.asm";
	map_lib["or"]="or.asm";
	map_lib["label"]="label.asm";
	map_lib["if-goto"]="if-goto.asm"; 
	map_lib["goto"]="goto.asm";
	map_lib["function"]="function.asm";
	map_lib["call"]="call.asm";
	map_lib["return"]="return.asm";
	int endjug=0;
	while(endjug==0)
	{
		instr1.clear();
		instr2.clear();
		for(int i=0;i<=1;i++)
		{	
			for (int j=0;j<=30;j++)
			{
				ins[j]='\0';
			}
			fscanf(fp1,"%s",&ins);
			instr.clear();
			instr+=ins;
		
			//instr1.clear();
			//instr2.clear();
			if(ins[0]<='9'&&ins[0]>='0')
			{
				num=0;
				for (count=0;ins[count]!='\0';count++)
				{
					num=num*10+ins[count]-'0';
				}
				instr2=instr;
			}
			else if(instr=="null")
			instr2=instr;
			else if (instr=="end")
			endjug=1;
			else if (ins[0]<='Z'&&ins[0]>='A')
			instr2=instr; 
			else if (ins[0]=='f'&&ins[1]=='u')
			{
				for (int k=0;k<=7;k++) instr1+=ins[k];
				functionname1.clear();
				for (int k=9;ins[k]!='_';k++)
				functionname1+=ins[k];
//				int functioncount;
				for (functioncount=0;ins[functioncount]!='\0';functioncount++);
				map_nvars[functionname1]=ins[functioncount-1]-'0';
			}
			else if (ins[0]=='c'&&ins[1]=='a')
			{
				for (int k=0;k<=3;k++) instr1+=ins[k];
				functionname2.clear();
				for (int k=5;ins[k]!='_';k++)
				{
					functionname2+=ins[k];
				}
//				int functioncount;
				for (functioncount=0;ins[functioncount]!='\0';functioncount++);
				map_nargs[functionname2]=ins[functioncount-1]-'0';
			}
			else
			instr1=instr;
		}	


		if(endjug==0)
		{
		const char* instrchar=map_lib[instr1].c_str();
		fp2=fopen(instrchar,"r");
		
		fscanf(fp2,"%c",&poi);
		while (poi!='*')
		{
			
			while (poi!='~'&&poi!='*')
			{
				putchar(poi);
				fscanf(fp2,"%c",&poi);
			}
			if (poi!='*')
			{ 
			fscanf(fp2,"%c",&poi);
			while (poi!='!')
			{
				if(poi!='#'&&poi!='$'&&poi!='%'&&poi!='^'&&poi!='['&&poi!=']'&&poi!='<'&&poi!='>'&&poi!='}'&&poi!='?')
				{
					putchar(poi);
				}
				else if(poi=='#')
				{
					printf("%d",num);
				}
				else if(poi=='$')
				{
					cout<<map_simp[instr1];
				}
				else if(poi=='%')
				{
					printf("%d",labelcount);
				}
				else if(poi=='^')
				{
					cout<<instr2;
				}
				else if(poi=='[')
				{
					printf("%d",map_nvars[functionname1]);
				}
				else if(poi==']')
				{
					printf("%d",map_nargs[functionname2]);
				}
				else if(poi=='<')
				{
					cout<<functionname1;
				}
				else if(poi=='>')
				{
					cout<<functionname2;
				}				
				else if(poi=='?')
				{
					if (map_nargs[functionname2]==0)
					{
						printf("@SP\nM=M+1");
					}
				}
				else if(poi=='}')
				{
					if (map_nargs[functionname2]==0)
					printf("1");
					else 
					printf("%d",map_nargs[functionname2]);
				}
				fscanf(fp2,"%c",&poi);
			}
			}
			fscanf(fp2,"%c",&poi);
		}
		
		fclose(fp2);
		}
		labelcount++;
	}
	
	fclose(fp1);
	return 0;
}
