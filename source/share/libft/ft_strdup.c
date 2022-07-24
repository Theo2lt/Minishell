/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:10:17 by engooh            #+#    #+#             */
/*   Updated: 2022/07/23 23:23:41 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*p;
	int	l;

	l = ft_strlen(s) + 1;
	p = malloc(l * sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s, l);
	return (p);
}
