#include "minishell.h"

int count(char *line, t_env *env)
{
    int i;
    int j;
    char *key;
    int counter;
    char *var;

    counter = 0;
    i = 0;
    while (line[i] != '\0') 
    {
        if (line[i] == '$') {
            j = i + 1;
            while (line[j] != ' ' && line[j] != '\0') {
                j++;
            }
            key = ft_strndup(line + i + 1, j - i - 1);
            i = j - 1;
            if (key == NULL) 
                return (-1);
            var = my_getenv(env, key);
            if (var != NULL)
            {
                counter += ft_strlen(var);
                free(var);
            }
        }
        else
            counter++;
        i++;
    }
    return (counter);
}

int fill(char *newline, char *line, t_env *env)
{
    int i;
    int j;
    char *key;
    int counter;
    char *var;

    counter = 0;
    i = 0;
    while (line[i] != '\0') 
    {
        if (line[i] == '$') {
            j = i + 1;
            while (line[j] != ' ' && line[j] != '\0') {
                j++;
            }
            key = ft_strndup(line + i + 1, j - i - 1);
            i = j - 1;
            if (key == NULL) 
                return (-1);
            var = my_getenv(env, key);
            if (var != NULL)
            {
                ft_strncpy(newline + counter, var, ft_strlen(var));
                counter += ft_strlen(var);
                free(var);
            }
        }
        else
        {
            newline[counter] = line[i];
            counter++;
        }
        i++;
    }
    newline[counter + 1] = '\0';
    return (0);
}

char *ft_expand(char *line, t_env *env)
{
    char *newline;
    int len;

    len = count(line, env);
    if (len == -1)
        return (NULL);
    newline = malloc(len + 1);
    if (newline == NULL)
        return (NULL);
    if (fill(newline, line, env) == -1) {
        free(newline);
        return (NULL);
    }
    return (newline);
}