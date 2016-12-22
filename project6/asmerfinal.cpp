#include <cstdio>
#include <cstdlib>
#include <map>  
#include <iostream>  
#include <stdio.h>
#include <cstring>
#include <string>
using namespace std; 
int main()  
{	
	map<string,int> map1;
	map<string,int> map2;
	int address=16,num;
	int instruction[16]={0};
	int i=0,orz;
	char str[1000];
	char a,b;
	char namein[100],nameout[100];
	scanf("%s",namein);
	scanf("%s",nameout);
	FILE *myasm=freopen(namein,"r",stdin);
	if(myasm==NULL)
		printf("null\n");
	freopen(nameout,"w",stdout);
	int line=-1;
	string c;
	//string SP,LCL,ARG,THIS,THAT,SCREEN,KBD;
	//string R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15;
	map1["SP"]=0;
	map1["LCL"]=1;
	map1["ARG"]=2;
	map1["THIS"]=3;
	map1["THAT"]=4;
	map1["R0"]=0;
	map1["R1"]=1;
	map1["R2"]=2;
	map1["R3"]=3;
	map1["R4"]=4;
	map1["R5"]=5;
	map1["R6"]=6;
	map1["R7"]=7;
	map1["R8"]=8;
	map1["R9"]=9;
	map1["R10"]=10;
	map1["R11"]=11;
	map1["R12"]=12;
	map1["R13"]=13;
	map1["R14"]=14;
	map1["R15"]=15;
	map1["SCREEN"]=16384;
	map1["KBD"]=24576;
	a='\0';
	b=getchar();
	while(a!=EOF)
	{
		i=0;

		while(b==' '||b=='\n')
		{
			a=b;
			b=getchar();
		}
	while(b!='\n'&&b!=EOF)
	{
		if (b!=' ')
		{
			str[i]=b;
			a=b;
			b=getchar();
			i++;
	    }
	    else 
	    {
	    	a=b;
	    	b=getchar();

	    }
	    
	}
	for(int j=i;j<=999;j++)
	    	str[j]='\0';
	a=b;
	if(str[0]=='(')
	{
		string countlable;
		for(int i=1;str[i]^')';i++)
			countlable+=str[i];
		map2[countlable]=line+1;
	}
	else
		line++;
	}	
	fclose(stdin);




	freopen(namein,"r",stdin);
	a='\0';
	b=getchar();
	
	while(a!=EOF)
	{
		i=0;

		while(b==' '||b=='\n')
		{
			a=b;
			b=getchar();
		}
	while(b!='\n'&&b!=EOF)
	{
		if (b!=' '&&b!='\n')
		{
			str[i]=b;
			a=b;
			b=getchar();
			i++;
	    }
	    else 
	    {
	    	a=b;
	    	b=getchar();

	    }
	    
	}
	for(int j=i;j<=999;j++)
	    	str[j]='\0';
	a=b;

	if (str[0]=='@')
	{
		string memname;
		memname.clear();
		for (int l=1;str[l]^'\0'&&str[l]^'\n'&&str[l]^' ';l++)
			memname+=str[l];
		instruction[0]=0;
		if(str[1]>='0'&&str[1]<='9')
		{
			num=str[1]-'0';
			for (int j=2;j<=i&&str[j]>='0'&&str[j]<='9';j++)
				num=num*10+str[j]-'0';
			for (int k=15;k>=1;num>>=1,k--)
				instruction[k]=num&1;
		}
		else if (map1.find(memname)!=map1.end())
			{
				num=map1[memname];
				for (int k=15;k>=1;num>>=1,k--)
					instruction[k]=num&1;
			}
		
		else if(map2.find(memname)!=map2.end())
			{
				num=map2[memname];
				for (int k=15;k>=1;num>>=1,k--)
					instruction[k]=num&1;
			}

		else 
		{
			num=map1[memname]=address++;
			for (int k=15;k>=1;num>>=1,k--)
					instruction[k]=num&1;
		}
 		
	}
	else if (str[0]=='(')
	{
		continue;
	}
	else if (str[1]==';')
	{
		instruction[13]=0;
		instruction[14]=0;
		instruction[15]=0;
		if(str[3]=='G'&&str[4]=='T')
		{
			instruction[13]=0;
			instruction[14]=0;
			instruction[15]=1;
		}
		if(str[3]=='E'&&str[4]=='Q')
		{
			instruction[13]=0;
			instruction[14]=1;
			instruction[15]=0;
		}
		if(str[3]=='G'&&str[4]=='E')
		{
			instruction[13]=0;
			instruction[14]=1;
			instruction[15]=1;
		}
		if(str[3]=='L'&&str[4]=='T')
		{
			instruction[13]=1;
			instruction[14]=0;
			instruction[15]=0;
		}
		if(str[3]=='N'&&str[4]=='E')
		{
			instruction[13]=1;
			instruction[14]=0;
			instruction[15]=1;
		}
		if(str[3]=='L'&&str[4]=='E')
		{
			instruction[13]=1;
			instruction[14]=1;
			instruction[15]=0;
		}
		if(str[3]=='M'&&str[4]=='P')
		{
			instruction[13]=1;
			instruction[14]=1;
			instruction[15]=1;
		}
		if(str[0]=='D')
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=0;

		}
		if(str[0]=='0')
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;

		}
		instruction[0]=instruction[1]=instruction[2]=1;
		instruction[10]=instruction[11]=instruction[12]=0;

	}
	else
	{
		instruction[0]=instruction[1]=instruction[2]=1;
		instruction[13]=instruction[14]=instruction[15]=0;
		string orz2;
		for(int i=0;str[i]!='=';i++)
			orz2+=str[i];
		if(orz2=="A")
		{
			instruction[10]=1;
			instruction[11]=0;
			instruction[12]=0;
		}
		if(orz2=="M")
		{
			instruction[10]=0;
			instruction[11]=0;
			instruction[12]=1;
		}
		if(orz2=="D")
		{
			instruction[10]=0;
			instruction[11]=1;
			instruction[12]=0;
		}
		if(orz2=="MD")
		{
			instruction[10]=0;
			instruction[11]=1;
			instruction[12]=1;
		}
		if(orz2=="AM")
		{
			instruction[10]=1;
			instruction[11]=0;
			instruction[12]=1;
		}
		if(orz2=="AD")
		{
			instruction[10]=1;
			instruction[11]=1;
			instruction[12]=0;
		}
		if(orz2=="AMD")
		{
			instruction[10]=1;
			instruction[11]=1;
			instruction[12]=1;
		}
		
		
		c.clear();
		for (orz=0;str[orz]!='=';orz++);

		for(int i=orz+1;str[i]^'\n'&&str[i]^'\0';i++)
			c+=str[i];
		if(c=="0")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;

		}
		if(c=="1")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="-1")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=1;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;
		}
		if(c=="D")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=0;
		}
		if(c=="A")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=0;
		}
		if(c=="!D")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=1;
		}
		if(c=="!A")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=1;
		}
		if(c=="-D")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=1;
		}
		if(c=="-A")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=1;
			
		}
		if(c=="D+1")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=1;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
			
		}
		if(c=="A+1")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="D-1")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=1;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=0;
		}
		if(c=="A-1")
		{
			instruction[3]=0;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;
			
		}
		if(c=="D+A")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;
			
		}
		if(c=="D-A")
		{
		    instruction[3]=0;
			instruction[4]=0;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="A-D")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="D&A")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=0;
		}
		if(c=="D|A")
		{
			instruction[3]=0;
			instruction[4]=0;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=1;
		}
		if(c=="M")
		{
			instruction[3]=1;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=0;
		}
		if(c=="!M")
		{
			instruction[3]=1;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=1;
		}
		if(c=="-M")
		{
			instruction[3]=1;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="M+1")
		{
			instruction[3]=1;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="M-1")
		{
			instruction[3]=1;
			instruction[4]=1;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;
		}
		if (c=="D+M")
		{
			instruction[3]=1;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=0;
		}
		if(c=="D-M")
		{
			instruction[3]=1;
			instruction[4]=0;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=1;
			instruction[9]=1;
		}
		if(c=="M-D")
		{
			instruction[3]=1;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=1;
			instruction[9]=1;
		}
		if (c=="D&M")
		{
			instruction[3]=1;
			instruction[4]=0;
			instruction[5]=0;
			instruction[6]=0;
			instruction[7]=0;
			instruction[8]=0;
			instruction[9]=0;
		}
		if(c=="D|M")
		{
			instruction[3]=1;
			instruction[4]=0;
			instruction[5]=1;
			instruction[6]=0;
			instruction[7]=1;
			instruction[8]=0;
			instruction[9]=1;
		}


	}
	for (int l=0;l<=15;l++)
 			printf("%d",instruction[l]);
 		printf("\n");
 	}
 	fclose(stdin);
	return 0;
}


