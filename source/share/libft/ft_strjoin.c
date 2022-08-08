/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh.1@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:41:22 by engooh            #+#    #+#             */
/*   Updated: 2022/08/04 10:04:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*c;
	char	*p;
	char	*tmp;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	c = p;
	tmp = (char *)s1;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	free(tmp);
	return (c);
}
/*
int	*ft_strjoin2(int *s1, int *s2)
{
	int	*c;
	int	*p;
	int	*tmp;

	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen2(s1) + ft_strlen2(s2) + 1) * sizeof(int));
	if (!p)
		return (NULL);
	c = p;
	tmp = s1;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	free(tmp);
	return (c);
}*/
