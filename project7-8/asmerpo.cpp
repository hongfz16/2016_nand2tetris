#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;
/*inline void _get_string(char *scr,char *obj)
{
	for (int i=0;scr[i]!='\0';++i) obj[i]=scr[i];
}*/
int main()//int argc,char *argv[])
{
	char namein[100],c,nameout[100];
	scanf("%s",namein);
	scanf("%s",nameout);
	//_get_string(argv[1],namein);
	//_get_string(argv[2],nameout);
	freopen(namein,"r",stdin);
	freopen(nameout,"w",stdout); 
	c=getchar();
	while(c!=EOF)
	{	
		while(c=='/')
		{
			//c=getchar();
			while(c!='\n')
				c=getchar();
			//c=getchar();
		}
		printf("%c",c);
		c=getchar();
	}
	fclose(stdin);
}
