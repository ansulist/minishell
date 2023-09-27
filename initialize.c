/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:23:16 by Famahsha          #+#    #+#             */
/*   Updated: 2023/09/04 14:47:27 by ansulist         ###   ########.fr       */
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

int one_heredoc(t_cmdop *command_line)
{
	char *buff;

	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
		{
			return (-1);
		}
		if (arestringsequal(buff, command_line->name) == true)
			return (0);
	}
	free(buff);
}

// TODO
bool execute_all_heredoc(t_cmdop *command_line, int len)
{
	int i;
	int childpid;
	int status;

	childpid = fork();
	if (childpid == 0) {
		signal(SIGINT, child_signal);
		i = 0;
		while (i < len)
		{
			if (command_line[i].operator== DOUBLE_LEFT_REDIRECTION)
			{
				one_heredoc(command_line + i);
			}
			i++;
		}
		exit(EXIT_SUCCESS);
	} 
	else
		waitpid(childpid, &status, 0);
	return (WEXITSTATUS(status) == EXIT_SUCCESS);
}

void	initialize_prompt(char **av, t_env *env)
{
	char	*line;
	char	*newline;
	char	*newnewline;
	t_cmdop *command;
	int command_len;

	(void)av;
	while (1)
	{
		line = readline("\033[31m./minishell $ \033[0m");
		if (line == NULL)
			exit(0);
		if (line[0] == '\0' || check_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (line)
		{
			newline = ft_expand(line, env);
			if (newline == NULL)
			{
				free(line);
				continue;
			}
			newnewline = rostring(newline);
			//newline = process_special_chars(newline, "<>");
			//newline = process_special_chars(newline, ">");
			if (check_syntaxerror(newnewline) == 1)
				continue ;
			command_len = init_struct(newnewline, &command);
			if (command_len == -1) {
				free(line);
				free(newnewline);
				continue;
			}
			if (execute_all_heredoc(command, command_len)) {
				exec_command_line(command, command_len, env);
			}
			// TODO: free command
			free(line);
			free(newline);
		}
	}
}
