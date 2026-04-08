#include"msh.h"

void execute_external_commands(char * input_string)
{
    /*char *argv[30];
    //step1-> convert 1D array(your input_string) to 2D array(argv)
    int len = strlen(input_string);
    char *temp = input_string;
    char *token; int i = 0;
    token = (strtok(temp, " "));
    printf("\nThe %s\n",token);
    while(token != NULL)
    {
       argv[i++] = token;
       token = strtok(NULL, " ");
    }
    argv[i] = NULL;*/

   /* int j = 0;

    while(argv[j]  != NULL)
    {
        printf("%s \n",argv[j++]);
    }*/
   extern char *argv[30];
    int res = execvp(argv[0],argv);
    {
        if(res == -1)
        {
            perror("execvp");
            exit(1);
        }
    }

}