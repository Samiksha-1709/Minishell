#include "msh.h"

char *get_command(char *input_string)
{
    static char cmd[20];
    int i = 0, j = 0;
    //fetch only the first word from input_string

    // skip starting spaces/tabs
    while (input_string[i] == ' ' || input_string[i] == '\t')
        i++;

    // copy first word
    while (input_string[i] != '\0' && input_string[i] != ' ' && input_string[i] != '\t')
    {
        cmd[j++] = input_string[i++];
    }

    cmd[j] = '\0';
    return cmd;
}
