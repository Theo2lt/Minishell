/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 04:07:45 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/21 03:05:59 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"
 
static int	lex_pipe(char *str)
{
	int	i;
	int	bool_char;
	int	bool_pipe;

	i = 0;
	bool_char = 1;
	bool_pipe = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			bool_char = 0;
		if (str[i] == '|')
		{
			if (bool_char == 1)
				return (0);
			bool_pipe = 1;
			bool_char = 1;
		}
		i++;
	}
	if (bool_pipe == 1 && bool_char == 1)
		return (0);
	return (1);
}

static int	lex_quote(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 1;
	while (str[i])
	{
		if (str[i] == '"' && double_quote == 1 && single_quote == 0)
			double_quote = 0;
		else if (str[i] == '"' && double_quote == 0 && single_quote == 0)
			double_quote = 1;
		else if (str[i] == '\'' && single_quote == 0 && double_quote == 1)
			single_quote = 1;
		else if (str[i] == '\'' && single_quote == 1 && double_quote == 1)
			single_quote = 0;
		i++;
	}
	if (single_quote == double_quote)
		return (0);
	return (1);
}

int	lexer_shell(char **str, t_pars *pars)
{

	//pars->expand = 0;
	if (!lex_quote(*str) && printf("quote KO\n"))
		return (0);
	ft_negative_quote(*str, pars);
	if (!lex_pipe(*str) && printf("pipe KO\n"))
		return (0);
	if (!lexer_redi(*str, pars) && printf("redir KO\n"))
		return (0);
	printf("res converte quote = [%s]\n", *str);
	*str = ft_init_pars(*str, pars);
	ft_positive_char(*str, pars);
	printf("after converte quote = [%s]\n", *str);
	return (1);
}

void	ft_exit(int exit_code)
{
	exit(exit_code);
}