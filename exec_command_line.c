#include "minishell.h"

int print_env_value(t_env *env, char *key)
{
	char *str;

	str = my_getenv(env, key);
	printf("%s\n", str);
	return (0);
}

int buildins(t_cmdop *cmd, t_env *env)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return ft_cd(env, cmd->args[0]);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return pwd();
	if (ft_strcmp(cmd->name, "echo") == 0)
		return ft_echo(env, cmd->args);
	if (ft_strcmp(cmd->name, "env") == 0)
		return ft_env(env, cmd);
	if (ft_strcmp(cmd->name, "export") == 0)
		return ft_export(env, cmd->name, cmd->args);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return ft_unset(env, cmd->name, cmd->args);
	return (0);
}

bool is_buildins(t_cmdop *cmd)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		return true;
	if (ft_strcmp(cmd->name, "cd") == 0)
		return true;
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return true;
	if (ft_strcmp(cmd->name, "echo") == 0)
		return true;
	if (ft_strcmp(cmd->name, "env") == 0)
		return true;
	if (ft_strcmp(cmd->name, "export") == 0)
		return true;
	if (ft_strcmp(cmd->name, "unset") == 0)
		return true;
	return (false);
}

// execute the buildins and binary commands
int exec_command(t_cmdop *cmd, t_env *env)
{
	if (cmd->operator== DOUBLE_LEFT_REDIRECTION)
	{
		// Ignore
		return (EXIT_SUCCESS);
	}
	if (is_buildins(cmd) == true)
	{
		buildins(cmd, env);
		return (EXIT_SUCCESS);
	}
	binary_command(env, cmd->name, cmd->args, cmd->nb_args);
	if (env->result == 127)
		return (127);
	return (EXIT_SUCCESS);
}

int exec_operator(t_cmdop *command_line, int len, t_env *env)
{
	int status;

	status = 0;
	if (len == 1 && command_line->operator== DOUBLE_LEFT_REDIRECTION)
	{
		// ignore
	}
	else if (len == 1)
		status = exec_command(command_line, env);
	else if (command_line[1].operator== PIPE)
		status = pipeline_exec(command_line, env, len);
	else if (command_line[1].operator== LEFT_REDIRECTION)
		status = left_redirect_exec(command_line, env, len);
	else if (command_line[1].operator== RIGHT_REDIRECTION ||
			 command_line[1].operator== DOUBLE_RIGHT_REDIRECTION)
		status = right_redirect_exec(command_line, env, len);
	else if (command_line[0].operator== DOUBLE_LEFT_REDIRECTION)
		status = exec_command_line(command_line + 1, len - 1, env); // go next
	else
		status = exec_command(command_line, env);
	return (status);
}

// exec cmd line with some conditions.
int exec_command_line(t_cmdop *command_line, int len, t_env *env)
{
	pid_t childpid;
	int status;

	status = 0;
	if (len == 1 && is_buildins(command_line) == true)
		buildins(command_line, env);
	else
	{
		childpid = fork();
		if (childpid == -1)
			return (-1);
		if (childpid == 0)
		{
			signal(SIGINT, child_signal);
			exec_operator(command_line, len, env);
			exit(status);
		}
		waitpid(childpid, &status, 0);
	}
	env->result = WEXITSTATUS(status);
	return (env->result);
}