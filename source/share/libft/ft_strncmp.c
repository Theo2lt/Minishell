/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:55:52 by engooh            #+#    #+#             */
/*   Updated: 2022/08/07 04:43:17 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (!n)
		return (0);
	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[i] && p2[i] && p1[i] == p2[i] && i < n - 1)
		i++;
	if (i != (n - 1))
		return (1);
	return (p1[i] - p2[i]);
}

int	ft_strncmp3(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!str2)
		return (str1[i]);
	if (!str1)
		return (-str2[i]);
	while (str1[i] == str2[i] && (i < n - 1) && str1[i] && str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (s1[i]);
	if (!s1)
		return (-s2[i]);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		if (s1[i] < s2[i] || s1[i] > s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}*/
