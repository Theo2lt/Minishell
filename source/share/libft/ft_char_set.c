#include "libft.h"

int    ft_char_set(char *str, char c)
{
    int    i;

    i = 0;
    if(!str[0])
        return(0);
    while (str[i])
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return (0);
}