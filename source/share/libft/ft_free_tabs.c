/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:58:52 by engooh            #+#    #+#             */
/*   Updated: 2022/08/19 18:06:40 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_free_tab(void **tabs)
{
	int	i;

	if (!tabs)
		return (0);
	i = -1;
	while (tabs[++i])
		if (tabs[i])
			free(tabs[i]);
	free(tabs);
	return (1);
}

char	**ft_free_tab2(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return (NULL);
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
