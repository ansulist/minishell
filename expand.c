/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:57:49 by Famahsha          #+#    #+#             */
/*   Updated: 2023/10/13 16:09:24 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_dollar_question_mark(t_env *env, char *newline, int *counter)
{
	char	*key;

	key = ft_itoa(env->result);
	if (key == NULL)
		return (-1);
	ft_strncpy(newline + *counter, key, ft_strlen(key));
	*counter += ft_strlen(key);
	free(key);
	return (0);
}

int	fill_dollar_var_len(char *newline, char *line, t_env *env, int *i)
{
	int		end;
	char	*key;
	char	*env_var;
	int		var_len;

	end = *i + 1;
	while (is_valid_env_char(line[end]))
		end++;
	if (end - *i - 1 == 0)
	{
		newline[ft_strlen(newline)] = '$';
		return (1);
	}
	key = ft_strndup(line + *i + 1, end - *i - 1);
	if (key == NULL)
		return (-1);
	*i = end - 1;
	env_var = my_getenv(env, key);
	free(key);
	if (env_var == NULL)
		return (0);
	ft_strncpy(newline + ft_strlen(newline), env_var, ft_strlen(env_var));
	var_len = ft_strlen(env_var);
	free(env_var);
	return (var_len);
}

int	fill_one(char *newline, char *line, t_env *env, t_fill_vars *vars)
{
	bool	ignore_env;
	int		ret;

	ignore_env = ignore_env_var(line, vars->i);
	if (!ignore_env && line[vars->i] == '$' && line[vars->i + 1] == '?')
	{
		if (fill_dollar_question_mark(env, newline, &vars->counter) == -1)
			return (-1);
		vars->i++;
		return (0);
	}
	if (!ignore_env && line[vars->i] == '$')
	{
		ret = fill_dollar_var_len(newline, line, env, &vars->i);
		if (ret == -1)
			return (-1);
		vars->counter += ret;
		return (0);
	}
	newline[vars->counter++] = line[vars->i];
	return (0);
}

int	fill(char *newline, char *line, t_env *env)
{
	t_fill_vars	vars;

	vars.counter = 0;
	vars.i = 0;
	while (line[vars.i] != '\0')
	{
		if (fill_one(newline, line, env, &vars) == -1)
			return (-1);
		vars.i++;
	}
	return (0);
}

char	*ft_expand(char *line, t_env *env)
{
	char	*newline;
	int		len;

	len = counter(line, env);
	if (len == -1)
		return (NULL);
	newline = ft_calloc(len + 1, 1);
	if (newline == NULL)
		return (NULL);
	if (fill(newline, line, env) == -1)
	{
		newline[0] = '\0';
		return (newline);
	}
	return (newline);
}
