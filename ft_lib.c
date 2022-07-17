/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:30:15 by tliot             #+#    #+#             */
/*   Updated: 2022/07/17 00:10:40 by tliot            ###   ########.fr       */
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

void	*ft_memset(void *str, int c, int n)
{
	int			i;
	unsigned char	*str2;

	str2 = (unsigned char *)str;
	i = 0;
	while (n > i)
	{
		str2[i] = c;
		i++;
	}
	return (str2);
}


// pour splite
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

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, int start, int len)
{
	int	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s) - start)
		str = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && i < len && start <= ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

 /////// | ///////
 
int	ft_char_set(char *str, char c)
{
	int	i;
	
	i = 0;
	if(!str)
		return(0);
	while (str[i])
	{
		if(str[i] == c)
			return(i);
		i++;
	}
	return (0);
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

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && (i < n - 1) && str1[i] && str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

