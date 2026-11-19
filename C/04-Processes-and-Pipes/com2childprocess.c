#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>

// Using pipe to communicate between 2 child processes.

//create 2 child processes, make child process 1 send hello to child process 2
//child process 1 is only writing it doesn't read
//child process 2 is only reading it doesn't write
//parent processes are not communicating with any child processes. 
// don't forget to wait.

int main()
{
    int p[2];
    pipe(p);

    int pid1 = fork();
    if(pid1 < 0){
        perror("fork failed\n"); //print error
        return 1; //to show it failed
    }
    if(pid1 == 0){
        //this is my child process 1 it doesn't read it writes
        close(p[0]); //close the read
        write(p[1], "Hello", 5);
        printf("child pro 1 wrote Hello \n");
        exit(0); //so it closes
    }
    
    int pid2 = fork();
    if(pid2 < 0){
        perror("fork failed\n"); //print error
        return 1; //to show it failed
    }
    if(pid2 ==0){
        //child process 2 will only read. it doesn't write
        close(p[1]);//close write
        char buffer;
        while(read(p[0], &buffer, sizeof(char))>0){ //while what is reading is not empty. 
            printf("%c", buffer); //reads one byte at a time and then appends it to the print/buffer.
        }
        
       printf("\n"); //this is so you can make a new line without it offending our loop. 
        exit(0); 
    }
    //outside the blocks is parent process (singular)
    close(p[1]); //we want to close both the read and write of parent process. //you can close p[1] before child process by the way.
    close(p[0]); 
    

    return 0;
}