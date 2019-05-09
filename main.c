#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int st_c;
int nd_c;
int canigo = 0;

char* deletefront(char* argument)
{
	int ile = strlen(argument);
	int half = (ile/2);			
	char *tab;
	int j = 0;

	tab = (char*)malloc(sizeof(char) * (half + 2));

	for(int i = half; i <= ile; i++)	
		{
			tab[j] = argument[i];		
			j++;
		}
	tab[j] = 0;

	return tab;
}

////////////////////////////////

char* deleteback(char *argument)
{
	int ile = strlen(argument);
	int half = (ile/2);			
	char *tab;
	int j = 0;

	tab = (char*)malloc(sizeof(char) * (half + 2));

	for(int i = 0; i <= (half-1); i++)	
		{
			tab[j] = argument[i];		
			j++;
		}
	tab[j] = 0;

	return tab;
}


/////////////////////////////////

char* sklej(char *argument, char *argument2)
{	
	int mem = strlen(argument) + strlen(argument2);

	char *tab = (char*)malloc(sizeof(char) * (mem+2));

	tab[0] = 0;

	strcat(tab,argument2);
	strcat(tab," ");
	strcat(tab,argument);	

	return tab;
}

/////////////////////////////////

void send(int s)
{
	//printf("Test\n");
	kill(st_c,SIGINT);
	kill(nd_c,SIGINT);
}

void end(int s)
{
	canigo = 1;
}


void ign(int s)
{
};

/////////////////////////////////
int main(int argc, char* argv[])
{
char *argument = argv[1];
char *argument2 = argv[2];
if(argument2 == NULL)
	{
		argument2 = (char*)malloc(sizeof(char) * 2);
		argument2[0] = 0;
		strcat(argument2," ");
	}
int pid;
int status;
int ret;	
int ile;
int a = -1;
int mem = 0;
int x = 0;

sigset_t iset;
sigset_t zset;
sigset_t iset2;
struct sigaction act;

sigemptyset(&iset);
sigaddset(&iset, SIGTSTP);
sigprocmask(SIG_BLOCK, &iset, NULL);
act.sa_handler = &send;
act.sa_mask = iset;
act.sa_flags = 0;
sigaction(SIGINT, &act, NULL);

struct sigaction act2;

sigemptyset(&iset2);
act.sa_handler = SIG_IGN;
act.sa_mask = iset;
act.sa_flags = 0;
sigaction(SIGTSTP, &act, NULL);

/////////////////////////////////////////////////////////////////////////////////////
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
////////////////////////////////////////////////////////////////////////////////////

ile = strlen(argv[1]);

while( (ile % 2) == 0) //czy liczba jest potega dwojki ?
	ile = (ile /2);

if(ile > 1) //nie !
	{
		ile = strlen(argv[1]);

		int f = 1;
		while(f<=ile)
			f = f * 2;

		int roznica = f - ile;
		while(roznica > 0)
			{
				strcat(argv[1],"t");
				roznica = roznica - 1;
			}
		//printf("lancuch po operacjach wstepnych: %s\n",argv[1]);
	}		
////////////////////////////////////////////////////////////////////////////////////
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
///////////////////////////////////////////////////////////////////////////////////

ile = strlen(argv[1]);

setpgid(0,0);// Tworzy dla aktualnego procesu nowa grupe

if(ile <= 1)//procesy najnizsze (niepodzielne ze wzgledu na zbyt mala ilosc argumentow)
	{
	sigset_t iset;
	struct sigaction act;

	sigemptyset(&iset);
	act.sa_handler = &end;
	act.sa_mask = iset;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	while(1)
	{
		if(canigo == 1) break;
	}

	printf("moj pid: %d %s %s\n",getpid(),argument2,argument);
	exit(0);
	}

pid = fork();

if(pid > 0)
{
	st_c = pid;
	
	pid = fork();

	if(pid == 0)
	{

		char *tab = deletefront(argument);
		char *tab2 = sklej(argument,argument2);

		execl( "prog", "prog", tab, tab2, NULL);
		printf("ERROR, execl nie zadzialal\n");
		exit(0);

	}
	if(pid > 0)
	{

		nd_c = pid;
			
		wait(&status);
		wait(&status);

		printf("moj pid: %d %s %s\n",getpid(),argument2,argument);
		
		sigpending(&zset);
		x = sigismember(&zset,SIGTSTP);

		if(x == 1) printf("Nacisnieto ctrl+z\n");
		
		sigprocmask(SIG_UNBLOCK, &iset, NULL);

		exit(0);
	}	
}


if(pid == 0)
{

	char *tab = deleteback(argument);
	char *tab2 = sklej(argument,argument2);

	execl( "prog", "prog", tab, tab2, NULL);
	printf("ERROR, execl nie zadzialal\n");
	exit(0);
	
}



return (0);
}
