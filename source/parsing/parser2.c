/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:50:55 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 13:51:53 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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
			if (*str == '|' && espace && !print_syntaxe_error('|'))
				return (0);
			str = parser_chevron_pipe_utils(str + 1, *str, &espace);
			if (!str)
				return (0);
		}
		if (str && *str)
			str++;
	}
	return (1);
}

t_exec	*parser(char *str, t_env *env)
{
	t_exec		*exec;
	t_token		tkn;

	exec = NULL;
	if (!str)
		return (NULL);
	if (!parser_quote(str))
		return (NULL);
	ft_converte_str(str, -1);
	if (!parser_chevron_pipe(str))
		return (NULL);
	str = parser_expende(str, env, 0);
	if (!str)
		return (NULL);
	tkn.env = env;
	tkn.begin = NULL;
	exec = tocken(str, &tkn, NULL);
	if (str)
		free(str);
	return (exec);
}
