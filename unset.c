#include "minishell.h"

int ft_unset(t_env *env, char *key, char **args)
{
    int i;

    i = 0;
    if (args == NULL)
        delete_env_variable(env, key);
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