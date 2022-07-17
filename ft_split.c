/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 00:03:40 by tliot             #+#    #+#             */
/*   Updated: 2022/07/17 00:16:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///// SPLIT ////


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

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
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
}

///
