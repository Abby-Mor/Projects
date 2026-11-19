//to get bidirectional communication you need 2 pipes. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/wait.h>
//Parent process wil send an integer n
//child process will return sum of n natural numbers


//child process will receive a value n
//it will then compute sum of n natural numbers
//then it'll writ the result to parent. 
//in parent process, parent process will write/ send value n. 
//it will then receive the sum of n natural numbers from child.
//this is bidirectional connection 2 pipes are needed. 
//we need a pipe to establish connection between child to parent
//we need another pipe to establish connection between parent and child
int main(){
    //we need 2 arrays of fd for each pipe
    int pc[2]; // use for parent(write) child(read)  
    int cp[2]; //use for child(write) parent(read)
    pipe(pc);
    pipe(cp);

    int pid = fork();
    if (pid ==0){
        //this is the child process
        //child process will first read from pc[0], read value n, it'll never write to pc[1]
        close(pc[1]);
        int n;
        read(pc[0],&n, sizeof(int));
        printf("n = %d\n", n); // just to debug and make sure it received n
        close(pc[0]); //this is because we are done using it
        int res = (n*(n+1))/2;
        //then child process will write/ send results to parent process, it'll write to cp[1], it never reads from cp[0]
        close(cp[0]);
        write(cp[1], &res, sizeof(int));
        close(cp[1]); //once done close the files
        exit(0);
    }
    //this is my parent process
    //write/ send value n to child it writes to pc[1], never reads from pc[0]
    close(pc[0]);
    int n = 5;
    write(pc[1], &n, sizeof(int));
    close(pc[1]);
    //it will receive the sum of the natural number it reads. it never writes to cp[1]
    close(cp[1]);
    int res;
    read(cp[0], &res, sizeof(int)); //when there is nothing read will wait. 
    close(cp[0]);
    printf("result = %d\n", res);



    return 0;
}