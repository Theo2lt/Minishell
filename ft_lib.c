/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:30:15 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 04:52:16 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}

// a supprimer 
char	*ft_strdup(char *s1)
{
	char	*str;
	if(!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (str == NULL)
		return (NULL);
	else
		str = ft_strcpy(str, s1);
	return (str);
}

int	ft_char_set(char *str, char c)
{
	int	i;
	
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if(!str)
		return(0);
	return (i);
}

char	*ft_strjoin(char  *s1,char  *s2)
{
	int		len;
	char	*str;
	int		i;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	y = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		str[i + y] = s2[y];
		y++;
	}
	free(s2);
	str[y + i] = '\0';
	return (str);
}
// DEMANDER A RICKO SI ON PEUT MODIF CA LIBFT
int	ft_strcmp(char *s1, char *s2)
{
	int i;

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
}