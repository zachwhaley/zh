#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define COUNT(x) (sizeof(x)/sizeof(0[x]))

struct builtin {
    const char *cmd;
    void (*run)(char**);
};

void runcd(char **args)
{
    int len = 0;
    while (args[len])
        len++;
    if (len > 1)
        chdir(args[1]);
}

void runexit(char **args)
{
    exit(0);
}

void runset(char **args)
{
    int len = 0;
    while (args[len])
        len++;
    if (len > 1) {
        char *name = args[1];
        char *value = strchr(args[1], '=');
        *value = '\0';
        value++;
        setenv(name, value, 1);
    }
}

struct builtin builtins[] = {
    { "cd", runcd },
    { "exit", runexit },
    { "set", runset },
};
void runcmd(char **args)
{
    // Check builtin commands
    for (int i = 0; i < COUNT(builtins); i++) {
        if (strcmp(builtins[i].cmd, args[0]) == 0) {
            // Run builtin command
            builtins[i].run(args);
            return;
        }
    }

    // Fork and exec command
    pid_t pid = fork();
    if (pid == 0)
        execvp(args[0], args);
    else
        waitpid(pid, NULL, 0);
}

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

int main(int argc, const char *argv[])
{
    char cmd[BUFSIZ];
    char cwd[FILENAME_MAX];
    while (1) {
        // Print prompt
        printf("%s ζ ", getcwd(cwd, FILENAME_MAX));

        // Get command
        fgets(cmd, BUFSIZ, stdin);

        // Parse command
        char **args = split(cmd);
        if (args[0])
            // Run command
            runcmd(args);
        free(args);
    }
    return 0;
}
