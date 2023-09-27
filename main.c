/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Famahsha < famahsha@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:15 by ansulist          #+#    #+#             */
/*   Updated: 2023/08/01 16:51:21 by Famahsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_exit = 0;

// int main(int argc, char **av, char **default_env) {
//     t_env *env;
//     (void)argc;
//     (void)av;
//     env = init_env(default_env);
//     // display_env(env);

//     // char *ls_args[2] = {
//     //     "-l",
//     //     NULL,
//     // }; 

//     char *echo_args[1] = {
//         "ANITA",
//     }; 

//     // ls -l | cat ./cat.c
//     t_cmdop command[1] = {
//         // {
//         //   "ls",
//         //   ls_args,
//         //   1,
//         //   NONE,
//         // },
//         // {
//         //   NULL,
//         //   NULL,
//         //   0,
//         //   PIPE,
//         // },
//         {
//           "env",
//           echo_args,
//           1,
//           NONE,
//         },
//     };

//     exec_command_line(command, 1, env);

//     // add_env_variable(env, "ANITA", "AWESOME");
//     // delete_env_variable(env, "ANITA");
//     // display_env(env);
//     // add_or_update(env, "ANITA", "DUMB");
//     // display_env(env);
//     // add_or_update(env, "ANITA", "HELOLO");
//     // display_env(env);

//     /*
//     const char *arr[3];
//     arr[0] = "blah";
//     arr[1] = "ANITA=$ANITA HELLO";
//     arr[2] = 0;

//     ft_echo(env, (char **)arr, 1);
//     */
//     /*
//    printf ("prev === %s\n", getcwd(NULL, 0));
//    ft_cd(env, "/Users/anitasulistiyawati/Desktop");
//    printf ("after === %s\n", getcwd(NULL, 0));
//    */
//    //char *result = ft_strreplace("anita", "~", "/home/anitasulistiyawati");

//    //printf("%s\n", result);
// }

#include "minishell.h"


int	ft_cerror(void)
{
	printf("zsh : command not found \n");
	return (0);
}

int	ft_error(void)
{
	printf("zsh : parse error \n");
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env *env;

	if (ac != 1)
	{
		printf("invalid no of arguments\n");
		return (0);
	}
	config_signal();
	env = init_env(envp);
	if (env == NULL)
		return (-1);
	initialize_prompt(av, env);
	return (0);
}