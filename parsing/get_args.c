#include "../minishell.h"

void			get_argument(char **str, char **ptr,
						t_var_bag *bag, t_hash_map *hm)
{
	char		*temp;
	int			len;

	len = 0;
	if (!conditions(**str, *bag, *(*str + 1)))
	{
		temp = *ptr;
		if (**str != '$' || bag->brack_flag && bag->spec_char == '\'' ||
			**str == '$' && belong("<>'\" ", *(*str + 1)))
			*ptr = ft_add_char(*ptr, **str);
		else
		{
			(*str)++;
			if (**str != '?')
				while (*(*str + len) && !belong("<>'\" ?", *(*str + len)))
					len++;
			else
				len++;
			get_env(*str, ptr, len, hm);
		}
		free(temp);
	}
	adjust_var_bag(bag, **str);
	*str += (len) ? len : 1;
}

int				extract_arg(t_command *command, char **str,
						t_var_bag *bag, t_hash_map *hm)
{
	int			len;
	char		*arg;
	char		*temp;

	arg = ft_strdup("");
	while (**str &&
			!((**str == ' ' || (is_red(**str) && !bag->slash_flag)) &&
			!bag->brack_flag))
		get_argument(str, &arg, bag, hm);
	if (arg[0])
		ft_lstadd_back(&(command->args), ft_lstnew((void*)arg));
	else
		free(arg);
	return (1);
}

t_redx			*get_file(char **str, t_var_bag *bag, t_hash_map *hm)
{
	t_redx		*red;

	(*str)++;
	while (**str && **str == ' ')
		(*str)++;
	if (is_red(**str))
		exit(1);
	red = (t_redx*)malloc(sizeof(t_redx));
	if (!red)
		return (NULL);
	red->file = ft_strdup("");
	while (**str && !((is_red(**str) || **str == ' ') && !bag->brack_flag))
		get_argument(str, &red->file, bag, hm);
	return (red);
}

int				extract_file(t_command *command, char **str,
							t_var_bag *bag, t_hash_map *hm)
{
	int			double_red;
	int			type;
	t_redx		*red;

	double_red = 0;
	type = (**str == '<');
	if (is_red(*(*str + 1)) && **str == *(*str + 1))
	{
		if (*(*str + 1) == '<')
			exit(1);
		double_red = 1;
		(*str)++;
	}
	red = get_file(str, bag, hm);
	red->type = double_red;
	if (type)
		ft_lstadd_back(&(command->in_redx), ft_lstnew((void*)red));
	else
		ft_lstadd_back(&(command->out_redx), ft_lstnew((void*)red));
	return (1);
}

int				get_cmd(t_command *command, char *str, t_hash_map *hm)
{
	t_var_bag	bag;
	int			i;

	ft_bzero(&bag, sizeof(bag));
	while (*str)
	{
		while (*str == ' ')
		{
			adjust_var_bag(&bag, *str);
			str++;
		}
		if (is_red(*str) && !bag.slash_flag)
			extract_file(command, &str, &bag, hm);
		else
			extract_arg(command, &str, &bag, hm);
	}
	return (1);
}
