/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/08/04 11:04:09 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	set_herdoc(char *str, t_exec *exec, int mode)
{
	int	pid;
	char	*input;

	exec->infile = open("/tmp/", __O_TMPFILE | O_RDWR, 0666);
	if (exec->infile < 0)
			ft_putstr_fd("ERROR HERDOC", 2);
	pid = fork();
	if (!pid)
	{
		while (42)
		{
			input = readline(">");
			if (!input)
				exit(0);
			input = parser_expende(input, exec->env);
			ft_putstr_fd(input, exec->infile);
			if (input)
				free(input);
		}
		close(exec->infile);
		exit(0);
	}
	else if (pid)
		waitpid(pid, NULL, 0);
}

int	set_infile(char *str, t_exec *exec, int mode)
{
	if (mode == 2 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->infile = open(str, O_RDONLY, 0666);
		if (exec->infile < 0)
			ft_putstr_fd("ERROR INFILE", 2);
	}
	else if (mode == 5 || mode == 6)
		set_herdoc(str, exec, mode);
	if (exec->infile < 0)
		return (0);
	return (1);
}

int	set_outfile(char *str, t_exec *exec, int mode)
{       
	if (mode == 3 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	else if (mode == 1 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	if (exec->outfile < 0)
		return (0);
	return (1);
}

char	*set_redir(char *str, int *type_redir)
{
	if (*str == '<' && str[1] && str[1] == '<' && ++str && ++str)
		*type_redir = 4;
	else if (*str == '>' && str[1] && str[1] == '>' && ++str && ++str)
		*type_redir = 3;
	else if (*str == '<' && ++str)
		*type_redir = 2;
	else if (*str == '>' && ++str)
		*type_redir = 1;
	return (str);
}

char	*set_file(char *start, char *res, t_exec *exec, int type_redir)
{
	char	*tmp;
	char	*new;

	if (*start == '\'' || *start == '"')
		start++;
	tmp = start;
	while (*tmp && !ft_strchr("\"'<>| ", *tmp))
		tmp++;
	new = ft_substr(start, 0, tmp - start);
	res = ft_strjoin(res, new);
	if (!new)
		free(new);
	if (*tmp && (*tmp == '\'' || *tmp == '"'))
		if (tmp[1] && !ft_strchr("\"'<>| ", tmp[1]))
			return (set_file(tmp + 1, res, exec, type_redir));
	if (type_redir == 1 || type_redir == 2)
		set_outfile(res, exec, type_redir);
	if (type_redir == 3 || type_redir == 4)
		set_infile(res, exec, type_redir);
	return (tmp);
}

char	*set_arg(char *start, char *res, t_exec *exec)
{
	char	*tmp;
	char	*new;
	char	charset[2] = {127, '\0'};

	if (*start == '\'' || *start == '"')
		start++;
	tmp = start;
	while (*tmp && !ft_strchr("\"'<>| ", *tmp))
		tmp++;
	new = ft_substr(start, 0, tmp - start);
	res = ft_strjoin(res, new);
	if (!new)
		free(new);
	if (*tmp && (*tmp == '\'' || *tmp == '"'))
		if (tmp[1] && !ft_strchr("\"'<>| ", tmp[1]))
			return (set_arg(tmp + 1, res, exec));
	exec->args = ft_strjoin(exec->args, res);
	exec->args = ft_strjoin(exec->args, charset);
	return (tmp);
}

char	*set_cmd(char *start, char *res, t_exec *exec)
{
	char	*tmp;
	char	*new;

	if (*start == '\'' || *start == '"')
		start++;
	tmp = start;
	while (*tmp && !ft_strchr("\"'<>| ", *tmp))
		tmp++;
	new = ft_substr(start, 0, tmp - start);
	res = ft_strjoin(res, new);
	if (!new)
		free(new);
	if (*tmp && (*tmp == '\'' || *tmp == '"'))
		if (tmp[1] && !ft_strchr("\"'<>| ", tmp[1]))
			return (set_cmd(tmp + 1, res, exec));
	exec->cmd_name = ft_strjoin(exec->cmd_name, res);
	return (tmp);
}

t_exec	*tocken(char *str, t_env *env)
{
	t_exec	exec;
	int		cmd;
	int		redir;
	int		type_redir;

	cmd = 0;
	redir = 0;
	exec.env = env;
	ft_converte_str(str, -1);
	while (*str)
	{
		if (cmd == 0 && redir == 0 && !ft_strchr(" <>|", *str) && cmd++)
			str = set_cmd(str, NULL, &exec);
		if (cmd == 1 && redir == 0 && !ft_strchr(" <>|", *str))
			str = set_arg(str, NULL, &exec);
		if (redir == 0 && (*str == '<' || *str == '>') && redir++)
			str = set_redir(str, &type_redir);
		if (redir == 1 && !ft_strchr(" <>|", *str) && redir--)
			str = set_file(str, NULL, &exec, type_redir);
		if (*str)
			str++;
	}
	return (NULL);
}
