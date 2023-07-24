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
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

bool areStringsEqual(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return false;
		str1++;
		str2++;
	}
	// Check if both strings have reached their end ('\0')
	return (*str1 == '\0' && *str2 == '\0');
}

static void redirect_input_char(t_cmdop *cmd)
{
	char *buff;
	int fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (areStringsEqual(buff, cmd->args[0] + 1) == true)
			break;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

static void r_input(t_cmdop *cmd)
{
	int file;
	int i;
	char *error;

	i = 0;
	if ((cmd + 1)->args[0])
	{
		while (cmd[i].operator== LEFT_REDIRECTION)
			i++;
		i = 0;
		while (cmd[i].operator== LEFT_REDIRECTION)
			i++;
		if (access(cmd[i].args[0], F_OK) == 0)
		{
			file = open(cmd[i].args[0], O_RDONLY, 0666);
			dup2(file, STDIN_FILENO);
		}
		else
		{
			// if fail, give error message
			error = ft_strjoin("./minishell: ", (cmd + 1)->args[0]);
			perror(error);
			free(error);
			exit(EXIT_FAILURE);
		}
	}
}

static void r_output(t_cmdop *cmd)
{
	int i;

	i = 0;
	close(STDOUT_FILENO);
	while (cmd[i].operator== RIGHT_REDIRECTION || cmd[i].operator== DOUBLE_RIGHT_REDIRECTION)
		i++;
	{
		if (cmd[i].operator== RIGHT_REDIRECTION)
			open(cmd[i + 1].args[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (cmd[i].operator== DOUBLE_RIGHT_REDIRECTION)
			open(cmd[i + 1].args[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		i++;
		;
		close(1);
	}
	if (cmd[i].operator== RIGHT_REDIRECTION)
		open(cmd[i + 1].args[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (cmd[i].operator== DOUBLE_RIGHT_REDIRECTION)
		open(cmd[i + 1].args[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
}

int redirect_exec(t_cmdop *cmd, t_env *env, int len)
{
	//t_cmdop *tmp;

	//tmp = cmd;
	// function to give output to the next cmd
	if (cmd->operator== DOUBLE_LEFT_REDIRECTION)
		r_input(cmd);
	// to give the output of whatever you wtite until one specific char
	else if (cmd->operator== LEFT_REDIRECTION)
		redirect_input_char(cmd);
	// function to give output to the next cmd
	else
		r_output(cmd);
	while (cmd->operator!= NONE && cmd->operator!= PIPE)
		// just exec command;
		if (cmd->operator== NONE)
			exec_command(cmd, env);
		else
			pipeline_exec(cmd, env, len);
	return (0);
}