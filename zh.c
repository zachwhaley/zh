#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char** split(char *cmd)
{
    int ndx = 0, size = 10;
    char **args = malloc(size * sizeof(char*));

    const char *tok = " \n";
    char *arg = strtok(cmd, tok);
    while (arg) {
        args[ndx] = arg;
        ndx++;
        if (ndx >= size) {
            size += size;
            args = realloc(args, size * sizeof(char*));
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

    // Fork and exec command
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
    }
    else {
        int wstatus;
        do {
            waitpid(pid, &wstatus, WUNTRACED);
        } while (!WIFEXITED(wstatus));
    }

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