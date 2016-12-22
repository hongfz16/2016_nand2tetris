#include "cstdio"
#include "cstdlib"
using namespace std;
char namein[100],nameout[100];
char cmd[1000];
int main()
{
	printf("Enter the name of your source file:");
	scanf("%s",namein);
	printf("Enter the name of your object file:");
	scanf("%s",nameout);
	sprintf(cmd,"asmerpo.exe %s temp1.vm",namein);
	system(cmd);
	system("project7_parser_dev.exe temp1.vm temp2.vm");
	sprintf(cmd,"project7_translator_dev.exe temp2.vm %s",nameout);
	system(cmd);
	system("del temp1.vm");
	system("del temp2.vm");
	return 0;
}
