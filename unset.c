#include "minishell.h"

int ft_unset(t_env *env, char **args)
{
    int i;

    i = 0;
    if (args[0] == NULL)
    {
        printf("here in unset\n");
        delete_env_variable(env, args[i]);
    }
    else if (args != NULL)
    {
        while (args[i])
        {
            delete_env_variable(env, args[i]);
            i++;
        }
    }
    return (0);
}