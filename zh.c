#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char** split(char *cmd)
{
    int ndx = 0, len = 10;
    char **args = malloc(len * sizeof(char*));
    const char *tok = " \n";

    char *arg = strtok(cmd, tok);
    while (arg) {
        args[ndx] = arg;
        ndx++;
        if (ndx >= len) {
            len += len;
            args = realloc(args, len * sizeof(char*));
        }
        arg = strtok(NULL, tok);
    }
    args[ndx] = NULL;
    return args;
}

void runcmd(char *cmd)
{
    // Split command into an array of arguments
    char **args = split(cmd);
    if (!args[0])
        goto done;

    // Fork and exec command
    pid_t pid = fork();
    if (pid == 0)
        execvp(args[0], args);
    else
        waitpid(pid, NULL, 0);
done:
    free(args);
}

int main(int argc, const char *argv[])
{
    char cmd[BUFSIZ];
    while (1) {
        // Print prompt
        printf("ζ ");
        // Get command
        fgets(cmd, BUFSIZ, stdin);
        // Run command
        runcmd(cmd);
    }
    return 0;
}
