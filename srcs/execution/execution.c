/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:06:05 by fsarbout          #+#    #+#             */
/*   Updated: 2021/04/05 15:59:28 by htagrour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_default_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	exec_(t_command command, int last_fd, int fds[], t_hash_map *env)
{
	char	**envs;
	char	**args;

	dup2(last_fd, 0);
	if (last_fd != 0)
		close(last_fd);
	if (command.next || command.out_redx)
		dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	envs = hash_to_arr(env, 0);
	args = list_to_array(command.args);
	if (built_in1(command, env, 0) == -1 && built_in2(args, env) == -1)
		execve(*args, args, envs);
	else
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

int	start_process(t_command command, int last_fd, int fds[], t_hash_map *env)
{
	pid_t	pid;

	g_var.flag = 1;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		sig_default_mode();
		if (get_in_fd(command, &last_fd) || get_out_fd(command, &fds[1]))
			exit(print_error("FIle ERROR", 1, env));
		if (!command.args)
			exit(0);
		if (get_full_path(&command, env))
			exit(print_error("command not found", 127, env));
		exec_(command, last_fd, fds, env);
	}
	close(fds[1]);
	return (pid);
}

int	get_return_status(int ret, t_hash_map *env, t_command *command)
{
	if (!command->next)
	{
		if (WIFEXITED(ret))
			add_return(env, WEXITSTATUS(ret));
		if (WIFSIGNALED(ret))
			add_return(env, WTERMSIG(ret) + 128);
	}
	return (0);
}

int	execute_commands(t_command *commands, int last_fd, int total
		, t_hash_map *env)
{
	int	fds[2];
	int	ret;
	int	pid;

	if ((total == 1) && commands->args && built_in1(*commands, env, 1) != -1)
		return (0);
	pipe(fds);
	pid = start_process(*commands, last_fd, fds, env);
	if (commands->next)
		ret = execute_commands(commands + 1, fds[0], total, env);
	close(fds[0]);
	waitpid(pid, &ret, 0);
	return (get_return_status(ret, env, commands));
}
