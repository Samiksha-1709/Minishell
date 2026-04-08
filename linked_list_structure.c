#include "msh.h"


Job *head = NULL;
Job *tail = NULL;
/* Foreground details (used when ctrl+z comes) */
extern int pid;              // your global child pid
extern char fg_cmd[100];     // store last executed command string


void insert_at_last(int pid, char *cmd)
{
    Job *new = malloc(sizeof(Job));
    new->pid = pid;
    strcpy(new->cmd, cmd);
    new->next = NULL;

    if (head == NULL)
    {
        head = tail = new;
    }
    else
    {
        tail->next = new;
        tail = new;
    }
}

void delete_at_last()
{
    if (head == NULL)
        return;

    if (head == tail)
    {
        free(head);
        head = tail = NULL;
        return;
    }

    Job *temp = head;
    while (temp->next != tail)
        temp = temp->next;

    free(tail);
    tail = temp;
    tail->next = NULL;
}

void jobs_command()
{
    Job *temp = head;
    int count = 1;

    if (temp == NULL)
    {
        printf("No stopped jobs\n");
        return;
    }

    while (temp != NULL)
    {
        printf("[%d] Stopped  %d  %s\n", count, temp->pid, temp->cmd);
        temp = temp->next;
        count++;
    }
}

void fg_command()
{
    if (tail == NULL)
    {
        printf("fg: no jobs\n");
        return;
    }

    int child_pid = tail->pid;
    int st;

    kill(child_pid, SIGCONT);                 // continue
    waitpid(child_pid, &st, WUNTRACED);       // wait in fg

    // if terminated normally OR killed -> remove job
    if (WIFEXITED(st) || WIFSIGNALED(st))
    {
        delete_at_last();
    }
    // if stopped again -> keep it in list (no delete)
}

void bg_command()
{
    if (tail == NULL)
    {
        printf("bg: no jobs\n");
        return;
    }

    int child_pid = tail->pid;

    kill(child_pid, SIGCONT);   // continue in bg

    // remove from stopped list because now running in background
    delete_at_last();
}
