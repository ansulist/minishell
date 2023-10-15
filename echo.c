/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:48:36 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/10 23:28:30 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo_display_one(t_env *env, char *str)
{
	int	i;

	(void)env;
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	return (0);
}

int	display_n(void)
{
	ft_putstr_fd("\n", 1);
	return (0);
}

int	ft_echo(t_env *env, char **args)
{
	int	i;
	int	flag_n;

	(void)env;
	flag_n = 0;
	i = 0;
	if (*args == NULL)
		return (display_n());
	if (is_flag_n(args[0]) == 1)
	{
		flag_n = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		if (i != flag_n)
			ft_putchar_fd(' ', 1);
		if (ft_echo_display_one(env, args[i]) == -1)
			return (0);
		i++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
