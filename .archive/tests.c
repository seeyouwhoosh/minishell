#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define RED \e[1;31m
#define NONE \e[0;0m


void msg_before_dying(int sig);
void kill_ass(int sig);

void traverse(char *fn, int indent) {
  DIR *dir;
  struct dirent *entry;
  int count;
  char path[1025];
  struct stat info;

  for (count=0; count<indent; count++) printf("   ");
  printf("%s\n", fn);

  if ((dir = opendir(fn)) == NULL)
    perror("opendir() error");
  else {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_name[0] != '.') {
        strcpy(path, fn);
        strcat(path, "/");
        strcat(path, entry->d_name);
        if (stat(path, &info) != 0)
          fprintf(stderr, "stat() error on %s: %s\n", path,
                  strerror(errno));
        else if (S_ISDIR(info.st_mode))
               traverse(path, indent+1);
      }
    }
    closedir(dir);
  }
}

int main(int ac, char **av, char **env)
{
	
	/* SIGNAL THINGIES */
		signal(SIGINT, msg_before_dying);
	/* char *getenv(const char *name); */
	for (size_t i = 0; env[i]; i++)
		printf("%s\n", env[i]); // aquí se imprimen todas las environmental variables
	char *envs = getenv("PATH");
	printf("\e[0;31mGETENV: %s\n\e[0;0m", envs);

	/* char *getcwd(char *buf, size_t size);
	int chdir(const char *path); */
	char *cwd = malloc(100);
	char *changed = malloc(100);
	getcwd(cwd, 100);
	printf("\e[0;32mCURRENT WORKING DIRECTORY: %s\n\e[0;0m", cwd);
	if (chdir(".."))
		perror("chdir");
	getcwd(changed, 100);
	printf("\e[0;32mCURRENT WORKING DIRECTORY: %s\n\e[0;0m", changed);
	chdir(cwd);

	/* pid_t fork(void); */
	int	nb = 0;
	pid_t pid = fork();
	if (pid < 0)
		printf("\e[0;33mERROR: %d\n\e[0;0m", pid);
	if (!pid)
	{
		printf("\e[0;33mCHILD PROCESS: %d\n\e[0;0m", pid);
		printf("%d\n", ++nb);
		exit(0);
	}
	wait(NULL);
	printf("\e[0;33mPARENT PROCESS: %d\n\e[0;0m", pid);
	printf("%d\n", --nb);

	/* char *ttyname(int fildes);
	int ttyslot(void); */
	printf("\e[0;34mPATHNAME OF TERMINAL: %s\n\e[0;0m", ttyname(0));
	printf("\e[0;34mINDEX OF CURRENT TERMINAL: %d\n\e[0;0m", ttyslot());

	/* int unlink(const char *path); */
	if (system("touch think; echo 'think file created'; ls"))
		perror("touch command");
	if (unlink("think"))
		perror("unlink");

	puts("Directory structure:");
	traverse("/mnt/d/Developer/42cursus/", 0);

	/* History and readline */
	char *input;
    input = readline("Enter a line of text: ");
    printf("You entered: %s\n", input);
    rl_replace_line("This is the new line", 0);
    rl_redisplay();
    input = readline("Enter another line of text: ");
    printf("You entered: %s\n", input);

}

void msg_before_dying(int sig)
{
	signal(SIGINT, SIG_IGN);
	printf("Goodbye, good fellow <3\n");
	exit(0);
}