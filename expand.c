#include "minishell.h"

int count_nbr(int nbr)
{
    int i;

    i = 0;
    if (nbr <= 0)
        return (1);
    if (nbr > 0)
    {
        while (nbr > 0)
        {
            nbr /= 10;
            i++;
        }
    }
    return (i);
}

// Count size of value behind $ variables
// i.e $HOME when $HOME worth "/home/anita"
// returns 11
int count_dollar_var_len(char *line, t_env *env, int *i)
{
    int end;
    char *key;
    char *env_var;
    int var_len;

    var_len = 0;
    end = *i + 1;
    while (line[end] != ' ' && line[end] != '\0')
        end++;
    key = ft_strndup(line + *i + 1, end - *i - 1);
    if (key == NULL)
        return (-1);
    *i = end - 1;
    env_var = my_getenv(env, key);
    free(key);
    if (env_var != NULL)
    {
        var_len = ft_strlen(env_var);
        free(env_var);
    }
    return (var_len);
}

int count(char *line, t_env *env)
{
    int i;
    int var_len;
    char *key;
    int counter;
    char *var;

    counter = 0;
    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '$' && line[i + 1] == '?')
        {
            counter = count_nbr(env->result);
            i = i + 2;
        }
        else if (line[i] == '$')
        {
            var_len = count_dollar_var_len(line, env, &i);
            if (var_len == -1)
                return (-1);
            counter += var_len;
        }
        else
            counter++;
        i++;
    }
    return (counter);
}

// Replace $? with value behind
// i.e $? worth 127
// fills newline with "127"
int fill_dollar_question_mark(t_env *env, char *newline, int *counter)
{
    char *key;

    key = ft_itoa(env->result);
    if (key == NULL)
        return (-1);
    ft_strncpy(newline + *counter, key, ft_strlen(key));
    *counter += ft_strlen(key);
    free(key);
    return (0);
}

// Fill newline with value behind $ variables
// i.e $HOME when $HOME worth "/home/anita"
// fill newline with "/home/anita"
int fill_dollar_var_len(char *newline, t_env *env, int *i, int *counter)
{
    int end;
    char *key;
    char *env_var;

    end = *i + 1;
    while (newline[end] != ' ' && newline[end] != '\0')
        end++;
    key = ft_strndup(newline + *i + 1, end - *i - 1);
    if (key == NULL)
        return (-1);
    *i = end - 1;
    env_var = my_getenv(env, key);
    free(key);
    if (env_var == NULL)
        return (0);
    ft_strncpy(newline + *counter, env_var, ft_strlen(env_var));
    *counter += ft_strlen(env_var);
    free(env_var);
    return (0);
}

int fill(char *newline, char *line, t_env *env)
{
    int i;
    int counter;

    counter = 0;
    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '$' && line[i + 1] == '?')
        {
            if (fill_dollar_question_mark(env, newline, &counter) == -1)
                return (-1);
        }
        else if (line[i] == '$')
        {
            if (fill_dollar_var_len(newline, env, &i, &counter) == -1)
                return (-1);
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
    if (fill(newline, line, env) == -1)
    {
        newline[0] = '\0';
        return (newline);
    }
    return (newline);
}