/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh.1@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:50:59 by engooh            #+#    #+#             */
/*   Updated: 2022/07/13 04:41:42 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_cntword(char const *s, char c, int n)
{
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

char	**ft_split_utils(char **p, char *s, char c, int len)
{
	int	j;
	int	i;

	j = -1;
	while (++j < len)
	{
		while (*s && *s == c)
			s++;
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		*p++ = ft_substr(s, 0, i);
		if (!*(p - 1))
			ft_free_tabs((void *)p - 1);
		while (*s && *s != c)
			s++;
	}
	*p = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		l;
	char	**p;
	char	**q;

	if (!s)
		return (NULL);
	l = ft_cntword(s, c, 0);
	p = malloc((l + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	q = p;
	p = ft_split_utils(p, (char *)s, c, l);
	return (q);
}
