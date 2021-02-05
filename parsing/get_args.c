#include "../minishell.h"

int is_red(char c) // is a redirection char
{
	return (c == '<' || c == '>');
}


char **get_final_args(t_list *list)
{
	char **args;
	char *temp;
	char *temp1;
	int i;
	char c;
	t_var_bag bag;

	i = 0;
	args = (char**)malloc(sizeof(char**) * (ft_lstsize(list) + 1));
	while (list)
	{
		temp = (char*)list->content;
		bzero(&bag, sizeof(bag));
		args[i] = ft_strdup("");
		while ((c = *temp) != 0)
		{	
			adjust_var_bag(&bag, c, 0);
			//finish this
			if (!(c == '\'' && (bag.slash_flag || (bag.brack_flag && bag.spec_char != '\''))||
					(c == '\\' && bag.slash_flag)))
			{
				temp1 = args[i];
				//if c = $ and !slash && brack ect 
				//get env variable 
			    args[i] = ft_strjoin(args[i], &c);
				free(temp1);
			}
			temp++;
		}
		i++;
		list = list->next;
	}
	args[i] = NULL;
	return args;
}

int get_cmd_arg(t_command *command, char *str, int i)
{
	int len;
	char *ptr;

	t_var_bag bag;

	ft_bzero(&bag, sizeof(bag));
	len = 0;
	while (str[i + len] && !((str[i + len] == ' ' || is_red(str[len + i])) && !bag.brack_flag))
	{
			adjust_var_bag(&bag, str[len+i], i);
			len++;
	}
	
	ptr = ft_substr(str, i, len);
	ft_lstadd_back(&(command->args), ft_lstnew((void*)ptr));
	return i + len;
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
	return i + len;
}

int ft_get_args(t_command *command, char *str)
{
    int value = 1;
    int i = 0;

    while(str[i])
    {
	    while(str[i] == ' ')
		  i++;
		 
	    if (is_red(str[i]))
			i = get_file(command, str, ++i);
		else
			i = get_cmd_arg(command, str, i);
	    i++;
    }
    return value;
}
