/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:27:20 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 16:10:30 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "srcs/utils/get_line/get_next_line.h"
# include "srcs/utils/libft/libft.h"
# include "srcs/utils/hash_table/hash_table.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>

# define RED "\e[0;31m"
# define RESET "\e[0m"
# define BLKHB "\e[0;100m"
# define BGRN "\e[1;32m"
# define CLEAR "\e[1;1H\e[2J"

typedef struct s_var_bag
{
	int		brack_flag;
	char	del;
	char	spec_char;
	int		slash_flag;
}				t_var_bag;

typedef struct s_redirection
{
	int		type;
	char	*file;
}				t_redx;

typedef struct s_command
{
	t_list	*args;
	int		next;
	t_list	*in_redx;
	t_list	*out_redx;
}				t_command;
typedef struct s_var
{
	t_list	*current;
	int		flag;
}				t_var;

t_var		g_var;
char		**updated_split(char const *str, char del, int *ele_number);
int			process_line(char *line, t_hash_map *hm);
int			free_array(void **array);
int			free_command_array(t_command *commands, int total);
int			execute(t_command *commande, int comm_number);
int			get_cmd(t_command *command, char *str, t_hash_map *hm);
void		adjust_var_bag(t_var_bag *bag, char c);
char		**list_to_array(t_list *list);
int			belong(char *str, char c);
int			is_red(char c);
int			conditions(char c, t_var_bag bag, char n);
char		*get_env(char *str, char **ptr, int len, t_hash_map *hm);
int			execute_commands(t_command *command,
				int last_fd, int total, t_hash_map *env);
void		free_command(t_command *command);
void		print_command(t_command commands, t_hash_map *env);
int			built_in1(t_command command, t_hash_map *hm, int flag);
int			built_in2(char **args, t_hash_map *env);
int			print_error(char *str, int error, t_hash_map *env);
void		sighandler(int signum);
t_command	*get_commands(char **temp, int total, t_hash_map *env);
int			array_lenght(char **str);
void		echo_check_n(char **args, int *flag);
int			ft_strchr_n(const char *s, int c);
int			ft_strchr_eql(const char *s, int c);
int			add_env(char *str, t_hash_map *env);
int			is_buitin1(char *str);
int			is_buitin2(char *str);
int			get_in_fd(t_command command, int *last_fd);
int			get_out_fd(t_command command, int *out_fd);
int			env(char **args, t_hash_map *env);
int			exit_(t_command cmd, t_hash_map *env);
int			echo(char **args);
int			export(t_command command, t_hash_map *env, int out_fd);
int			unset(t_command command, t_hash_map *env);
int			is_valide_key(char *str);
int			is_valide_exit(char *str);
int			print_env(t_hash_map *env, int out_fd);
int			is_buitin1(char *str);
int			get_full_path(t_command *command, t_hash_map *env);
void		add_return(t_hash_map *env, int ret);
int			is_built_in(char *str);
void		get_external_env(char **envs, t_hash_map *env);
void		ignore_signals(void);
void		print_shell(void);
int			free_error(char **str, t_hash_map *env);

#endif
