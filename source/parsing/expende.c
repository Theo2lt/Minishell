/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expende.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:52:00 by engooh            #+#    #+#             */
/*   Updated: 2022/08/19 14:38:40 by engooh           ###   ########.fr       */
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
		return (new);
	}
	new = ft_strjoin(new, str + j);
	return (new);
}

void	ft_converte_expende(char *str)
{
	while (str && *str)
	{
		if (ft_strchr("<>|", *str))
			*str *= -1;
		str++;
	}
}

	/* modifier ici par theo */
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
	if (str)
		free(str);
	if (content)
		free(content);
	return (tmp);
}

int	annule_exepend_heredoc(char *str, int i, int *heredoc)
{
	if (str[i] == '|' && *heredoc)
		*heredoc = 0;
	else if (str[i] == '<' && str[i + 1] && str[i + 1] == '<' && !*heredoc)
		*heredoc = 1;
	if (str[i] == '$' && *heredoc)
	{
		str[i] *= -1;
		*heredoc = 0;
	}
	return (i);
}

char	*parser_expende(char *str, t_env *env, int heredoc)
{
	int	i;
	int	j;

	i = -1;
	heredoc = 0;
	while (str && str[++i])
	{
		i = annule_exepend_heredoc(str, i, &heredoc);
		if (str[i] == '$' && str[i + 1] && (str[i + 1] == '_'
				|| ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			str = ft_expende(env, str, i + 1, j);
			i--;
		}
		else if (str[i] == '$' && str[i + 1]
			&& ft_isdigit(str[i + 1]))
		{
			str = ft_expende(env, str, i + 1, i + 2);
			i--;
		}
	}
	return (str);
}
