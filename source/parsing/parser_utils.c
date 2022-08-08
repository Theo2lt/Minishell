/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 23:44:15 by engooh            #+#    #+#             */
/*   Updated: 2022/07/29 22:50:39 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Minishell.h"

char	*puterror(char *str)
{
	ft_putstr_fd(str, 2);
	return (NULL);
}

char	*ft_parser_pipe_utils(char *str, int stop)
{
	if (!str)
		return (NULL);
	while (stop && *str && *str == ' ')
		str++;
	if (!*str)
		return (puterror(
				"bash: syntax error near unexpected token `newline'\n"));
	if (*str == '|' || !stop)
		return (puterror("bash: syntax error near unexpected token `|'\n"));
	return (str);
}

char	*ft_parser_chevron_utils(char *str, char c)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	while (*str && *str == ' ')
		str++;
	if (!*str)
		return (puterror(
				"bash: syntax error near unexpected token `newline'\n"));
	if (*str == '|')
		return (puterror(
				"bash: syntax error near unexpected token `|'\n"));
	if ((*str == '<' || *str == '>') && str > tmp)
		return (puterror("bash: syntax error near unexpected token `< >'\n"));
	if ((*str == '<' || *str == '>') && str == tmp)
	{
		if (*str != c)
			return (puterror(
					"bash: syntax error near unexpected token `< >'\n"));
		if (*(str + 1) && (*(str + 1) == '<' || *(str + 1) == '>'))
			return (puterror(
					"bash: syntax error near unexpected token `< >'\n"));
	}
	return (str);
}

char	*ft_check_expend(char *str, char c)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	if (c == '"')
	{
		if (*str == '$' && *(str + 1) && (ft_isalpha(*(str + 1))
				|| *(str + 1) == '_'))
		{
			str++;
			while (*str && (ft_isalnum(*str) || *str == '_'))
				str++;
			return (str);
		}
	}
	return (tmp);
}

void	ft_converte_quotes(char *str, int signe)
{
	char	c;

	if (!str)
		return ;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *(str++);
			while (*str && *str != c)
			{
				str = ft_check_expend(str, c);
				if (*str && *str == c)
					break ;
				if (signe < 0 && *str > 0)
					*str = -1 * *str;
				if (signe > 0 && *str < 0)
					*str = -1 * *str;
				str++;
			}
		}
		str++;
	}
}
