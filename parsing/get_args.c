#include "../minishell.h"

int is_red(char c) // is a redirection char
{
	return (c == '<' || c == '>');
}

int get_file(t_command *command, char *str, int i)
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
	return i;
}

int ft_get_args(t_command *command, char *str)
{
    int value = 1;
    int i = 0;
	
	ft_bzero(command, sizeof(t_command));
    while(str[i])
    {
	    while(str[i] == ' ')
		  i++;
	    if (is_red(str[i]))
		{
			 i = get_file(command, str, ++i);
		}
	    i++;
    }
    return value;
}
