/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:33 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 11:50:35 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

int	pipe_left(t_cmdop *cmd, t_env *env, int fd[2], bool ghost)
{
	int ret;

	ret = 0;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ghost == true)
	{
		close(STDOUT_FILENO);
		return (0);
	}
	ret = exec_command(cmd, env);
	close(STDOUT_FILENO);
	return (ret);
}

int	pipe_right(t_cmdop *cmd, t_env *env, int fd[2], int len)
{
	int ret;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	env->fd_in = true;
	close(fd[0]);
	ret = exec_command_line(cmd, len, env);
	close(STDIN_FILENO);
	return (ret);
}

void	counting(int *len, t_cmdop **cmd, bool ghost)
{
	if (ghost)
	{
		*cmd += 1;
		(*len) -= 1;
	}
	else
	{
		*cmd += 2;
		(*len) -= 2;
	}
}

int	pipeline_exec(t_cmdop *cmd, t_env *env, int len, bool ghost)
{
	pid_t	childpid;
	int		fd[2];
	int		temp;

	if (pipe(fd) == -1)
		return (-1);
	childpid = fork();
	if (childpid == -1)
		return (-1);
	if (childpid == 0)
	{
		temp = pipe_left(cmd, env, fd, ghost);
		free_everything(env);
		exit(temp);
	}
	counting(&len, &cmd, ghost);
	pipe_right(cmd, env, fd, len);
	close(fd[0]);
	close(fd[1]);
	waitpid(childpid, &temp, 0);
	return (0);
}
