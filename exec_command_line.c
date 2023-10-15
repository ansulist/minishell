/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:10:48 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/14 00:54:22 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmdop *cmd, t_env *env)
{
	if (cmd->operator == DOUBLE_LEFT_REDIRECTION)
		return (EXIT_SUCCESS);
	else if (cmd->operator == LEFT_REDIRECTION)
	{
		left_redirect_one(cmd, env, 1);
		return (EXIT_SUCCESS);
	}
	if (is_buildins(cmd) == true)
	{
		buildins(cmd, env);
		return (EXIT_SUCCESS);
	}
	env->result = 0;
	binary_command(env, cmd->name, cmd->args, cmd->nb_args);
	return (env->result);
}

int	exec_operator(t_cmdop *command_line, int len, t_env *env)
{
	int	status;

	status = 0;
	if (len == 1 && command_line->operator == DOUBLE_LEFT_REDIRECTION)
		return (status);
	if (len != 1 && command_line[1].operator == PIPE)
		status = pipeline_exec(command_line, env, len, false);
	else if (len == 1 && command_line[0].operator == LEFT_REDIRECTION)
		status = left_redirect_one(command_line, env, len);
	else if (len == 1)
		status = exec_command(command_line, env);
	else if (command_line[1].operator == PIPE)
		status = pipeline_exec(command_line, env, len, false);
	else if (command_line[0].operator == PIPE)
		status = pipeline_exec(command_line, env, len, true);
	else if (command_line[1].operator == LEFT_REDIRECTION)
		status = left_redirect_exec(command_line, env, len);
	else if (command_line[1].operator == RIGHT_REDIRECTION
		|| command_line[1].operator == DOUBLE_RIGHT_REDIRECTION)
		status = right_redirect_exec(command_line, env, len);
	else if (command_line[0].operator == DOUBLE_LEFT_REDIRECTION)
		status = exec_command_line(command_line + 1, len - 1, env);
	else
		status = exec_command(command_line, env);
	return (status);
}

int	exec_command_line(t_cmdop *command_line, int len, t_env *env)
{
	pid_t	childpid;
	int		status;

	status = 0;
	env->result = 0;
	if (len == 1 && is_buildins(command_line) == true)
		buildins(command_line, env);
	else
	{
		childpid = fork();
		if (childpid == -1)
			return (-1);
		if (childpid == 0)
		{
			signal(SIGINT, signal_controller);
			status = exec_operator(command_line, len, env);
			free_everything(env);
			exit(status);
		}
		waitpid(childpid, &status, 0);
	}
	env->result = WEXITSTATUS(status);
	return (env->result);
}
