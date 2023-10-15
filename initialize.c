/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:23:16 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/15 11:20:28 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

bool	execute_all_heredoc(t_cmdop *command_line, int len, t_env *env)
{
	int	i;
	int	childpid;
	int	status;

	childpid = fork();
	if (childpid == 0)
	{
		signal(SIGINT, child_signal);
		i = 0;
		while (i < len)
		{
			if (command_line[i].operator == DOUBLE_LEFT_REDIRECTION)
				one_heredoc(command_line + i);
			i++;
		}
		free_command_struct(command_line, len);
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(childpid, &status, 0);
	return (WEXITSTATUS(status) == EXIT_SUCCESS);
}

char	*prepare_string(char *line, t_env *env)
{
	char	*expanded;
	char	*trimed;
	char	*processed_left_red;
	char	*processed_right_red;

	expanded = ft_expand(line, env);
	if (expanded == NULL)
		return (NULL);
	trimed = rostring(expanded);
	free(expanded);
	if (trimed == NULL)
		return (NULL);
	processed_left_red = process_special_chars(trimed, "<");
	free(trimed);
	if (processed_left_red == NULL)
		return (NULL);
	processed_right_red = process_special_chars(processed_left_red, ">");
	free(processed_left_red);
	return (processed_right_red);
}

void	line_execute(char *line, t_env *env)
{
	t_cmdop	*command;
	int		command_len;

	command_len = init_struct(line, &command);
	if (command_len == -1)
		return ;
	env->nb_struct = command_len;
	env->origin = command;
	free(line);
	if (!execute_all_heredoc(command, command_len, env))
	{
		free_command_struct(command, command_len);
		return ;
	}
	exec_command_line(command, command_len, env);
	free_command_struct(command, command_len);
}

char	*line_sanitize_and_check(char *line, t_env *env)
{
	char	*sanitized_line;

	sanitized_line = prepare_string(line, env);
	if (sanitized_line == NULL || check_syntaxerror(sanitized_line) == 1)
	{
		free(sanitized_line);
		return (NULL);
	}
	return (sanitized_line);
}

void	initialize_prompt(t_env *env)
{
	char	*line;
	char	*sanitized_line;

	while (1)
	{
		line = readline("\033[31m./minishell $ \033[0m");
		if (line == NULL)
			bye_minishell(env);
		if (line[0] != '\0' && !check_spaces(line))
		{
			add_history(line);
			sanitized_line = line_sanitize_and_check(line, env);
			if (sanitized_line != NULL)
				line_execute(sanitized_line, env);
		}
		free(line);
	}
}
