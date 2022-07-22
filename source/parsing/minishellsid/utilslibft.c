/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslibft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 07:58:21 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/18 04:44:36 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

 int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	if (!new || !alst)
		return ;
	if (*alst)
	{
		ft_lstlast(*alst)-> next = new;
	}
	else
		*alst = new;
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

int	ft_lstsize(t_env *lst)
{
	int			size;
	t_env		*current;

	current = lst;
	size = 0;
	if (!lst)
		return (size);
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_env	*ft_lstnew(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

char	*ft_strchr(char *str, int c)
{
	int				i;
	char			*s;
	unsigned char	d;

	s = (char *)str;
	d = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			return (s + i);
		i++;
	}
	if (d == 0)
		return (&s[i]);
	return (NULL);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)) + 1);
	if (!str)
		return (NULL);
	while (s1 && *s1)
	{
		str[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = '\0';
	return (str);
}



static int	ft_lengood(char *str, unsigned int len, unsigned int s)
{
	unsigned int	goodlen;

	goodlen = 0;
	while (goodlen < len && str[s])
	{
		goodlen++;
		s++;
	}
	return (goodlen);
}

char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * ft_lengood(s, len, start) + 1);
	if (!str)
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
