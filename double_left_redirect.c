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

int handle_one_double_redirection(t_cmdop *cmd, int fd[2], bool w) 
{
	char *buff;

 	while (1)
	{
		buff = readline("> ");
		if (buff == NULL) {
			return (-1);
		}
		if (arestringsequal(buff, cmd->name) == true)
			return (0);
		
		if (w)
			ft_putendl_fd(buff, fd[1]);
		free(buff);
	} 
}

int count_consecutive_double_left_redirection(t_cmdop *cmd, int len)
{
	int nb;

	nb = 0;
	while (len > 0 && cmd->operator == DOUBLE_LEFT_REDIRECTION)
	{
		cmd++;
		len--;
		nb++;
	}

	return (nb);
}

int double_left_right(t_cmdop *cmd, int len, int fd[2]) 
{
	int nb;

	nb = count_consecutive_double_left_redirection(cmd, len);
	printf("[count_consecutive_double_left_redirection, nb: %d]\n", nb);
	close(fd[0]);
	while (len > 0 && cmd->operator == DOUBLE_LEFT_REDIRECTION)
	{
		handle_one_double_redirection(cmd, fd, nb == 1);
		cmd++;
		len--;
		nb--;
	}

	close(fd[1]);
	return (0);
}

int    double_left_redirect_exec(t_cmdop *cmd, t_env *env, int len)
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
		printf("[A]\n");
		double_left_right(cmd + 1, len - 1, fd);
		exit(0);
	}
	close(fd[1]);
	waitpid(childpid, &temp, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	printf("[B]\n");
	exec_command(cmd, env);
	close(fd[0]);
	return (0);
}