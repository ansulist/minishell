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

int    right_redirect_exec(t_cmdop *cmd, t_env *env, int len)
{
	int fd;
	int ret;
	t_cmdop *c;
	
	// close stdout to redirect output in the file
	close(STDOUT_FILENO);
	c = cmd;
	cmd++;
	len--;
	fd = 0;
	while (len > 0 && (cmd->operator == RIGHT_REDIRECTION ||
	  cmd->operator == DOUBLE_RIGHT_REDIRECTION)) {
		if (fd != 0)
			close(fd);
		if (cmd->operator == RIGHT_REDIRECTION)
			fd = open(cmd->name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (cmd->operator== DOUBLE_RIGHT_REDIRECTION)
			fd = open(cmd->name, O_WRONLY | O_APPEND | O_CREAT, 0666); 
		if (fd == -1) {
			return (-1);
		}
		len--;
		cmd++;
	}
	ret = exec_command(c, env);
	close(fd);
	return (ret);
}