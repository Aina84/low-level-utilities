#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>



int main (int argc , char *argv[])
{

    int n = argc, in, out;

    const char *ifile_path = argv[1], *ffile_path = argv[2];
    
    char buff[5200];
    
    ssize_t bytes_read;


    //validate argv length

    if(n!=3){
	printf("Invalid input: Only input: %s <original_ifilepath> <output_ffilepath> ",argv[0]);
	return 0;	
    }



    //get file descriptors, create output file if it not exists

    in = open(ifile_path, O_RDONLY);
    if(in == -1){
	printf("Error occured while trying to open ifile");
	close(in);
	return 1;
    }

    out = open(ffile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(out == -1){
	printf("Error occured while trying to open ffile");
	close(out);
	return 1;
    }

    //read ifile into buff, write buff into ffile	

    while((bytes_read=read(in, buff, sizeof(buff)))>0){
	write(out, buff, bytes_read);
    }

    //close files by fd

    close(in);

    close(out);
    
    printf("copy done successfully\n");

    return 0;

 }
