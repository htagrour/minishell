#include "get_next_line.h"

int	ft_get_char(int *c, int fd)
{
	int				i;
	char			*temp;
	struct termios	termios_new;
	struct termios	termios_backup;

	ft_bzero(&termios_new, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &termios_backup);
	termios_new = termios_backup;
	termios_new.c_lflag &= ~ (ICANON | ECHO);
	termios_new.c_cc[VMIN] = 1;
	termios_new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_new);
	temp = malloc(sizeof(char) * 5);
	i = read(fd, temp, 4);
	temp[i] = 0;
	*c = str_to_int(temp);
	free(temp);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_backup);
	return (i);
}

void	get_hist(t_list **current, int flag)
{
	if (flag && *current && (*current)->next)
		*current = (*current)->next;
	if (!flag && *current && (*current)->prev)
		*current = (*current)->prev;
}

void	change_current(t_list**current, int c)
{
	char	**str;
	char	*temp;

	if (*current)
	{
		str = (char **)(&(*current)->content);
		temp = *str;
		if (c != DELETE)
			*str = ft_add_char(*str, c);
		else
			if (*str)
				*str = ft_del_char(*str);
		free(temp);
	}
	else
	{
		if (c != DELETE)
		{
			temp = ft_strdup(" ");
			temp[0] = c;
			ft_lstadd_front(current, ft_lstnew((void*)temp));
		}
	}
}

void	adjust_hist(t_list **hist, char **line)
{
	if (g_var.current->content)
		*line = ft_strdup((char*)g_var.current->content);
	else
		*line = ft_strdup("");
	if (!g_var.current->prev)
	{
		ft_lstclear(hist, free);
		*hist = copy_list(g_var.current);
	}
	else
		ft_lstadd_front(hist, ft_lstnew(ft_strdup(*line)));
	ft_lstclear(&g_var.current, free);
}

int	get_line(char **line, int fd, t_list **hist)
{
	int	c;

	g_var.current = copy_list(*hist);
	ft_lstadd_front(&g_var.current, ft_lstnew(ft_strdup("")));
	print_shell();
	ft_putstr_fd(tgetstr("sc", NULL), STDOUT_FILENO);
	while (1)
	{
		ft_get_char(&c, fd);
		if (c >= 0 && c <= 255)
		{
			if (c == '\n')
				break ;
			if (c >= 32 && c <= 127)
				change_current(&g_var.current, c);
			if (c == CTR_D && (!g_var.current || !g_var.current->content
					|| !*(char*)g_var.current->content))
				clear_and_exit();
			if (c == ARROW_UP || c == ARROW_DOWN)
				get_hist(&g_var.current, c == ARROW_UP);
		}
		refresh(g_var.current);
	}
	adjust_hist(hist, line);
	return (1);
}
