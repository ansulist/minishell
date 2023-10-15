/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:58:25 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/14 11:52:03 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_and_write(t_cmdop *cmd, int pipe_fd[2])
{
	int		fd;
	char	buf[42];
	int		nb;

	fd = open(cmd->name, O_RDONLY, 0666);
	while (1)
	{
		nb = read(fd, buf, 42);
		if (nb <= 0)
			break ;
		if (write(pipe_fd[1], buf, nb) == -1)
		{
			close(pipe_fd[1]);
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int	right(t_cmdop *cmd, int len, int pipe_fd[2], t_env *env)
{
	(void)env;
	close(pipe_fd[0]);
	while (len > 0 && cmd->operator == LEFT_REDIRECTION)
	{
		if (access(cmd->name, F_OK) == 0)
		{
			if (read_and_write(cmd, pipe_fd) == -1)
				return (-1);
		}
		else
		{
			close(pipe_fd[1]);
			ft_putstr_fd("./minishell : No such file or directory\n", 2);
			free_everything(env);
			exit(127);
		}
		cmd++;
		len--;
	}
	close(pipe_fd[1]);
	return (0);
}

int	check_access_path(char *name, int fd)
{
	if (access(name, R_OK) != 0)
	{
		ft_putstr_fd("./minishell : file does not exist\n", 2);
		return (-1);
	}
	if (fd == -1)
	{
		ft_putstr_fd("./minishell : Permission Denied\n", 2);
		return (-1);
	}
	return (0);
}

int	left_redirect_one(t_cmdop *cmd, t_env *env, int len)
{
	int		fd;
	char	buf[42];
	int		nb;

	(void)len;
	(void)env;
	fd = open(cmd->name, O_RDONLY, 0666);
	if (check_access_path(cmd->name, fd) == -1)
	{
		exit(0);
	}
	while (1)
	{
		nb = read(fd, buf, 42);
		if (nb <= 0)
			break ;
		if (write(STDOUT_FILENO, buf, nb) == -1)
			return (-1);
	}
	close(fd);
	return (0);
}

int	left_redirect_exec(t_cmdop *cmd, t_env *env, int len)
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
		temp = right(cmd + 1, len - 1, fd, env);
		free_everything(env);
		exit(temp);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_command(cmd, env);
	close(fd[0]);
	waitpid(childpid, &temp, 0);
	return (0);
}
