/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:09 by ansulist          #+#    #+#             */
/*   Updated: 2023/07/13 11:08:53 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// joining the s1 and s2 then free the s1
char	*join_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*appended;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	appended = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!appended)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		appended[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		appended[i++] = s2[j++];
	appended[i] = '\0';
	free(s1);
	return (appended);
}

//getting the value of the path
static char **get_full_path(t_env *env)
{
    char *path;

    path = my_getenv(env, "PATH");
    return (ft_split(path, ':'));
}

static char *get_path_bin(t_env *env, char *cmd)
{
    int i;
    char *tmp;
    char *path_bin;
	char **path;

 	if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
	path = get_full_path(env);
	if (path == NULL)
		return (NULL);
    i = 0;
    while (path[i])
    {
        // join each path with the "/"
        tmp = ft_strjoin(path[i], "/");
        // join the path with the cmd
        path_bin = join_free(tmp, cmd);
        // check if there is the path or no
        // if there is then return the path to be executed
        if (access(path_bin, F_OK | X_OK) == 0)
            return (path_bin);
        free(path_bin);
        i++;
    }
	// TODO : Replece with the correct string
	printf ("./minishell : %s : command not found\n", cmd);
    return (NULL);
}

void print_2d_array(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		printf ("%s\n", str[i]);
		i++;
	}
}

void    binary_command(t_env *env, char *cmd, char **args, int nb_args)
{
    char *path_bin;
	char **envp;
	char **execve_args;
	int i;

	path_bin = get_path_bin(env, cmd);
	if (path_bin == NULL)
		return;
	execve_args = malloc(sizeof(char **) * (nb_args + 2));
	if (execve_args == NULL)
	{
		free(path_bin);
		return ;
	}
	execve_args[0] = path_bin;
	i = 0;
	while (i < nb_args) 
	{
		execve_args[i + 1] = args[i];
		i++;
	}
	execve_args[i + 1] = NULL;
	envp = ft_list_to_array(env->vars);
	if (envp == NULL) {
		printf("./minishell : no such file or directory\n");
		free(envp);
		free(path_bin);
		return;
	}
	// Need to fork before
	if(execve(path_bin, execve_args, envp) == -1)
		perror("error");
	ft_free_twod_array(envp);
	ft_free_twod_array(execve_args);
	free(path_bin);
}