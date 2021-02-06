#include "../minishell.h"

int is_red(char c) // is a redirection char
{
	return (c == '<' || c == '>');
}

int get_cmd_arg(t_command *command, char *str,t_var_bag *bag, int i)
{
	int len;
	char *ptr;
	char c;


	len = 0;
	c = str[i];

	while (str[i + len] && !((str[i + len] == ' ' || is_red(str[len + i])) && !bag->brack_flag && !bag->slash_flag))
	{
			c = str[i + len];
			len++;
			adjust_var_bag(bag, str[len + i], i);
			bag->prev_char = str[len + i];
	}
	ptr = ft_substr(str, i, len);
	if (!command->command)
		command->command = ptr;
	else
		ft_lstadd_back(&(command->args), ft_lstnew((void*)ptr));
	return i + len;
}

int get_file(t_command *command, char *str, t_var_bag *bag,int i)
{
	int len;
	int double_red;



	double_red = 0;
	len = 0;
	int type = (str[i - 1] == '<');

	if (is_red(str[i]) && str[i] == str[i -1])
	{
		if (str[i] == '<')
			return 0;
		double_red = 1;
		i++;
	}
	while(str[i] && str[i] == ' ')
		i++;
	if (is_red(str[i]))
		//error
		return 0;
	while(str[i + len] && !is_red(str[i + len]) && str[i + len] != ' ')
		len++;
	t_redirection *red = (t_redirection*) malloc(sizeof(t_redirection));

	red->type = double_red;
	red->file = ft_substr(str, i, len);
	// if (!red[0])
	// 	error

	if (type)
		ft_lstadd_back(&(command->in_redx), ft_lstnew((void*)red)); // in red should not have list but it's ok
	else
		ft_lstadd_back(&(command->out_redx), ft_lstnew((void*)red));
	return i + len ;
}

int ft_get_args(t_command *command, char *str)
{
    int value = 1;
    int i = 0;
	t_var_bag bag;
	char c;

	ft_bzero(&bag, sizeof(bag));
	ft_bzero(command, sizeof(t_command));
    while(str[i])
    {
	    while(str[i] == ' ')
		  i++;
		  c = str[i];
		adjust_var_bag(&bag,str[i], i);
	    if (is_red(str[i]) && !bag.slash_flag)
			i = get_file(command, str,&bag, ++i);
		else
			i = get_cmd_arg(command, str,&bag, i);

		bag.prev_char = str[i];
    }
    return value;
}
