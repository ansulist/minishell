#include <stdlib.h>
#include <stdbool.h>
#include<string.h>


int	ft_myisspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v')
		return (1);
	return (0);
}

char *ft_mystrchr(char *s, int c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == (char)c)
            return (char *)(s + i);
        i++;
    }
    if (s[i] == (char)c)
        return (char *)(s + i);
    return NULL;
}

int count_special_chars(char *string, char *special_chars)
{
    int count = 0;
    while (*string)
    {
        if (ft_mystrchr(special_chars, *string))
            count++;
        string++;
    }
    return count;
}

char *process_special_chars(char *string, char *special_chars)
{
    int count = count_special_chars(string, special_chars);
    char *temp = (char *)malloc((strlen(string) + (2 * count) + 1) * sizeof(char));
    char *result = temp;

    while (*string)
    {
        if (ft_mystrchr(special_chars, *string))
        {
            *temp++ = ' ';
            if (ft_mystrchr(special_chars, *(string + 1)))
                *temp++ = *string;
            *temp++ = *string;
            while (*(string + 1) && ft_mystrchr(special_chars, *(string + 1)))
                string++;
            if (*(string + 1) && (!ft_myisspace(*(string + 1))))
                *temp++ = ' ';
        }
        else
        {
            *temp++ = *string;
        }
        string++;
    }
    *temp = '\0';
    return result;
}
