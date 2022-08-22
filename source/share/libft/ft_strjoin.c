/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:41:22 by engooh            #+#    #+#             */
/*   Updated: 2022/08/22 16:11:33 by engooh           ###   ########.fr       */
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

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*c;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	c = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (c);
}

char	*ft_joint_free_s2(char *str1, char *str2)
{
	char	*str_join;

	str_join = NULL;
	str_join = ft_strjoin2(str1, str2);
	if (str2)
		free(str2);
	return (str_join);
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
