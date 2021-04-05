/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:28:32 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:46 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_argument(char **str, char **ptr, t_var_bag *bag, t_hash_map *env)
{
	char	*temp;
	int		len;

	len = 0;
	if (!conditions(**str, *bag, *(*str + 1)))
	{
		temp = *ptr;
		if (**str != '$' || (bag->brack_flag && bag->spec_char == '\'')
			|| (**str == '$' && (belong("<>'\" |", *(*str + 1))
						|| !*(*str + 1))))
			*ptr = ft_add_char(*ptr, **str);
		else
		{
			(*str)++;
			if (**str != '?' || !belong("<>'\"| \\?", **str))
				while (*(*str + len) && !belong("<>'\"| \\?", *(*str + len)))
					len++;
			else
				len++;
			get_env(*str, ptr, len, env);
		}
		free(temp);
	}
	adjust_var_bag(bag, **str);
	return (len);
}

int	extract_arg(t_command *command, char **str, t_var_bag *bag, t_hash_map *env)
{
	char	*arg;
	int		len;

	arg = ft_strdup("");
	while (**str && !((**str == ' ' || (is_red(**str)
					   	 && !bag->slash_flag)) && !bag->brack_flag))
	{
		len = get_argument(str, &arg, bag, env);
		if (len)
			*str += len;
		else
			*str += 1;
	}
	ft_lstadd_back(&(command->args), ft_lstnew((void*)arg));
	return (1);
}

t_redx	*get_file(char **str, t_var_bag *bag, int len, t_hash_map *env)
{
	t_redx	*red;

	while (**str && **str == ' ')
		(*str)++;
	if (is_red(**str))
		return (NULL);
	red = (t_redx*)malloc(sizeof(t_redx));
	if (!red)
		return (NULL);
	red->file = ft_strdup("");
	while (**str && !((is_red(**str) || **str == ' ') && !bag->brack_flag))
	{
		len = get_argument(str, &red->file, bag, env);
		if (len)
			*str += len;
		else
			*str += 1;
	}
	if (!red->file[0])
	{
		free(red->file);
		free(red);
		return (NULL);
	}
	return (red);
}

int	extract_file(t_command *command, char **str
		, t_var_bag *bag, t_hash_map *env)
{
	int		double_red;
	int		type;
	t_redx	*red;

	double_red = 0;
	type = (**str == '<');
	if (is_red(*(*str + 1)) && **str == *(*str + 1))
	{
		if (*(*str + 1) == '<')
			return (-1);
		double_red = 1;
		(*str)++;
	}
	*str += 1;
	red = get_file(str, bag, 0, env);
	if (!red)
		return (-1);
	red->type = double_red;
	if (type)
		ft_lstadd_back(&(command->in_redx), ft_lstnew((void*)red));
	else
		ft_lstadd_back(&(command->out_redx), ft_lstnew((void*)red));
	return (1);
}

int	get_cmd(t_command *command, char *str, t_hash_map *env)
{
	t_var_bag	bag;

	ft_bzero(&bag, sizeof(bag));
	ft_bzero(command, sizeof(t_command));
	while (*str)
	{
		while (*str == ' ')
		{
			adjust_var_bag(&bag, *str);
			str++;
		}
		if (*str)
		{
			if (is_red(*str) && !bag.slash_flag)
			{
				if (extract_file(command, &str, &bag, env) < 0)
					return (print_error("syntax error", 258, env));
			}
			else
				extract_arg(command, &str, &bag, env);
		}
	}
	return (0);
}
