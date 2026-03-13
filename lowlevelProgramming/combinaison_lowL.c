#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int n, k;
	if(argc == 3){
		n=atoi(argv[1]);
		k=atoi(argv[2]);

		if(k==0 || k==n){
			printf("1");
			return 0;
		}
		int p1[2], p2[2];
		pipe(p1); pipe(p2);

		if(fork()==0){
			close(p1[0]); dup2(p1[1], STDOUT_FILENO);
			char s_n[10], s_k[10];
			sprintf(s_n, "%d", n-1); sprintf(s_k,"%d",k);
			execl(argv[0],argv[0],s_n, s_k, NULL);
			exit(0);
		}
		if(fork()==0){
			close(p2[0]); dup2(p2[1], STDOUT_FILENO);
			char s_n[10], s_k[10];
			sprintf(s_n, "%d", n-1); sprintf(s_k, "%d", k-1);
			execl(argv[0],argv[0],s_n, s_k, NULL);
			exit(0);
		}
		close(p1[1]);close(p2[1]);
		wait(NULL); wait(NULL);
		
		char b1[20], b2[20];
		int r1 = read(p1[0], b1, 19); b1[r1] = '\0';
		int r2 = read(p2[0], b2, 19); b2[r2] = '\0';

		printf("%lld", atoll(b1)+atoll(b2));
		return 0;
	}
	printf("Entrer n : \n");
	scanf("%d", &n);
	printf("Entrez k : ");
	scanf("%d",&k);

	if(k<0 || k>n){
		printf("0\n");
		return 0;
	}
	int p[2];
	pipe(p);
	if(fork()==0){
		close(p[0]); dup2(p[1],STDOUT_FILENO);
		char s_n[10], s_k[10];
		sprintf(s_n, "%d", n);sprintf(s_k,"%d",k);
		execl(argv[0],argv[0],s_n,s_k, NULL);
		exit(0);
	}
	close(p[1]);
	wait(NULL);
	char res[20];
	int r = read(p[0], res, 19); res[r] = '\0';
	printf("\nC(%d, %d) = %s\n",n, k, res);
	return 0;
}
