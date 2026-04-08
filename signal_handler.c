#include"msh.h"

extern char prompt[20];
extern int pid;
extern char fg_cmd[100];
void signal_handler(int signum)
{
    if(signum == SIGINT)
    { 
        printf("\nThe child pid is %d\n",pid);
        //child is present or not
        if(pid == 0)
        {
            //if child is not present
        printf("\n");
        printf("%s \n",prompt);
        fflush(stdout);
        }
    }
    else if(signum == SIGTSTP)
    {
        if(pid == 0)
        //if child is not present
        {
        printf("\n");
        printf("%s \n",prompt);
        fflush(stdout);
        }
        else
        {
            //store the stopped process info into the linked list
             //child running -> stop it
           //kill(pid, SIGTSTP);

            // store stopped process into linked list
            insert_at_last(pid, fg_cmd);

            printf("\n[%d] Stopped  %s\n", pid, fg_cmd);

            // reset pid (shell is free now)
            pid = 0;

           // printf("%s ", prompt);
            fflush(stdout);

        }
    }
    else if(signum == SIGCHLD)
    {
        int st;
        pid_t cpid;

        // clear all terminated background processes
        while ((cpid = waitpid(-1, &st, WNOHANG)) > 0)
        {
           // printf("\nDone.");
        }

    }
}