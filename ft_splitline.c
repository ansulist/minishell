/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:40:44 by Famahsha          #+#    #+#             */
/*   Updated: 2023/07/19 15:11:14 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int count_pipes(char *str)
// {
// 	int count;
// 	int quotecount;
// 	char *ptr;

// 	count = 0;
// 	quotecount = 0;
// 	ptr = str;
// 	while (*ptr != '\0')
// 	{
// 		if (*ptr == '\"')
// 			quotecount++;
// 		if (*ptr == '|' && (quotecount % 2 == 0))
// 		{
// 			count++;
// 			*ptr = 2;
// 		}
// 		ptr++;
// 	}
// 	return (count);
// }

// void	freecommand(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd == NULL)
// 		return ;
// 	while (i < cmd->count)
// 	{
// 		free(cmd->args[i]);
// 		i++;
// 	}
// 	free(cmd->args);
// 	cmd->args = NULL;
// 	cmd->count = 0;
// }
// t_cmdop create_struct(int count)
// {
// 	t_cmdop cmd;

// 	cmd.args = (char **)malloc(sizeof(char *) * count);
// 	cmd.nb_args = count;
// 	return (cmd);
// }

// t_cmdop *ft_splitline(char *str)
// {
// 	int i;
// 	char **args;
// 	int j;
// 	int count;
// 	t_cmdop *command;

// 	i = 0;
// 	j = 0;
// 	count = count_pipes(str);
// 	args = ft_split(str, ' ');
// 	if (args == NULL)
// 		return NULL;
// 	command = NULL;
// 	if (!args[i] || ft_isspace(*args[i]))
// 	{
// 		free(args);
// 		return (0);
// 	}
// 	while (args[i])
// 	{
// 		if (args[i - 1] == NULL || args[i - 1] == )
// 			command[i].name = ft_strdup(args[i]);
// 		command[i] = create_struct(count);
// 		printf("%s\n", command[i].args[i]);
// 		i++;
// 	}
// 	// freecommand(&command);
// 	free(args);
// 	return (command);
// }

t_operator is_operator(char *str)
{
	if (str == NULL)
	{
		return NONE;
	}

	if (str[0] == '|' && str[1] == '\0')
	{
		return PIPE;
	}

	if (str[0] == '<' && str[1] == '\0')
	{
		return LEFT_REDIRECTION;
	}

	if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
	{
		return DOUBLE_LEFT_REDIRECTION;
	}

	if (str[0] == '>' && str[1] == '\0')
	{
		return RIGHT_REDIRECTION;
	}

	if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
	{
		return DOUBLE_RIGHT_REDIRECTION;
	}

	return NONE;
}

// this function works only if av is correct
int count_struct(char **av)
{
	int i;
	t_operator op;
	int nb_struct;

	nb_struct = 0;
	i = 0;
	while (av[i] != NULL)
	{
		op = is_operator(av[i]);
		// it's a command
		if (op == NONE)
		{
			nb_struct++;
			i++;
			// pass all the arguments
			while (av[i] != NULL && is_operator(av[i]) == NONE)
			{
				i++;
			}
		}
		else if (op == PIPE)
		{
			nb_struct++;
			i++;
		}
		else
		{
			// we are in a redirection
			if (i == 0) {
				// heredoc case
				nb_struct++;
				i += 2;
			} else {
				nb_struct += 2;
				i += 2;
			}
		}
	}
	return (nb_struct);
}

// ls -l -e | wc -l
// i:  1
// k:       3
int fill_structs(char **av, t_cmdop *command)
{
	int i;
	int j;
	int k;
	t_operator op;

	i = 0;
	j = 0;
	while (av[i] != NULL)
	{
		op = is_operator(av[i]);
		if (op == NONE)
		{
			command[j].name = ft_strdup(av[i]);
			if (command[j].name == NULL)
			{
				// TODO: handle malloc failure
				return (-1);
			}
			i++;
			k = i;
			// pass all the arguments
			while (av[k] != NULL && is_operator(av[k]) == NONE)
			{
				k++;
			}
			command[j].nb_args = k - i;
			command[j].args = malloc(sizeof(char *) * (k - i + 1));
			if (command[j].args == NULL)
			{
				// TODO: handle malloc failure
				return (-1);
			}
			k = 0;
			while (av[i] != NULL && is_operator(av[i]) == NONE)
			{
				command[j].args[k] = ft_strdup(av[i]);
				if (command[j].args[k] == NULL)
				{
					// TODO: handle malloc failure
					return (-1);
				}
				k++;
				i++;
			}
			j++;
		}
		else if (op == PIPE)
		{
			command[j].operator= PIPE;
			j++;
			i++;
		}
		else
		{
			command[j].operator= op;
			command[j].name = ft_strdup(av[i + 1]);
			if (command[j].name == NULL)
			{
				// TODO: handle malloc failure
				return (-1);
			}
			j++;
			i += 2;
		}
	}
	return (0);
}

void print_struct(t_cmdop *cmd, int len)
{
	int i;
	int j;

	i = 0;
	while (len > i)
	{
		if (cmd[i].name != NULL) {
			printf("name: %s\n", cmd[i].name);
		}
		printf("op: %d\n", cmd[i].operator);
		j = 0;
		if (cmd[i].args != NULL)
		{
			while (cmd[i].args[j] != NULL)
			{
				printf("args: %s\n", cmd[i].args[j]);
				j++;
			}
		}
		printf("----------------\n\n");
		i++;
	}
}

// TODO path
int check_dollarsign(t_cmdop *cmd, int len, t_env *env)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (cmd[i].args[j])
		{
			if (ft_strncmp(cmd[i].args[j], "$", 1) == 0)
			{
				tmp = ft_strdup(cmd[i].args[j]);
				cmd[i].args[j] = my_getenv(env, cmd[i].args[j]);
				if (cmd[i].args[j] == NULL)
				{
					cmd[i].args[j] = tmp;
					free(tmp);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int init_struct(char *str, t_cmdop **command)
{
	int nb_struct;
	char **av;

	av = ft_split(str, ' ');
	if (av == NULL)
		return (-1);
	nb_struct = count_struct(av);
	if (nb_struct == 0)
	{
		free(av);
		return (0);
	}
	*command = malloc(sizeof(t_cmdop) * nb_struct);
	if (*command == NULL)
	{
		free(av);
		return (-1);
	}
	if (fill_structs(av, *command) == -1)
	{
		free(av);
		free(*command);
		return (-1);
	}
	print_struct(*command, nb_struct);
	free(av);
	return (nb_struct);
}