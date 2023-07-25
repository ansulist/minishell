#include "libft.h"

char *ft_strndup(char *str, int n)
{
    int i;
    char *res;

    i = 0;
    res = (char *)malloc(sizeof(char) * (n + 1));
    if (res == NULL)
        return (NULL);
    while (str[i] != '\0' && i < n)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}
