#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>

//Goal: Child process will send an integer to parent process
//child process will communicate with parent process and send the parent process an integer

int main()

{

    int p[2];  //the fds are stored in p. 
    pipe(p);  //parent now has acess to p[1] for write and p[0] for read
    //when we do this it adds them to the nearest available fd.
    //we write to p in child and then parent can read it in p. 

    int pid = fork(); // a child process is created. 
    if (pid == 0){ //to be safe we can do a if p < 0 return an error or write to stderr. 
        //child process//
        //child process will only write it doesn't read we can close p[0]
        close(p[0]); //we can just close them because they are files
        printf("This is a child process\n");
        int value = 369;  //have to put the value in a variable.
        write(p[1], &value, sizeof(int));  //takes an addresss so we're type casting it into an addresss
        printf("child process wrote= %d\n", value);
        exit(0); //for it to finish

    }
    //everything else is parent process//
    //parent process will only read. since it's only reading we can close p[1] which writes.
       
        close(p[1]);
        int value; //where it's going to read the integer to. //value here is a different variable btw.
        read(p[0], &value, sizeof(int)); //reads  , needs address don't forget
        printf("this is the parent process \n");
        printf("parent process read = %d\n", value);
        wait(NULL); //parent has to wait for child

    return 0;


}