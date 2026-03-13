#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

	int n = argc, fd, it_count=0;
	const char* file_path = argv[1], *researched_word = argv[2];
	char buff[4050];
	char arrof_index[4050]="";
	char* p_index;

	//validate input length
	if(n>3 || n<3){
		printf("Input error: input entry must be %s <file_path> <researched_word>\n",argv[0]);
		return 1;
	}

	//get fd of the targeted file
	
	fd = open(file_path,O_RDONLY);
	if(fd == -1){
		printf("Error occured: can't open the file\n");
		close(fd);
		return 1;
	}

	//read file

	read(fd, buff, sizeof(buff));
 	
	//searching the word in buff
	p_index = buff;
	while((p_index=strstr(p_index, researched_word))!=NULL){	
		it_count++;
		char temp[20];
		int index = p_index-buff;
		sprintf(temp,",%d",index);
		it_count==1 ? sprintf(temp, "%d", index) : sprintf(temp, ", %d", index);
		strcat(arrof_index,temp);
		p_index+=strlen(researched_word);
	}

	printf("Result ==> Iteration count %d , found at [%s]\n",it_count,arrof_index);

	close(fd);

	return 0;

}	
