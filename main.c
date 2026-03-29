#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
void printWelcome() {
    printf("\n");
    printf("  ██╗    ██╗ █████╗ ██████╗ ███╗   ███╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
    printf("  ██║    ██║██╔══██╗██╔══██╗████╗ ████║██╔════╝██║  ██║██╔════╝██║     ██║\n");
    printf("  ██║ █╗ ██║███████║██████╔╝██╔████╔██║███████╗███████║█████╗  ██║     ██║\n");
    printf("  ██║███╗██║██╔══██║██╔══██╗██║╚██╔╝██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
    printf("  ╚███╔███╔╝██║  ██║██║  ██║██║ ╚═╝ ██║███████║██║  ██║███████╗███████╗███████╗\n");
    printf("   ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
    printf("\n");
    printf("          YOUR SHELL. YOUR RULES. YOUR WORLD.  [ WarmShell v2.0 ]\n");
    printf("\n");
}


void printPrompt() {
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("WarmShell %s> ",cwd);
    fflush(stdout);
}
#define MAX_ARGS 100
void parse(char *input,char*args[]){
  int index=0;
  char *token;
  char *saveptr;
  token=strtok_r(input," ",&saveptr);
  while(token!=NULL && index<MAX_ARGS-1){
    args[index++]=token;
    token=strtok_r(NULL," ",&saveptr);
  }
  args[index]=NULL;

}

int main() {
  printWelcome();
  char input[1025];
    while(1){
    printPrompt();
    if(fgets(input,sizeof(input),stdin)==NULL){break;}
    input[strcspn(input, "\n")] = 0;
    if(input[0]=='\0') continue;
    char *args[MAX_ARGS];
    parse(input,args);
    if(strcmp(args[0],"exit")==0) break;
    if(strcmp(args[0],"cd")==0){
      if(args[1]==NULL) chdir(getenv("HOME"));
      else chdir(args[1]);
      continue;
    }

    pid_t pid=fork();
    if(pid==0){
      execvp(args[0],args);
      perror("the execvp failed");
      exit(1);
    }
    else if(pid>0){
      wait(NULL);
    }
    else{
    perror("fork failed");
    printf("Not a command for now \n");
    }
  }
    return 0;
}
