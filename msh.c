/******************************************************************************
 * Author         : Samiksha  Mane
 * Date           : 22-01-2026
 * File           : msh.c
 * Description    : Minishell program capable of executing built-in and external
 *                  commands with basic job control.
 * Objective      :
 *   - To design and implement a simple Linux shell.
 *   - To understand process creation using fork().
 *   - To execute external commands using execvp().
 *   - To implement built-in commands like cd, pwd, exit, echo.
 *   - To support job control using Ctrl+C, Ctrl+Z, jobs, fg, bg.
 *   - To understand signal handling and process states.
 *
 * Usage          :
 *   Compile:
 *      gcc *.c -o minishell
 *
 *   Execute:
 *      ./minishell
 *
 * Output         :
 *   - Displays a custom shell prompt (minishell$).
 *   - Executes Linux commands entered by the user.
 *   - Supports foreground and background execution.
 *   - Displays stopped and running jobs using job control commands.
 *
 ******************************************************************************/



#include "msh.h"

char prompt[20] = "minishell$";
int main()
{
    system("clear");
    
    char input_string[40];

    scan_input(prompt,input_string);
    
}
