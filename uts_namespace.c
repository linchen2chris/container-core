#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

char *const child_args[] = {"/bin/sh", NULL};

int child_main(void* args) {
  printf("in child process\n");
  sethostname("new_host", 8);
  execv(child_args[0], child_args);
  return 1;
};

int main(int argc, char *argv[]) {
  printf("main process \n");
  int child_pid=clone(child_main, child_stack+STACK_SIZE, SIGCHLD|CLONE_NEWUTS,NULL);
  waitpid(child_pid,NULL, 0);
  printf("end process \n");
  return 0;
}
