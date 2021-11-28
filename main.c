#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<math.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

static int *glob_var;
int x = 1;
int loc;
static int *glob_loc;
int main(int argc, char *argv[])
{

    //Next two variable are shared variable between processes
    //this variable gives number to all tree processes
    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    //this variable tells us leaves left child or right child
    glob_loc = mmap(NULL, sizeof *glob_loc, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *glob_var = 1;
    int n,ab;
    int leftchild,rightchild;
    int status=0;
    pid_t wpid;
    //scanf("%d",&n);

    long arg = strtol(argv[1], NULL, 10);//argument to int

    //argument check
    if(argc>2){
        printf("Too many Argument");
        exit(0);
    }

if(argc<2){
   printf("Please Give Argument");
        exit(0);
    }
    //In this loop we creating process tree
    for(int i=1;i<arg;i++)
    {
        printf("[%d] pid %d ,ppid %d\n",x,getpid(),getppid());fflush(stdout);

        //creating left child
        leftchild=fork();
        if(leftchild==0){
            *glob_loc =1;
            loc = *glob_loc;
            *glob_var+=1;
            x = *glob_var;
            printf("[%d] pid %d created left child with pid %d\n",x/2,getppid(),getpid());fflush(stdout);
        }
        //creating right child
        if(leftchild != 0){
            rightchild=fork();
            wait(NULL);
        }
        //printing right child created
        if(rightchild==0 && leftchild !=0) {
            *glob_var+=1;
            x = *glob_var;
            *glob_loc =0;
            loc = *glob_loc;
            printf("[%d] pid %d created right child with pid %d\n",x/2,getppid(), getpid());
            fflush(stdout);
        }
        if(leftchild!=0 && rightchild!=0) {
            break;
        }

    }

    //wait children
    if(leftchild!=0 && rightchild!=0) {
        while ((wpid = wait(&status)) > 0);
        sleep(3);
        if(x%2==0 && x != 1){
            printf("[%d] left child %d of %d exited with status %d\n",x/2,getpid(),getppid(),x);
        }
        if(x%2==1 && x != 1){
            printf("[%d] right child %d of %d exited with status %d\n",x/2,getpid(),getppid(),x);
        }
        wait(NULL);
    }

    //leaves print process ids an parent id and exited
    else{
        sleep(1);
        printf("[%d] pid %d ,ppid %d\n",x,getpid(),getppid());fflush(stdout);
        sleep(2);
        if(loc==1){
            printf("[%d] left child %d of %d exited with status %d\n",x/2,getpid(),getppid(),x);
        }
        if(loc==0){
            printf("[%d] right child %d of %d exited with status %d\n",x/2,getpid(),getppid(),x);
        }
        wait(NULL);
    }

    //free allocated memory map
    munmap(glob_var, sizeof *glob_var);

    waitpid(leftchild,&ab,0);
    waitpid(rightchild,&ab,0);

    return 0;
}
