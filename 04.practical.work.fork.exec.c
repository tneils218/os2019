#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
  int status, pid1, pid2;
  printf("This is main before fork()\n");
  pid1 = fork();
  if(pid1 == 0){
    printf("\tThis is the first child\n\tNow run \"ps -ef\"\n");
    char* args[] = {"/bin/ps", "-ef", NULL};
    if(execvp("/bin/ps", args) < 0){
      printf("Fail to execute \"ps -ef\"\n");
    }
  }
  else {
    waitpid(pid1, NULL, 0);
    printf("This is parent after fork, child is %d\n\tContinue to create another child\n", pid1);
    pid2 = fork();
    if(pid2 == 0){
      printf("\tThis is the second child\n\tNow run \"free -h\"\n");
      char* args[] = {"/usr/bin/free", "-h", NULL};
      if(execvp("/usr/bin/free", args) < 0){
        printf("Fail to execute \"free -h\"\n");
      }
    }
    else {
      printf("This is parent after 2 forks, second child is %d\nNothing to do more.\n", pid2);
      waitpid(pid2, NULL, 0);
    }
  }
  return 0;
}
