/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 23:44:03 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 17:45:41 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Minishell.h"

int	ft_parser_quote(char *str)
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
		return (0);
	return (1);
}

int	ft_parser_chevron_and_pipe(char *str)
{
	int	stop;

	if (!str)
		return (0);
	stop = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '<' && *str != '>' && *str != '|')
			stop = 1;
		else if (stop && (*str == '<' || *str == '>'))
			stop = 0;
		if (*str && (*str == '<' || *str == '>'))
			str = ft_parser_chevron_utils(str + 1, *str);
		else if (*str == '|')
			str = ft_parser_pipe_utils(str + 1, stop);
		if (!str)
			return (0);
		str++;
	}
	return (1);
}

int	ft_parser_quote_chevron_pipe(char *str)
{
	if (!ft_parser_quote(str) && printf("ko quote\n"))
		return (0);
	ft_converte_quotes(str);
	//printf("test in == %s\n", str);
	if (!ft_parser_chevron_and_pipe(str))
		return (0);
	ft_converte_quotes(str);
	//printf("test out == %s\n", str);
	return (0);
}

int	parser(char *str)
{
	if (!str)
		return (0);
	if (!ft_parser_quote_chevron_pipe(str))
		return (0);
	return (1);
}
