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
    ft_putstr_fd(BGRN, STDOUT_FILENO);
    ft_putstr_fd("my_shell>", STDOUT_FILENO);
    ft_putstr_fd(RESET, STDOUT_FILENO);
}

void sighandler(int signum) {
    ft_putchar_fd('\n', STDOUT_FILENO);
    print_shell();
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
    int fd = open("test.txt", O_RDONLY);
    signal(SIGINT, sighandler);
   errors = (t_list*)malloc(sizeof(t_list));
    while (i > 0)
    {
        print_shell();
        i = get_next_line(fd, &line);
        if (line[0])
            process_line(line, env, errors);
        free(line);
    }
    free_hash_map(env);
    ft_lstclear(&errors, &fun);
    free(errors);

    return 0;
}
