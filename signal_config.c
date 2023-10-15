/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:58:32 by ansulist          #+#    #+#             */
/*   Updated: 2023/10/15 11:20:37 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	child_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		exit(130);
	}
}

void	signal_controller(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (waitpid(-1, &g_exit_status, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDERR_FILENO, "  \n", 4);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 1;
		}
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		g_exit_status = 131;
	}
	else if (sig_num == SIGSEGV)
	{
		printf("_____SEGMENTATION_____FAULT_____");
		exit(EXIT_FAILURE);
	}
}

void	trap_signals(void)
{
	signal(SIGINT, signal_controller);
	signal(SIGQUIT, signal_controller);
	signal(SIGSEGV, signal_controller);
}
