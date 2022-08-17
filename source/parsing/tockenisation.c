/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/08/17 13:42:57 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_positive_negative(char *str, int signe)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str && signe > 0 && *str < 0)
			*str *= -1;
		if (*str && signe < 0 && *str > 0)
			*str *= -1;
		str++;
	}
}

void	read_herdoc(char *limiter, t_exec *exec, int mode)
{
	char		*input;

	while (42)
	{
		input = readline("> ");
		if (!input || !ft_strncmp(limiter, input, ft_strlen(limiter) + 1))
		{
			//close(exec->infile);
			ft_exit((*g_global));
		}
		if (mode == 4)
		{
			input = parser_expende(input, exec->env, 0);
			ft_positive_negative(input, 1);
		}
		ft_putstr_fd(input, exec->infile);
		if (input)
			free(input);
	}
}

void	set_herdoc(char *str, t_exec *exec, int mode)
{
	int		pid;

	exec->infile = open("/tmp/", __O_TMPFILE | O_RDWR, 0666);
	if (exec->infile < 0)
		ft_putstr_fd("ERROR HERDOC", 2);
	pid = fork();
	if (!pid)
	{
		read_herdoc(str, exec, mode);
		//close(exec->infile);
		ft_exit((*g_global));
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
			ft_putstr_fd("ERROR INFILE\n", 2);
	}
	else if (mode == 4 || mode == 5)
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
			ft_putstr_fd("ERROR OUFILE\n", 2);
	}
	else if (mode == 1 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE\n", 2);
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

char	*set_file(char *start, char *res, t_exec *exec, int type_redir)
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
			return (set_file(tmp + 1, res, exec, type_redir));
	ft_positive_negative(res, 1);
	if (type_redir == 1 || type_redir == 3)
		set_outfile(res, exec, type_redir);
	if (type_redir == 2 || type_redir >= 4)
		set_infile(res, exec, type_redir);
	if (res)
		free(res);
	return (tmp);
}

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

t_exec	*set_tocken(t_exec *exec, t_env *env)
{
	if (!exec)
	{
		exec = malloc(sizeof(t_exec));
		exec->env = env;
		exec->infile = 0;
		exec->outfile = 1;
		exec->next = NULL;
		exec->args = NULL;
		exec->tabs_exeve = NULL;
	}
	return (exec);
}

t_exec	*tocken(char *str, t_exec *exec, t_env *env, int cmd)
{
	int		redir;
	int		type_redir;

	if (!str || !*str)
		return (exec);
	redir = 0;
	exec = set_tocken(exec, env);
	ft_converte_str(str, -1);
	while (*str && *str != '|')
	{
		if (cmd == 0 && redir == 0 && !ft_strchr(" <>|", *str) && ++cmd)
			str = set_cmd(str, NULL, exec);
		if (cmd >= 1 && redir == 0 && !ft_strchr(" <>|", *str))
			str = set_arg(str, NULL, exec);
		if (redir == 0 && (*str == '<' || *str == '>') && ++redir)
			str = set_redir(str, &type_redir);
		if (redir == 1 && !ft_strchr(" <>|", *str) && !(--redir))
			str = set_file(str, NULL, exec, type_redir);
		if (*str && *str != '|')
			str++;
	}
	exec->tabs_exeve = ft_split(exec->args, 127);
	if (*str && *str == '|')
		exec->next = tocken(str + 1, exec->next, env, 0);
	return (exec);
}
