/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 23:44:03 by engooh            #+#    #+#             */
/*   Updated: 2022/08/23 13:51:50 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*print_syntaxe_error(char c)
{
	if (c == '\'')
		printf("bosh: syntax error near unexpected token `quotes'\n");
	else if (c == '<' || c == '>' || c == '|')
		printf("bosh: syntax error near unexpected token `%c'\n", c);
	else
		printf("bosh: syntax error near unexpected token `newline'\n");
	(*g_global)->exit_code = 2;
	return (NULL);
}

char	*check_expende(char *str, int mode)
{
	if (!str)
		return (NULL);
	if (str && !*str)
		return (str);
	if (!mode && *str == '$' && ++str)
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	else if (mode && *str == '$' && ++str)
		if (*str && (ft_isalpha(*str) || *str == '_'))
			while (*str && (ft_isalnum(*str) || *str == '_'))
				str++;
	if (*str == '$')
		return (check_expende(str, mode));
	return (str);
}

void	ft_converte_str(char *str, int signe)
{
	int	c;	

	if (!str)
		return ;
	while (str && *str)
	{
		if (*str == '\'' || *str == '"')
		{
			c = *str++;
			while (*str && *str != c)
			{
				if (c == '"')
					str = check_expende(str, 0);
				if (*str && *str != c && *str > 0 && signe < 0)
					*str *= -1;
				if (*str && *str != c && *str < 0 && signe > 0)
					*str *= -1;
				if (*str && *str != c)
					str++;
			}
		}
		if (*str)
			str++;
	}
}

int	parser_quote(char *str)
{
	int	single_quote;
	int	double_quote;

	if (!str)
		return (0);
	single_quote = 0;
	double_quote = 1;
	while (*str)
	{
		if (*str == '"' && !double_quote && !single_quote)
			double_quote = 1;
		else if (*str == '"' && double_quote && !single_quote)
			double_quote = 0;
		else if (*str == '\'' && !single_quote && double_quote)
			single_quote = 1;
		else if (*str == '\'' && single_quote && double_quote)
			single_quote = 0;
		str++;
	}
	if (single_quote == double_quote)
	{
		print_syntaxe_error('\'');
		return (0);
	}
	return (1);
}

char	*parser_chevron_pipe_utils(char *str, int c, int *espace)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	while (*tmp && *tmp == ' ')
		tmp++;
	if (!*tmp)
		return (print_syntaxe_error(0));
	if (c == '|' && *tmp == c)
		return (print_syntaxe_error(c));
	if ((c == '<' || c == '>')
		&& (*tmp == '<' || *tmp == '>' || *tmp == '|') && tmp - str)
		return (print_syntaxe_error(c));
	if ((c == '<' || c == '>')
		&& (*tmp == '<' || *tmp == '>' || *tmp == '|') && c != *tmp)
		return (print_syntaxe_error(c));
	if ((c == '<' || c == '>') && (*tmp == '<' || *tmp == '>') && c == *tmp)
		if (tmp[1] == '<' || tmp[1] == '>' || tmp[1] == '|')
			return (print_syntaxe_error(c));
	if (*tmp == '<' || *tmp == '>')
		return (parser_chevron_pipe_utils(tmp + 1, *tmp, espace));
	return (tmp - 1);
}
