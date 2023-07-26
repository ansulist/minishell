#include "minishell.h"

extern long long	g_exit;

static void	exit_non_nb_arg(void)
{
	g_exit = 2;
	ft_putendl_fd("./minishell : args is not number", STDERR_FILENO);
}

int ft_count_array(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}

void    ft_exit(t_cmdop *cmd)
{
    int nb_args;

    nb_args = ft_count_array(cmd->args);
    ft_putendl_fd("exit minishell, bye!", STDOUT_FILENO);
    if (nb_args == 1)
    {
        if (digits_or_signals(cmd->args[0]) == true)
        {
            if (is_longlong(cmd->args[0]) == true)
                g_exit = ft_atoll(cmd->args[0]);
            else
                exit_non_nb_arg();

        }
        else
            exit_non_nb_arg();
    }
    else if (nb_args > 1)
    {
        g_exit = 2;
        ft_putendl_fd("./minishell : Too many argument", STDERR_FILENO);
    }
    // TODO FREE EVERYTHING AFTER EXIT 
    exit(g_exit);
}