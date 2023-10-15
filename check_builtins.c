/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:49 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/12 23:50:33 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_value(t_env *env, char *key)
{
	char	*str;

	str = my_getenv(env, key);
	printf("%s\n", str);
	return (0);
}

int	buildins(t_cmdop *cmd, t_env *env)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd, env);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (ft_cd(env, cmd->args[0]));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (ft_echo(env, cmd->args));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (ft_env(env, cmd));
	if (ft_strcmp(cmd->name, "export") == 0)
		return (ft_export(env, cmd->name, cmd->args));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (ft_unset(env, cmd->name, cmd->args));
	return (0);
}

bool	is_buildins(t_cmdop *cmd)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (true);
	return (false);
}
