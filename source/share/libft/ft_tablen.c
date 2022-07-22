
#include "libft.h"

int    ft_tablen(char **tab)
{
    int    i;

    i = 0;
    if (!tab[i])
        return (i);
    while (tab[i])
        i++;
    return (i);
}