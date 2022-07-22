/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 03:51:31 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/21 03:05:41 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"
 
static int	 lexer_sens(char *str)
{
	int i;
	int	d;
	int	g;

	i = 0;
	d = 0;
	g = 1;
	while (str[i])
	{
		if (str[i] == '>' )
		{
			d = 1;
			while (str[i] && str[i + 1] && (str[i + 1] == ' '
					|| str[i + 1] == '>'))
				i++;
			if (str[i + 1] != '<' && str[i + 1])
				d = 0;
		}
		else if (str[i] == '<' && d == 1)
			g = 0;
		i++;
	}
	if (d && !g)
		return (0);
	return (1);
}

static int	lexer_redirection_char(char *str)
{
	int	i;
	int	chevron;
	int	espace;

	i = 0;
	espace = 0;
	chevron = 0;
	while (str[i])
	{
		if (chevron && espace && (str[i] == '>' || str[i] == '<'))
			return (0);
		if (str[i] == '>' || str[i] == '<')
			chevron = 1;
		else if (str[i] == ' ' && chevron)
			espace = 1;
		else if (chevron && str[i] != 32)
		{
			chevron = 0;
			espace = 0;
		}
		i++;
	}
	return (1);
}

static int lexer_last_redi(char *str, t_pars *pars)
{
	int	i;
	int	bool_char;

	(void)pars;
	bool_char = 0;
	i = ft_strlen(str) - 1;
	//pars->len = i + 1;
	while (i >= 0)
	{
		if (str[i] != ' ' && str[i] != '<' && str[i] != '>')
			bool_char = 1;
		if ((str[i] == '<' || str[i] == '>') && bool_char == 0)
		{
			return (0);
		}
		i--;
	}
	return (1);
}

static int	lexer_tripleredi(char *str)
{
	int	i;
	int	n;

	if (!str)
		return (0);
	i = -1;
	n = 0;
	while (str[++i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] == '>')
			return (0);
		if (str[i] == '<' || str[i] == '>')
			n++;
		else
			n = 0;
		if (n >= 3)
			return (0);
	}
	return (1);
}

 static int	lexer_redi_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[++i] == ' ' || str[i] == '<' || str[i] == '>')
			{
			}
			if (str[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

int	lexer_redi(char *str, t_pars *pars)
{
	if (!lexer_last_redi(str, pars) && printf("KO last chevron\n"))
		return (0);
	else if (!lexer_redi_pipe(str) && printf("KO chevron pipe\n"))
		return (0);
	else if (!lexer_redirection_char(str) && printf("KO chevron char\n"))
		return (0);
	else if (!lexer_sens(str) && printf("KO chevron sens\n"))
		return (0);
	else if (!lexer_tripleredi(str) && printf("KO chevron triple\n"))
		return (0);
	return (1);
}