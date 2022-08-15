/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 23:44:03 by engooh            #+#    #+#             */
/*   Updated: 2022/08/15 21:59:05 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/*int	ft_parser_quote(char *str)
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
	while (*str) {
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

char	*ft_parser_quote_chevron_pipe(char *str)
{
	if (!ft_parser_quote(str) && printf("ko quote\n"))
		return (NULL);
	ft_converte_quotes(str, -1);
	printf("test in == %s\n", str);
	if (!ft_parser_chevron_and_pipe(str))
		return (NULL);
	return (str);
}

char	*parser(char *str, t_env *env)
{
	if (!str)
		return (NULL);
	if (!ft_parser_quote_chevron_pipe(str))
		return (NULL);
	str = ft_parse_expende(str, env);
	ft_converte_quotes(str, 1);
	printf("test out == %s\n", str);
	return (str);
}
*/

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
		return (0);
	return (1);
}

char	*parser_chevron_pipe_utils(char *str, int c)
{
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = str;
	while (*tmp && *tmp == ' ')
		tmp++;
	if (!*tmp)
		return (NULL);
	if (c == '|' && *tmp == c)
		return (NULL);
	if ((c == '<' || c == '>')
		&& (*tmp == '<' || *tmp == '>' || *tmp == '|') && tmp - str)
		return (NULL);
	if ((c == '<' || c == '>')
		&& (*tmp == '<' || *tmp == '>' || *tmp == '|') && c != *tmp)
		return (NULL);
	if ((c == '<' || c == '>') && (*tmp == '<' || *tmp == '>') && c == *tmp)
		if (tmp[1] == '<' || tmp[1] == '>' || tmp[1] == '|')
			return (NULL);
	if (*tmp == '<' || *tmp == '>')
		return (parser_chevron_pipe_utils(tmp + 1, *tmp));
	return (tmp);
}

int	parser_chevron_pipe(char *str)
{
	int	espace;

	if (!str)
		return (0);
	espace = 1;
	while (str && *str)
	{
		if (*str != '|' && *str != '<' && *str != '>' && *str != ' ' && espace)
			espace = 0;
		if (*str == '<' || *str == '>' || *str == '|')
		{
			if (*str == '|' && espace && printf("KO sytanxe\n"))
				return (0);
			str = parser_chevron_pipe_utils(str + 1, *str);
			if (!str && printf("KO syntaxe\n"))
				return (0);
		}
		if (str && *str)
			str++;
	}
	return (1);
}

t_exec	*parser(char *str, t_env *env)
{
	t_exec	*exec;

	exec = NULL;
	if (!str || !env)
		return (NULL);
	if (!parser_quote(str))
		return (NULL);
	ft_converte_str(str, -1);
	if (!parser_chevron_pipe(str))
		return (NULL);
	str = parser_expende(str, env, 0);
	if (!str)
		return (NULL);
	exec = tocken(str, NULL, env, 0);
	if (str)
		free(str);
	return (exec);
}
