/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:20:23 by engooh            #+#    #+#             */
/*   Updated: 2022/07/23 23:26:55 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	int	i;
	char	*p;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start > len || start > i)
		return ((char *)ft_calloc(sizeof(char), 1));
	if (len >= i - start)
		p = (char *)malloc(sizeof(char) * (i - start + 1));
	else
		p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (s[++i + start] && i < len)
		p[i] = s[i + start];
	p[i] = '\0';
	return (p);
}
