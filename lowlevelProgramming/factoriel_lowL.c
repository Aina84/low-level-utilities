#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){

	int n;
	int k;
	int m;
	if(argc>1){
		n=atoi(argv[1]);	
	}else{
		printf("veuillez entrer un nombre");
	}

	if(n<=1){
		printf("%d!=1",n);
		return 1;	
	}
	int pipeFd[2];
	pipe(pipeFd);

	pid_t pid = fork();

	if(pid==0){
		close(pipeFd[0]);
		char next[10];
		sprintf(next,"%d",n-1);
		dup2(pipeFd[1], STDOUT_FILENO);
		close(pipeFd[1]);
		execl(argv[0],argv[0],next,NULL);
		exit(1);
	}
	else if(pid>0){
		close(pipeFd[1]);
		
		wait(NULL);

		char buffer[20];

		int bytes = read(pipeFd[0], buffer, sizeof(buffer)-1);
		
		close(pipeFd[0]);
		if(bytes>0){
			buffer[bytes] = '\0';

			long long resultchild = atoll(buffer);
			long long r = n*resultchild;

			printf("%lld\n",r);

		}

	}
	printf();
	return 0;

}
