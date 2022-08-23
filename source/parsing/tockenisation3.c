/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:44:30 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 18:22:34 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	set_outfile(char *str, t_exec *exec, int mode)
{
	if (mode == 3 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (exec->outfile < 0)
		{
			ft_print_error_file(str, strerror(errno));
			(*g_global)->exit_code = 1;
		}
	}
	else if (mode == 1 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (exec->outfile < 0)
		{
			ft_print_error_file(str, strerror(errno));
			(*g_global)->exit_code = 1;
		}
	}
	if (exec->outfile < 0)
		return (0);
	return (1);
}

char	*set_redir(char *str, int *type_redir)
{
	if (*str == '<' && str[1] && str[1] == '<' && ++str && ++str)
	{
		*type_redir = 4;
		while (*str && *str == ' ')
			str++;
		if (*str == '\'' || *str == '"')
			*type_redir = 5;
	}
	else if (*str == '>' && str[1] && str[1] == '>' && ++str && ++str)
		*type_redir = 3;
	else if (*str == '<' && ++str)
		*type_redir = 2;
	else if (*str == '>' && ++str)
		*type_redir = 1;
	return (str);
}

char	*set_begin(char	*str)
{
	if (!str)
		return (NULL);
	if (*str && *str == '$')
		if (str[1] && (str[1] == '\'' || str[1] == '"'))
			return (str + 2);
	if (*str && (*str == '\'' && *str == '"'))
		return (str + 1);
	return (str);
}

int	if_expende_heredoc(char *str, t_token *tkn)
{
	if (tkn->type_redir >= 4)
	{
		if (!str)
			return (1);
		while (*str && *str != '"' && *str != '\'' && *str != ' ')
			str++;
		if (*str == '"' || *str == '\'')
			tkn->type_redir = 5;
		else
			tkn->type_redir = 4;
	}
	return (1);
}

char	*set_file(char *start, char *res, t_token *tkn)
{
	char	*tmp;
	char	*new;

	start = set_begin(start);
	tmp = start;
	while (*tmp && !ft_strchr("\"'<>| ", *tmp))
		tmp++;
	new = ft_substr(start, 0, tmp - start);
	res = ft_strjoin(res, new);
	if (new)
		free(new);
	if (*tmp && (*tmp == '\'' || *tmp == '"'))
		if (tmp[1] && !ft_strchr("<>| ", tmp[1]))
			return (set_file(tmp + 1, res, tkn));
	ft_positive_negative(res, 1);
	if (tkn->type_redir == 1 || tkn->type_redir == 3)
		set_outfile(res, tkn->exec, tkn->type_redir);
	if (tkn->type_redir == 2 || tkn->type_redir >= 4)
		if (!set_infile(tkn, res, tkn->exec))
			return (NULL);
	if (tkn->type_redir == 2 && res)
		free(res);
	return (tmp);
}
