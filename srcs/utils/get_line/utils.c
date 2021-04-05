#include "get_next_line.h"

int	str_to_int(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i += *str;
		str++;
	}
	return (i);
}

void	refresh(t_list *current)
{
	char	*temp;

	if (current)
	{
		temp = (char*)current->content;
		if (temp)
		{
			ft_putstr_fd(tgetstr("rc", NULL ), STDOUT_FILENO);
			write(1, "\r", 1);
			ft_putstr_fd(tgetstr("cd", NULL), STDOUT_FILENO);
			print_shell();
			ft_putstr_fd(temp, STDOUT_FILENO);
		}
	}
}

int	clear_and_exit(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO, 1);
	ft_lstclear(&g_var.current, free);
	exit(0);
}
