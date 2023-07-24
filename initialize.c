/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:23:16 by Famahsha          #+#    #+#             */
/*   Updated: 2023/07/19 12:08:10 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_spaces(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

void	initialize_prompt(char **av, t_env *env)
{
	char	*line;
	// char	*modifiedline;
	char	*newline;
	t_cmdop *command;
	int command_len;

	(void)av;
	while (1)
	{
		line = readline("\033[31m./minishell $ \033[0m");
		if (line == NULL || !ft_strcmp(line, "exit"))
			exit(0);
		if (line[0] == '\0' || check_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (line)
		{
			printf("line is %s\n", line);
			newline = rostring(line);
			printf("after rostring is %s \n", newline);
			check_syntaxerror(newline);

			command_len = init_struct(newline, &command);
			if (command_len == -1) {
				free(line);
				continue;
			}

			exec_command_line(command, command_len, env);
			
			// TODO: free command

			free(line);

			// free(newline);

			// printf("line is %s\n", line);
			// modifiedline = rostring(line);
			// printf("after rostring is %s \n", modifiedline);
			// check_syntaxerror(modifiedline);
			// ft_splitline(modifiedline);
			// free(line);
			// free(modifiedline);
		}
	}
}
