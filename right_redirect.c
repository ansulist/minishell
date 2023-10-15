/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:58:25 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 01:03:18 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_redirect_exec_child(t_cmdop *cmd, t_env *env, int len)
{
	int		fd;
	int		ret;
	t_cmdop	*c;

	close(STDOUT_FILENO);
	c = cmd++;
	len--;
	fd = 0;
	while (len > 0 && (cmd->operator == RIGHT_REDIRECTION
			|| cmd->operator == DOUBLE_RIGHT_REDIRECTION))
	{
		if (fd != 0)
			close(fd);
		if (cmd->operator == RIGHT_REDIRECTION)
			fd = open(cmd->name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (cmd->operator == DOUBLE_RIGHT_REDIRECTION)
			fd = open(cmd->name, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1)
			return (-1);
		len--;
		cmd++;
	}
	ret = exec_command(c, env);
	close(fd);
	return (ret);
}

void	counting_loop(int *len, t_cmdop **cmd)
{
	*cmd += 1;
	(*len)--;
}

int	right_redirect_exec(t_cmdop *cmd, t_env *env, int len)
{
	pid_t	childpid;
	int		status;
	int		ret;

	childpid = fork();
	if (childpid == -1)
		return (-1);
	if (childpid == 0)
	{
		status = right_redirect_exec_child(cmd, env, len);
		free_everything(env);
		exit(status);
	}
	waitpid(childpid, &status, 0);
	ret = WEXITSTATUS(status);
	if (ret != EXIT_SUCCESS)
		return (ret);
	counting_loop(&len, &cmd);
	while (len > 0 && (cmd->operator == RIGHT_REDIRECTION
			|| cmd->operator == DOUBLE_RIGHT_REDIRECTION))
		counting_loop(&len, &cmd);
	if (len <= 0)
		return (0);
	return (exec_command_line(cmd, len, env));
}
