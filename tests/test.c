#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <signal.h>

/*
 * loop over commands by sharing
 * pipes.
 */

static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
			}
			close(fd[0]);
            // is builtin function
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		wait(NULL); 		/* Collect childs */
		close(fd[1]);
		fdd = fd[0];
		cmd++;
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc > 1) {
        struct stat sb;
        printf("%s is%s executable.\n", argv[1], stat(argv[1], &sb) == 0 &&
                                                 sb.st_mode & S_IXUSR ? 
                                                 "" : " not");
    }
    return 0;
}   