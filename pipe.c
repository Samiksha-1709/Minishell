#include "msh.h"

void implement_n_pipe(char *argv[])
{
    char *cmds[10][30];   // max 10 commands, each max 30 args
    int cmd_count = 0;
    int arg_index = 0;

    // Step1: split argv into cmds[][] using "|"
    for (int i = 0; argv[i] != NULL; i++)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            cmds[cmd_count][arg_index] = NULL;
            cmd_count++;
            arg_index = 0;
        }
        else
        {
            cmds[cmd_count][arg_index++] = argv[i];
        }
    }
    cmds[cmd_count][arg_index] = NULL;
    cmd_count++; // total commands

    int pipefd[2];
    int in_fd = 0; // initially stdin
    pid_t pid;
    int status;

    // Step2: create processes for each command
    for (int i = 0; i < cmd_count; i++)
    {
        pipe(pipefd); // create pipe

        pid = fork();

        if (pid == 0)
        {
            // child process

            // redirect input
            dup2(in_fd, STDIN_FILENO);

            // redirect output (except last command)
            if (i != cmd_count - 1)
                dup2(pipefd[1], STDOUT_FILENO);

            close(pipefd[0]);
            close(pipefd[1]);

            execvp(cmds[i][0], cmds[i]);
            perror("execvp");
            exit(1);
        }
        else
        {
            // parent process
            wait(NULL);

            close(pipefd[1]);

            in_fd = pipefd[0]; // next command reads from here
        }
    }

    // close final read end
    close(in_fd);
}
