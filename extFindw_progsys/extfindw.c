#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096
#define MAX_PATH 1024
#define MAX_FILENAME 1024

int main(int argc, char* argv[]){

	if(argc!=3){
		printf("Invalid input:\n Only input: %s <folder_path> <researched_word>",argv[0]);
		return 1;
	}
	DIR* dossier;
	struct dirent *entree;
	char* DIR_PATH = argv[1];
	char* researched_word = argv[2];
	char buffer[BUFFER_SIZE];
	char temp_path[MAX_PATH];
	ssize_t bytes_read;

	dossier = opendir(DIR_PATH);

	if(dossier==NULL){
		printf("Error cannot open directory");
		return 1;
	}

	while((entree=readdir(dossier))!=NULL){
		if(strcmp(entree->d_name, ".")==0 && strcmp(entree->d_name, "..")==0){
			continue;
		}
		char filepath[MAX_PATH];
		printf("%s boucle 1 \n",entree->d_name);
		snprintf(filepath, sizeof(filepath),"%s/%s",DIR_PATH,entree->d_name);
		int fd = open(filepath, O_RDONLY);
		if(fd<0){
			printf("cannot open file");
			close(fd);
			return 1;
		}
		snprintf(temp_path,sizeof(temp_path),"./%s/%s",DIR_PATH, "%s.tmp",entree->d_name);
		int infd = open(temp_path, O_WRONLY | O_CREAT | O_TRUNC , 0644);
		

		while((bytes_read=read(fd, buffer, sizeof(buffer)))>0){
			char* ptr = buffer;
			char* end = buffer+bytes_read;
			char* pos;

			while((pos = strstr(ptr, researched_word))!=NULL){
				write(infd,ptr,pos-ptr);
				printf("1 trouver dans %s \n", filepath);
				ptr = pos+strlen(researched_word);
				
			}
			write(infd,ptr,end-ptr);

		}
		
		close(fd);
		close(infd);

		rename(temp_path, entree->d_name);

	}

	closedir(dossier);

	return 0;
}

