/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:58:52 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 02:46:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_tab(void **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab[i]);
	free(tab);
	return (1);
}

char   **ft_free_tab2(char **tab)
{
    int    i;

    i = 0;
    while (tab && tab[i])
    {
        free(tab[i]);
        i++;
    }
    if(tab)
        free(tab);
    return (NULL);
}
