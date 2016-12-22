//by li-rj 2016-10-20
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

map<string,int> lab;
map<string,int> var;
map<string,string> ist;
int ins[16];
int line;
int pot=0;
char s[1000];
char aname[100];
char *sname="tmp.spf";
char oname[100];
inline void simplify()
{
	freopen(aname,"r",stdin);
	freopen(sname,"w",stdout);
	char t1,t2;
	t1='\0';t2=getchar();
	while(t2!=EOF)
	{
		if(t1=='/'||t2=='/')
		{
			gets(s);
			t1='\n';t2=getchar(); 
			continue;
		}
		if((t1^'\n'||t2^'\n')&&t2^' ')
			putchar(t2);
		t1=t2;
		t2=getchar();
	}
}
inline void AT()
{
	++line;int d=0,i;ins[15]=0;
	string _name;
	if(s[1]<='9'&&s[1]>='0')
	{
		for(i=1;'0'<=s[i]&&s[i]<='9';++i) d=d*10+s[i]-'0';
		for(i=0;d;d>>=1) ins[i++]=d&1;
	}
	else
	{
		_name.clear();
		for(i=1;s[i]^'\n'&&s[i]^'\0';++i) _name+=s[i];
		if(lab.find(_name)!=lab.end())
			for(i=0,d=lab[_name];d;d>>=1) ins[i++]=d&1;
		else if(var.find(_name)!=var.end())
			for(i=0,d=var[_name];d;d>>=1) ins[i++]=d&1;
		else 
			for(int i=0,d=var[_name]=pot++;d;d>>=1) ins[i++]=d&1;	
	}
	for(int i=15;i>=0;--i) putchar(ins[i]+'0');
	putchar('\n');
}
inline void LABAL()
{
	string lable;
	for(int i=1;s[i]^')';++i) lable+=s[i];
	lab[lable]=line;
}
inline void JUMP()
{
	string inst,code;
	inst.clear();
	int i;
	for(i=0;s[i]^';';++i) inst+=s[i];
	i+=2;
	switch(s[i])
	{
		case 'M':ins[0]=ins[1]=ins[2]=1;break;
		case 'N':ins[0]=ins[2]=1;break;
		case 'E':ins[1]=1;break;
		case 'G':ins[0]=1;
				 if(s[i+1]=='E') ins[1]=1;
				 break;
		case 'L':ins[2]=1;
				 if(s[i+1]=='E') ins[1]=1;
				 break;
	}
	code=ist[inst];
	ins[15]=ins[14]=ins[13]=1;
	for(int i=0;i^7;++i) ins[12-i]=code[i]-'0';
	for(int i=15;i>=0;--i) putchar(ins[i]+'0');
	putchar('\n');
}
inline void INST()
{
	string inst,code;int i;inst.clear();
	for(i=0;s[i]^'=';++i)
	{
		switch(s[i])
		{
			case 'M':ins[3]=1;break;
			case 'D':ins[4]=1;break;
			case 'A':ins[5]=1;break;
		}
	}
	for(++i;s[i]^'\0'&&s[i]^'\n';++i) inst+=s[i];
	code=ist[inst];
	ins[15]=ins[14]=ins[13]=1;
	for(int i=0;i^7;++i) ins[12-i]=code[i]-'0';
	for(int i=15;i>=0;--i) putchar(ins[i]+'0');
	putchar('\n');
}
inline void Asmer()
{
	string lable;
	freopen(sname,"r",stdin);
	freopen("con","w",stdout);
	freopen(oname,"w",stdout);
	while(scanf("%s",s)!=EOF)
	{
		if(s[0]=='(') continue;		
		for(int i=0;i!=16;++i) ins[i]=0;
		if(s[0]=='@') AT();
		else if(s[1]==';') JUMP();
		else INST();
	}
}
inline void _init()
{
	printf("enter the source file name:");
	scanf("%s",aname);
	printf("enter the object file name:");
	scanf("%s",oname);
	freopen("ins_set.txt","r",stdin);
	string inst,code;
	for(int i=1;i<=28;++i) 
	{
		cin>>inst>>code;
		ist[inst]=code;
	}
	var["SCREEN"]=1<<14; var["KBD"]=24576;
	freopen(sname,"r",stdin);
	while(scanf("%s",s)!=EOF)
	{
		if(s[0]=='(') LABAL();
		else ++line;
	}	
	fclose(stdin);

}
int main()
{
	_init();
	simplify();
	Asmer();
	return 0;
}
