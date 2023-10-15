/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:15 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/13 15:05:28 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	ft_cerror(void)
{
	printf("zsh : command not found \n");
	return (0);
}

int	ft_error(void)
{
	printf("./minishell : zsh : parse error \n");
	return (2);
}

void	free_env(t_env *env)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (env->vars != NULL)
	{
		tmp = env->vars;
		while (tmp != NULL)
		{
			tmp2 = tmp;
			if (tmp->content != NULL)
				free((char *)tmp->content);
			tmp = tmp->next;
			free(tmp2);
		}
	}
	free(env);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	if (ac != 1)
	{
		printf("%s : invalid no of arguments\n", av[1]);
		return (0);
	}
	g_exit = 0;
	trap_signals();
	env = init_env(envp);
	if (env == NULL)
		return (-1);
	initialize_prompt(env);
	free_env(env);
	return (0);
}
