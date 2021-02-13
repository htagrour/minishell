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

int main (void)
{
    char *line;
    t_hash_map *env;
    int j;
    int i = 1;
    char **temp;
    



    int fd = open("test.txt", O_RDONLY);
    env = init_hash_map(100);
    set_value("PATH", PATH,env);
    set_value("TERM", "xterm-256color", env);
    set_value("?", "0",env);
    signal(SIGINT, sighandler);
   // error = (t_list*)malloc(sizeof(t_list));
    while (i > 0)
    {
        print_shell();
        i = get_next_line(STDIN_FILENO, &line);
        if (line[0])
            process_line(line, env);
        
        free(line);
    }
    free_hash_map(env);
    ft_lstclear(&error, &fun);
    free(error);

    return 0;
}
