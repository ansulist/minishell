#include "minishell.h"

int	print_env_value(t_env *env, char *key)
{
	char *str;
	
	str = my_getenv(env, key);
	printf("%s\n", str);
	return (0);
}

// execute the buildins and binary commands
int exec_command(t_cmdop *cmd, t_env *env)
{
	// printf("EXECUTE COMMAND: %s\n", cmd->name);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return ft_cd(env, cmd->args[0]);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return pwd();
	if (ft_strcmp(cmd->name, "echo") == 0)
		return ft_echo(env, cmd->args);
	if (ft_strcmp(cmd->name, "env") == 0)
		return ft_env(env, cmd);
	if (ft_strcmp(cmd->name, "export") == 0)
		return display_export(env);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return ft_export(env, cmd->name, cmd->args);
	binary_command(env, cmd->name, cmd->args, cmd->nb_args);
	return (0);
}

// int single_command(t_cmdop *cmd, t_env *env, int len)
// {
// 	pid_t childpid;
// 	int status;

// 	if (len == 1)
// 	{
// 		childpid = fork();
// 		if (childpid == 0)
// 		{
// 			exec_command(cmd, env);
// 			exit(0);
// 		}
// 		else
// 			waitpid(childpid, &status, 0);
// 	}
// 	return (0);
// }

// exec cmd line with some conditions.
int exec_command_line(t_cmdop *command_line, int len, t_env *env)
{
	pid_t childpid;
	int status;

	childpid = fork();
	if (childpid == 0)
	{
		signal(SIGINT, child_signal);
		if (len == 1)
			 exec_command(command_line, env);
		else if ((command_line + 1)->operator== PIPE)
			 pipeline_exec(command_line, env, len);
		else {
			redirect_exec(command_line, env, len);
			// TODO: handle redirection
		}
		exit(0);
	}
	waitpid(childpid, &status, 0);
	// i = 0;
	// while (i < len)
	// {
	// 	if (command_line[i].operator == NONE)
	// 	{
	// 		if (exec_command(&command_line[i], env) == -1)
	// 			return (-1);
	// 	}
	// 	else if (command_line[i].operator == PIPE)
	// 	{
	// 		if (pipeline_exec(&command_line[i], env) == -1)
	// 			return (-1);
	// 	}
	// 	// else if (command_line[i].operator != NONE && command_line[i].operator != PIPE)
	// 	// {
	// 	// 	if (redirect_exec(&command_line[i], env) == -1)
	// 	// 		return (-1);
	// 	// }
	// 	i++;
	// }
	return (0);
}