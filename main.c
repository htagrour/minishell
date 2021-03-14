#include "includes/minishell.h"


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

void print_shell(int flag)
{
    if (flag)
        ft_putstr_fd("\33[2K\r", STDOUT_FILENO);
    ft_putstr_fd(BGRN, STDOUT_FILENO);
    ft_putstr_fd("my_shell😎>", STDOUT_FILENO);
    ft_putstr_fd(RESET, STDOUT_FILENO);
}
//need to be done
void  sig_handler(int sig)
{
    ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
    // print_shell();
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n",STDOUT_FILENO);
        print_shell(1);
    }
    // signal(sig, SIG_IGN);
}

void ignore_signals()
{
        signal(SIGINT, sig_handler);
        signal(SIGQUIT, sig_handler);
}

// void fun(void *str)
// {
//     char *temp;

//     temp = (char*)str;
//     if (temp)
//         free(temp);
// }

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

int process_line(char *line, t_hash_map *env)
{
    t_command *commands;
    char **temp1;
    char **temp2;
    int i;
    int total;
    //you should free char array
    temp1 = updated_split(line, ';', &i);
    if (!temp1)
        return (print_error("syntax error", 258, env));
    i = -1;
    while (temp1[++i])
    {
        temp2 = updated_split(temp1[i], '|', &total);
        if (!temp2)
            return (print_error("syntax error", 258, env));
        if (!(commands = get_commands(temp2, total, env)))
            return (free_array((void**)temp1));
        execute_commands(commands, 0, total, env);
        free_command_array(commands, total);
    }
    free_array((void**)temp1);
    return 0;
}

int main (int argc, char *argv[], char **envs)
{
    char *line;
    t_hash_map *env;
    int i = 1;

    

    env = init_hash_map(100);
    get_external_env(envs, env);
    // int fd = open("test.txt", O_RDONLY);
    ignore_signals();
    while (i > 0)
    {
        print_shell(0);
	//system("/bin/stty raw");
        i = get_next_line(STDIN_FILENO, &line);
	//system("/bin/stty cooked");
        if (line[0])
            process_line(line, env);
        free(line);
    }
    free_hash_map(env);

    return 0;
}
