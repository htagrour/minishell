#include "minishell.h"
#include <time.h>
#include <signal.h>

void prints(void *str)
{
    printf("%s|\n", ((t_redx*)str)->file);
}

void printss(void *str)
{
    printf("%s\n", (char*)str);
}
void print_array(char **tab)
{
    while (*tab)
    {
        printf("%s\n", *tab);
        tab++;
    }
    
}
void print_command(t_command commands ,t_hash_map *env)
{

          ft_lstiter(commands.args, &printss);
          printf("in file: ");
          ft_lstiter(commands.in_redx, &prints);
          printf("\nout file: ");
          ft_lstiter(commands.out_redx, &prints);
        printf("---------------------------------------\n");
}

void print_shell(void)
{
    ft_putstr_fd("\33[2K", STDOUT_FILENO);
    ft_putstr_fd(BGRN, STDOUT_FILENO);
    ft_putstr_fd("\rmy_shell>", STDOUT_FILENO);
    ft_putstr_fd(RESET, STDOUT_FILENO);
}

void  INThandler(int sig)
{
  if (!getpid())
  {
      exit(130);
}
    // print_shell();
    if (sig == SIGINT)
        ft_putstr_fd("\n",STDOUT_FILENO);
    print_shell();
}

void ignore_signals()
{
    
        signal(SIGINT, INThandler);
        signal(SIGQUIT, INThandler);
}

void fun(void *str)
{
    char *temp;

    temp = (char*)str;
    if (temp)
        free(temp);
}
void get_external_env(char **envs, t_hash_map *env)
{
    char **temp;

    while (*envs)
    {
        temp = ft_split(*envs, '=');
        set_value(temp[0], temp[1], env);
        free_array((void**)temp);
        envs++;
    }
}
int main (int argc, char *argv[], char **envs)
{
    char *line;
    t_hash_map *env;
    int j;
    t_list *errors;
    int i = 1;
    char **temp;
    

    env = init_hash_map(100);
    get_external_env(envs, env);
    int fd = open("test.txt", O_RDONLY);
    ignore_signals();
    while (i > 0)
    {
        print_shell();
        i = get_next_line(STDIN_FILENO, &line);
        if (line[0])
            process_line(line, env);
        free(line);
    }
    free_hash_map(env);

    return 0;
}
