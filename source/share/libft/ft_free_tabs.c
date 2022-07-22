/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:58:52 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 02:46:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_tab(void **tabs)
{
	int	i;

	if (!tabs)
		return (0);
	i = -1;
	while (tabs[++i])
		free(tabs[i]);
	free(tabs[i]);
	free(tabs);
	return (1);
}

char   **ft_free_tab2(char **tab)
{
    int    i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (NULL);
}
