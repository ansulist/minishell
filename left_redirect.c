/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:58:25 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/18 13:58:27 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int right(t_cmdop *cmd, int len, int pipe_fd[2]) {
	int fd;
	char buf[42];
	int nb;

	close(pipe_fd[0]);
	// We need to send all files contents to parent through pipe
	while (len > 0 && cmd->operator == LEFT_REDIRECTION) {
		if (access(cmd->name, F_OK) == 0)
		{
			fd = open(cmd->name, O_RDONLY, 0666);
			while (1) {
				nb = read(fd, buf, 42);
				if (nb <= 0)
					break;
				if (write(pipe_fd[1], buf, nb) == -1) {
					close(pipe_fd[1]);
					return (-1);
				}
			}
			close(fd);
		}
		else
		{
			perror("./minishell: ");
			close(pipe_fd[1]);
			exit(0);
		}
		cmd++;
		len--;
	}
	close(pipe_fd[1]);
	return (0);
}

int    left_redirect_exec(t_cmdop *cmd, t_env *env, int len)
{
	pid_t childpid;
	int fd[2];
	int temp;

	// make the exit function to quit
	if (pipe(fd) == -1)
		return (-1);
	childpid = fork();
	// make the exit function to quit
	if (childpid == -1)
		return (-1);
	if (childpid == 0)
	{
		right(cmd + 1, len - 1, fd);
		exit(0);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_command(cmd, env);
	close(fd[0]);
	waitpid(childpid, &temp, 0);
	return (0);
}