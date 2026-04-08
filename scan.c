#include "msh.h"

char *external_commands[200];
char *argv[30];
int pid = 0;
int status;
char fg_cmd[100]; //store last executed command string

void scan_input(char *prompt, char *input_string)
{
    //requirements
    //1.prompt
    signal(SIGINT, signal_handler); //register the signal
    signal(SIGTSTP, signal_handler);

    extract_external_commands(external_commands);

    while (1)
    {
        printf("%s ", prompt);
        scanf(" %[^\n]", input_string);
        //getchar();

        //validate the input string is PS1 or not
        if ((strncmp(input_string, "PS1=", 4)) == 0)
        {
            //my input string is PS1
            //step1 -> validate space is present or not
            if (input_string[4] == ' ' || input_string[4] == '\t')
            {
                //if space is present dont change the prompt
                continue;
            }
            else
            {
                //if space is not present then change the prompt
                strcpy(prompt, input_string + 4);
            }
        }
        else
        {
            //step2 -> to get only the first word of our input_string
            //to comapre and check what type of command it is
            char *cmd = get_command(input_string);
            // printf("The First Word is %s\n",cmd);

            //step 3-> with the cmd we can check what type of commnad it is
            int type = check_command_type(cmd);

            if (type == BUILTIN)
            {
                // printf("\nBuilt In commands.\n");
                execute_internal_commands(input_string);
            }

            //check the command type is external or not
            else if (type == EXTERNAL)
            {
                int pipe_flag = 0;

                //step1-> convert 1D array(your input_string) to 2D array(argv)
                char *temp = input_string;
                char *token;
                int i = 0;

               // printf("\nThe %s\n", token);

                token = strtok(temp, " \t");
                while(token != NULL)
                {
                    argv[i++] = token;
                    token = strtok(NULL, " \t");
                }
                argv[i] = NULL;


                //step2->validate pipe is present or not
                for (int i = 0; argv[i] != NULL; i++)
                {
                    if (strcmp(argv[i], "|") == 0)
                    {
                        pipe_flag = 1;
                        break;
                    }
                }

                //printf("\nExternal commands.\n");

                strcpy(fg_cmd, input_string);

                //create a child process
                pid = fork();
                if (pid == 0)
                {
                    //child
                    signal(SIGINT, SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);

                    if (pipe_flag == 1)
                    {
                        implement_n_pipe(argv);
                    }
                    else
                    {
                        //to execute the external commands.
                        execute_external_commands(input_string);
                    }
                }
                else if (pid > 0)
                {
                    //parent
                   waitpid(pid, &status, WUNTRACED);
                    //wait(NULL);
                    pid = 0;
                }
            }

            else if (strcmp(input_string, "jobs") == 0)
            {
                //implement
                jobs_command();
            }
            else if (strcmp(input_string, "fg") == 0)
            {
                //implement fg
                fg_command();
            }
            else if (strcmp(input_string, "bg") == 0)
            {
                //implement bg
                bg_command();
            }
        }
    }
}

void extract_external_commands(char **external_commands)
{
    int fd;
    char ch;
    char buf[50] = {'\0'};
    int i = 0, j = 0;

    // step1 = open the external_commands.txt in read mode using system call
    fd = open("external_command.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    //step2 = read commands one by one
    while (read(fd, &ch, 1) > 0)
    {
        if (ch == '\r')
        {
            continue;
        }

        if (ch != '\n')
        {
            buf[i++] = ch;
        }
        //step3 = allocate the memory dynamically
        else
        {
            buf[i] = '\0'; // must terminate string

            external_commands[j] = calloc(strlen(buf) + 1, sizeof(char));
            //step4 = store the command into the 2D array
            strcpy(external_commands[j++], buf);

            memset(buf, '\0', 50);
            i = 0;
        }
    }

    // store last command if file doesn't end with '\n'
    if (i > 0)
    {
        buf[i] = '\0';
        external_commands[j] = calloc(strlen(buf) + 1, sizeof(char));
        strcpy(external_commands[j], buf);
        j++;
    }

    // end marker for external commands array
    external_commands[j] = NULL;

    close(fd);
}

int check_command_type(char *command)
{
    //printf("\nThe command is %s\n",command);

    /*List of builtin commands*/
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
                        "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
                        "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

    //step1->check the commmand is BUILTIN or not
    for (int i = 0; builtins[i] != NULL; i++)
    {
        if (strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }

    //step2->check the command is external or not
    for (int i = 0; external_commands[i] != NULL; i++)
    {
        if (strcmp(command, external_commands[i]) == 0)
        {
            return EXTERNAL;
        }
    }

    //step3->if it not builtin not external then it invalid
    return NO_COMMAND;
}
