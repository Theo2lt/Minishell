/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:20:23 by engooh            #+#    #+#             */
/*   Updated: 2022/07/31 17:48:20 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	i = -1;
	p = malloc(sizeof(char) * (len + 1));
	if (!p || !s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*p = '\0';
		return (p);
	}
	while (s[++i + start] && i < len)
		p[i] = s[i + start];
	p[i] = '\0';
	return (p);
}
