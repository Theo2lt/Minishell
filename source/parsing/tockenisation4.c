/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:45:38 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 13:45:51 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	read_heredoc(t_token *tkn)
{
	char		*input;

	while (42)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("bosh: warning: here-document ", 2);
			ft_putstr_fd("at line 1 delimited by end-of-file", 2);
			ft_putstr_fd(" (wanted `end')\n", 2);
			exit_heredoc(tkn, 0);
		}
		if (!input || !ft_strncmp(tkn->limiter, input,
				ft_strlen(tkn->limiter) + 1))
			exit_heredoc(tkn, 0);
		if (tkn->type_redir == 4)
			input = parser_expende(input, tkn->exec->env, 0);
		ft_putstr_fd(input, tkn->exec->infile);
		ft_putstr_fd("\n", tkn->exec->infile);
		if (input && tkn->type_redir == 4)
			free(input);
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		exit(130);
	}
}

int	signal_heredoc(t_token *tkn, int mode)
{
	if (!tkn->pid)
		signal(SIGINT, handler);
	if (tkn->pid)
	{
		if (mode)
			signal(SIGINT, SIG_IGN);
		if (!mode)
			signal(SIGINT, get_signal);
	}
	return (1);
}

int	set_heredoc(t_token *tkn, char *str)
{
	tkn->limiter = str;
	tkn->file_name = ft_create_name();
	open_heredoc(tkn);
	tkn->pid = fork();
	if (!tkn->pid)
	{
		signal_heredoc(tkn, 0);
		read_heredoc(tkn);
	}
	if (tkn->pid)
	{
		signal_heredoc(tkn, 1);
		waitpid(tkn->pid, &tkn->status, 0);
		if (WIFEXITED(tkn->status))
			(*g_global)->exit_code = WEXITSTATUS(tkn->status);
		signal_heredoc(tkn, 1);
		open_heredoc(tkn);
		ft_free2(tkn->limiter);
		ft_free2(tkn->file_name);
		if ((*g_global)->exit_code == 130)
			return (0);
	}
	return (1);
}

int	set_infile(t_token *tkn, char *str, t_exec *exec)
{
	if (tkn->type_redir == 2 && exec->infile >= 0 && exec->outfile >= 1)
	{
		exec->infile = open(str, O_RDONLY, 0666);
		if (exec->infile < 0)
		{
			ft_print_error_file(str, strerror(errno));
			(*g_global)->exit_code = 1;
		}
	}
	else if (tkn->type_redir == 4 || tkn->type_redir == 5)
		if (!set_heredoc(tkn, str))
			return (0);
	if (exec->infile < 0)
		return (0);
	return (1);
}
