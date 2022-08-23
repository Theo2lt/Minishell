/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:42:51 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 13:49:57 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*set_arg(char *start, char *res, t_exec *exec)
{
	char	*tmp;
	char	*new;
	char	charset[2];

	charset[0] = 127;
	charset[1] = 0;
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
			return (set_arg(tmp + 1, res, exec));
	ft_positive_negative(res, 1);
	exec->args = ft_strjoin(exec->args, res);
	exec->args = ft_strjoin(exec->args, charset);
	if (res)
		free(res);
	return (tmp);
}

char	*set_cmd(char *start, char *res, t_exec *exec)
{
	char	*tmp;
	char	*new;
	char	charset[2];

	charset[0] = 127;
	charset[1] = 0;
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
			return (set_cmd(tmp + 1, res, exec));
	ft_positive_negative(res, 1);
	exec->args = ft_strjoin(exec->args, res);
	exec->args = ft_strjoin(exec->args, charset);
	if (res)
		free(res);
	return (tmp);
}

t_exec	*add_exec(t_exec **exec, t_exec *new)
{
	if (exec && *exec)
		add_exec(&((*exec)->next), new);
	*exec = new;
	(*exec)->next = NULL;
	return (*exec);
}

t_exec	*set_tocken(t_token *tkn, t_exec *exec, char *str)
{
	if (!exec)
	{
		exec = malloc(sizeof(t_exec));
		if (!exec)
			return (NULL);
		exec->tabs_exeve = NULL;
		exec->env = tkn->env;
		tkn->type_redir = 0;
		exec->next = NULL;
		exec->args = NULL;
		exec->outfile = 1;
		exec->infile = 0;
		tkn->exec = exec;
		tkn->redir = 0;
		tkn->cmd = 0;
		if (!tkn->begin)
			tkn->begin = exec;
		if (tkn->begin)
			tkn->begin = add_exec(&tkn->begin, exec);
	}
	ft_converte_str(str, -1);
	return (exec);
}

t_exec	*tocken(char *str, t_token *tkn, t_exec *exec)
{
	if (!str || !*str)
		return (exec);
	exec = set_tocken(tkn, exec, str);
	while (*str && *str != '|')
	{
		if (tkn->cmd == 0 && tkn->redir == 0
			&& !ft_strchr(" <>|", *str) && ++tkn->cmd)
			str = set_cmd(str, NULL, tkn->exec);
		if (tkn->cmd >= 1 && tkn->redir == 0 && !ft_strchr(" <>|", *str))
			str = set_arg(str, NULL, tkn->exec);
		if (tkn->redir == 0 && (*str == '<' || *str == '>') && ++tkn->redir)
			str = set_redir(str, &tkn->type_redir);
		if (tkn->redir == 1 && !ft_strchr(" <>|", *str) && !(--tkn->redir)
			&& if_expende_heredoc(str, tkn))
			str = set_file(str, NULL, tkn);
		if (!str)
			return (exec);
		if (*str && *str != '|')
			str++;
	}
	exec->tabs_exeve = ft_split(exec->args, 127);
	if (*str && *str == '|')
		exec->next = tocken(str + 1, tkn, exec->next);
	return (exec);
}
