#include "libft.h"

int ft_strlen_2d(char **arr) {
    int i;

    i = 0;
    while (arr[i] != NULL)
        i++;

    return (i);
}
