/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:33 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/18 11:29:57 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_status;

int pipe_left(t_cmdop *cmd, t_env *env, int fd[2])
{
	close(fd[0]);
	// redirect eveything that was supposed to be written in STDOUT_FILENO to fd[1] (write in pipe)
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	// Execute ls
	exec_command(cmd, env);
	return (0);
}

int pipe_right(t_cmdop *cmd, t_env *env, int fd[2], int len)
{
	close(fd[1]);
	// redirect eveything that was supposed to be read in fd[0] in STDIN_FILENO (read in pipe)
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	// Execute grep
	exec_command_line(cmd, len, env);
	return (0);
}

int pipeline_exec(t_cmdop *cmd, t_env *env, int len)
{
	pid_t childpid;
	int fd[2];
	int temp;

	// make the exit function to quit
	if (pipe(fd) == -1)
		return (-1);
	childpid = fork();
	// make the exit function to quit
	if (childpid == -1)
		return (-1);
	if (childpid == 0)
	{
		pipe_left(cmd, env, fd);
		exit(0);
	}
	pipe_right(cmd + 2, env, fd, len - 2);
	close(fd[0]);
	close(fd[1]);
	waitpid(childpid, &temp, 0);
	return (0);
}



// ls | grep anita
// int main(int ac, char **av)
// {
//     // Create the pipe
//     int fd[2];

//     // 0: read
//     // 1: write
//     if (pipe(fd) == -1)
//     {
//         printf("error\n");
//         return (1);
//     }
//     int first_child_id = fork();
//     if (first_child_id == 0)
//     {
//         // We are in the first child
//         // We want to execute "ls"

//         // close the read
//         close(fd[0]);
//         // redirect eveything that was supposed to be written in STDOUT_FILENO to fd[1] (write in pipe)
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         // Execute ls
//         char *args[] = {"/bin/ls", "-l", NULL};
//         execve("/bin/ls", args, NULL);
//         // close(STDOUT_FILENO);
//         exit(0);
//     }
//     // Create a new process
//     int second_child_id = fork();
//     if (second_child_id == 0)
//     {
//         // We are in the first child
//         // We want to execute "grep anita"
//         // close the write
//         close(fd[1]);
//         // redirect eveything that was supposed to be read in fd[0] in STDIN_FILENO (read in pipe)
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         // Execute grep
//         char *args[] = {"/usr/bin/grep", "export", NULL};
//         execve("/usr/bin/grep", args, NULL);
//         // close(STDIN_FILENO);
//         exit(0);
//     }
//     // We are in the parent
//     // Wait all the children to finish their job
//     int first_child_status;
//     int second_child_status;

//     close(fd[0]);
//     close(fd[1]);

//     waitpid(first_child_id, &first_child_status, 0);
//     printf("First child finished\n");

//     waitpid(second_child_id, &second_child_status, 0);
//     printf("Second child finished\n");
// }
