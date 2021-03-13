/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:16:06 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/13 16:25:26 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "minishell.h"

typedef struct s_var_bag
{
    int		brack_flag;
	char 	prev_char;
	char	spec_char;
    int     slash_flag;
} t_var_bag;

typedef struct  s_redirection
{
    int type;
    char *file;
} t_redx;

typedef struct s_command
{
    t_list *args;
    int next;
    t_list *in_redx; //type = 0;
    t_list *out_redx; // type = 1;
} t_command;
t_list *error;

#endif