/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expende.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:52:00 by engooh            #+#    #+#             */
/*   Updated: 2022/07/28 20:10:02 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Minishell.h"

char	*ft_replace(char *str, char *node, int i, int j)
{
	char	*new;

	new = ft_substr(str, 0, i - 1);
	if (node)
	{
		new = ft_strjoin(new, node);
		new = ft_strjoin(new, str + j);
		printf("replace1 %s  str[%c]\n", new, str[j]);
		return (new);
	}
	new = ft_strjoin(new, str + j);
	printf("replace2 %s str[%c]\n", new, str[j]);
	return (new);
}

char	*ft_expende(t_env *env, char *str, int start, int end)
{
	char	*tmp;
	char	*content;

	content = ft_getenv(env, str + start, (end - start));
	if (content)
		tmp = ft_replace(str, content, start, end);
	if (!content)
		tmp = ft_replace(str, NULL, start, end);
	return (tmp);
}

char	*ft_parse_expende(char *str, t_env *env)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && (str[i + 1] == '_'
				|| ft_isalpha(str[i + 1])))
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			str = ft_expende(env, str, i + 1, j);
			i--;
		}
		else if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]))
		{
			str = ft_expende(env, str, i, i + 2);
			i--;
		}
	}
	return (str);
}
