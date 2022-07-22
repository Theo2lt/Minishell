/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh.1@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:50:59 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 02:00:30 by engooh           ###   ########.fr       */
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

///// SPLIT ////
/*
static int	n_word(char const *s, char c)
{
	int	n_word;
	int	i;

	n_word = 0;
	i = 0;
	if (s[i] && s[0] != c)
		n_word++;
	while (s[i] && s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			n_word++;
		i++;
	}
	if (n_word == 0)
		return (0);
	return (n_word);
}

static char	**write_word(char const *s, char sep, char **tab)
{
	int	i;
	int	nbr_lettre;
	int	nbr_word;

	i = -1;
	nbr_lettre = 0;
	nbr_word = 0;
	while (s[++i])
	{
		if (s[i] == sep)
		{
			if (nbr_lettre != 0)
			{
				tab[nbr_word++] = ft_substr(s, i - nbr_lettre, nbr_lettre);
				if (!tab[nbr_word - 1])
					return (ft_free_tab(tab));
			}
			nbr_lettre = 0;
		}
		else
			nbr_lettre++;
	}
	if (nbr_lettre != 0)
		tab[nbr_word] = ft_substr(s, i - nbr_lettre, nbr_lettre);
	return (tab);
}

static char	**ft_null(char const *string, char **tab)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	if (i == 0)
	{
		tab[0] = malloc(sizeof(char));
		tab[0] = NULL;
		return (tab);
	}
	tab[0] = ft_substr(string, 0, i);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= 0)
	{
		tab = malloc(sizeof(char) * (1));
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc((n_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[n_word(s, c)] = NULL;
	if (ft_strchr(s, c))
		return (write_word(s, c, tab));
	else
		return (ft_null(s, tab));
}*/
