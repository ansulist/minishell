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

bool arestringsequal(const char *str1, const char *str2)
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

void redirect_input_char(t_cmdop *cmd)
{
	char *buff;
	int fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (arestringsequal(buff, cmd->name) == true)
			break;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}