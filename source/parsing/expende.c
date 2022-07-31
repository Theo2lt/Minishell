/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expende.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:52:00 by engooh            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/31 17:50:24 by engooh           ###   ########.fr       */
=======
/*   Updated: 2022/07/29 22:48:34 by engooh           ###   ########.fr       */
>>>>>>> 650e81247cc84a1761bd5e7eef3a0df5323f8416
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

void	ft_converte_expende(char *str)
{
	while (str && *str)
	{
		if (ft_strchr("<>|\"\'", *str))
			*str *= -1;
		str++;
	}
}

char	*ft_expende(t_env *env, char *str, int start, int end)
{
	char		*tmp;
	char		*content;

	content = ft_getenv(env, str + start, (end - start));
	ft_converte_expende(content);
	if (content)
		tmp = ft_replace(str, content, start, end);
	if (!content)
		tmp = ft_replace(str, NULL, start, end);
	return (tmp);
}

char	*parser_expende(char *str, t_env *env)
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
