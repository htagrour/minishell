/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:26 by fsarbout          #+#    #+#             */
/*   Updated: 2021/03/13 16:46:14 by fsarbout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "minishell.h"

char **updated_split(char const *str, char del, int *ele_number);
int process_line(char *line, t_hash_map *hm);
int free_array(void **array);
int free_command_array(t_command *commands, int total);
int execute(t_command *commande, int comm_number);
int get_cmd(t_command *command, char *str, t_hash_map *hm);
void adjust_var_bag(t_var_bag *bag, char c);
char **list_to_array(t_list *list);
int belong(char *str, char c);
int is_red(char c);
int conditions(char c, t_var_bag bag, char n);
char *get_env(char *str, char **ptr, int len, t_hash_map *hm);
int execute_commands(t_command *command, int last_fd, int total, t_hash_map *env);
void free_command(t_command *command);
void print_command(t_command commands, t_hash_map *env);
int built_in1(t_command command, t_hash_map *hm);
int built_in2(char **args, t_hash_map *env);
int print_error(char *str, int error, t_hash_map *env);
void sighandler(int signum);
t_command *get_commands(char **temp, int total, t_hash_map *env);
int array_lenght(char **str);
void echo_check_n(char **args, int *flag);
int ft_strchr_n(const char *s, int c);

#endif