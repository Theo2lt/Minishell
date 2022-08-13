/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:50:59 by engooh            #+#    #+#             */
/*   Updated: 2022/08/13 13:40:36 by tliot            ###   ########.fr       */
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
			ft_free_tab((void *)p - 1);
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

char	**ft_split2_element(char *str, char c)
{
	char **split;
	int i;
	int y;
	
	i = 0;
	split = NULL;
	split = malloc(3 * sizeof(char *));
	
	while (str[i] && str[i] != c)
		i++;
	split[0] = ft_substr(str, 0, i);
	if(i == ft_strlen3(str))
		split[1] = 0;
	else
	{
		y = ++i;
		while (str[i])
			i++;
		split[1] = ft_substr(str, y, i);
	}
	split[2] = 0;
	return (split);
}