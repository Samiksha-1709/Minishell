#include"msh.h"

extern int status;
void execute_internal_commands(char *input_string)
{
   // printf("\nHi i am from the internal commands file.\n");
    //printf("\nThe input string is %s\n",input_string);
    //step1 -> comapare and check your inout_string is exit or not
    if(strcmp(input_string, "exit") == 0)
    {
        exit(1);//system call
    }

    //step2->compare and check your input_string is pwd or not
    if(strcmp(input_string, "pwd") == 0)
    {
        char str[100];
        getcwd(str,100);
        printf("%s\n",str);
    }

    if (strncmp(input_string, "cd", 2) == 0)
{
    // case: only "cd"
    if (input_string[2] == '\0')
    {
        chdir(getenv("HOME"));
    }
    else
    {
        // skip "cd " (space)
        if (chdir(&input_string[3]) == -1)
            perror("chdir");
    }
}

    //step4->compare and check your input_string echo or not
    if(strncmp(input_string, "echo",4) == 0)
    {
        //step4.1->compare and check your input string is echo $SHELL or not
        if(strncmp(&input_string[5], "$SHELL",6) == 0)
        {
            printf("%s \n",getenv("SHELL"));
        }
        //step4.2->check your input_string is echo $ or not
        else if(strncmp(&input_string[5], "$?",2) == 0)
        {
            printf("%d\n", WEXITSTATUS(status));
        }
        //step4.3->check your input string is echo $$ or not
        else if(strncmp(&input_string[5], "$$",2) == 0)
        {
            printf("%d \n",getpid());
        }
    }

}