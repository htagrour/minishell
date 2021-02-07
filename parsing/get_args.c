#include "../minishell.h"

int is_red(char c) // is a redirection char
{
	return (c == '<' || c == '>');
}

int conditions(char c, t_var_bag bag, char n)
{
	

	if (bag.brack_flag && bag.spec_char == '\'' && c != '\'')
		return 0;
	if (c == '"' && !bag.slash_flag)
		return 1;
	if (c == '\'' && (!bag.slash_flag && !(bag.brack_flag && bag.spec_char == '"')))
		return 1;
	if (c == '\\' && 
		(!bag.slash_flag && !(bag.brack_flag && bag.spec_char == '"' && !bag.slash_flag && n != '"')))
		return 1;
    return 0;
}

char *adjust_arg(char *temp, t_hash_map *hm)
{
	char c;
	int i;
	int len;
	char *str;
	t_var_bag bag;
	char *temp1;

	i = 0;
	str = ft_strdup("");
	ft_bzero(&bag, sizeof(bag));
	while ((c = temp[i]) != 0)
	{
		len = 0;
		if (!conditions(c, bag, temp[i + 1]))
		{
			temp1 = str;
			if (c == '$' && !bag.slash_flag && !(bag.brack_flag && bag.spec_char == 92))
			{
				i++;
				while (temp[i + len] && !belong("<>'\" ", temp[i + len]))
					len++;
				str = ft_strjoin(str, get_value(ft_substr(temp, i, len),hm));
				i += len;
			}
			else
				str = ft_add_char(str, c);
			free(temp1);
		}
		adjust_var_bag(&bag,c,i);
		i += (len) ? 0:1;
	}
	return str;
}

int get_cmd_arg(t_command *command, char *str, int i, t_var_bag *bag, t_hash_map *hm)
{
	int len;
	char *ptr;
	char *temp;

	len = 0;
	while (str[i + len] && 
			!((str[i + len] == ' ' || (is_red(str[len + i]) && !bag->slash_flag)) && 
			!bag->brack_flag))
	{
			char c = str[i + len];
			adjust_var_bag(bag, str[len+i], i);
			len++;
	}
	temp = ft_substr(str, i, len);
	ptr = adjust_arg(temp, hm);
	free(temp);
	if (ptr[0])
		ft_lstadd_back(&(command->args), ft_lstnew((void*)ptr));
	else
		free(ptr);
	return i + len;
}

int get_file(t_command *command, char *str, int i,t_var_bag *bag)
{
	int len;
	int double_red;



	double_red = 0;
	len = 0;
	int type = (str[i - 1] == '<');

	if (is_red(str[i]) && str[i] == str[i -1])
	{
		if (str[i] == '<')
			return i;
		double_red = 1;
		i++;
	}
	while(str[i] && str[i] == ' ' )
		i++;
	if (is_red(str[i]))
	{
		printf("error");
		//error
		exit(1);
	}
	while(str[i + len] && !((is_red(str[i + len])  || str[i + len] == ' ') && !bag->brack_flag))
	{
		adjust_var_bag(bag, str[len + i], i);
		len++;
	}
	t_redirection *red = (t_redirection*) malloc(sizeof(t_redirection));

	red->type = double_red;
	red->file = ft_substr(str, i, len);
	// if (!red[0])
	// 	error

	if (type)
		ft_lstadd_back(&(command->in_redx), ft_lstnew((void*)red));
	else
		ft_lstadd_back(&(command->out_redx), ft_lstnew((void*)red));
	return i + len;
}

int ft_get_args(t_command *command, char *str, t_hash_map *hm)
{
    int value = 1;
	t_var_bag bag;
	int i = 0;

	bzero(&bag, sizeof(bag));
    while(str[i])
    {
	    while(str[i] == ' ')
		{
			adjust_var_bag(&bag, str[i], i);
			i++;
		}
		char c = str[i];
		if (is_red(str[i]) && !bag.slash_flag)
			i = get_file(command, str, ++i, &bag);
		else
			i = get_cmd_arg(command, str,i, &bag, hm);
    }
    return value;
}
