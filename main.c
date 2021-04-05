#include "minishell.h"

char	*get_term(void)
{
	char		*term_name;

	term_name = getenv("TERM");
	if (!term_name)
	{
		ft_putendl_fd("TERM environment variable not set", STDOUT_FILENO, 1);
		exit(1);
	}
	return (term_name);
}

int	main(int argc, char *argv[], char **envs)
{
	char		*line;
	t_hash_map	*env;
	t_list		*hist;

	hist = NULL;
	argv = NULL;
	(void)argc;
	hist = NULL;
	tgetent(NULL, get_term());
	env = init_hash_map(30);
	get_external_env(envs, env);
	ignore_signals();
	while (get_line(&line, STDIN_FILENO, &hist))
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (line[0])
			process_line(line, env);
		free(line);
	}
	ft_lstclear(&hist, free);
	free_hash_map(env);
	return (0);
}

int	process_line(char *line, t_hash_map *env)
{
	t_command	*commands;
	char		**temp1;
	char		**temp2;
	int			i;
	int			total;

	temp1 = updated_split(line, ';', &i);
	if (!temp1)
		return (print_error("syntax error", 258, env));
	i = -1;
	while (temp1[++i])
	{
		temp2 = updated_split(temp1[i], '|', &total);
		if (!temp2)
			return (free_error(temp1, env));
		commands = get_commands(temp2, total, env);
		if (!commands)
			return (free_array((void**)temp1));
		execute_commands(commands, 0, total, env);
		g_var.flag = 0;
		free_command_array(commands, total);
	}
	free_array((void**)temp1);
	return (0);
}

void	print_shell(void)
{
	ft_putstr_fd(BGRN, STDOUT_FILENO);
	ft_putstr_fd("minishell😎$> ", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
}
