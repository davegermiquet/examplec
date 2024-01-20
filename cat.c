#include<unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define BUFSIZE 30
#define PERMS 0666


void filecopy(int filesource, int filedestination);
void error (char * , ...);

int mygetchar(int fd);

int mygetchar(int input_file_descriptor)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;
    
    if (n==0) {
        n= read(input_file_descriptor,buf,sizeof buf);
        bufp  = buf;
    }
    if (--n >= 0){
        return (unsigned char) *bufp++;
    }
    else {
        n = 0;
        return EOF;
    }
}
int myputchar(int fd,char c) {
    write(fd,&c,1);
}

void filecopy(int input_file_descriptor, int output_file_descriptor) {
    int c;
    while ((c = mygetchar(input_file_descriptor))!= EOF){
        myputchar(output_file_descriptor,c);
    }
}

int main(int argc, char *argv[])
{   
    if (argc == 1){
        filecopy(0,1);
    }
    else {
        while (--argc > 0)
        {
            int fd = NULL;
            ++argv;
            if ((fd = open(*argv,O_RDONLY)) < 1) {
                printf("Cannot read file %s %d\n",*argv,fd);
                return -1;
            }
            else {
                filecopy(fd,0);
                close(fd);
            }
        }
    }
}


