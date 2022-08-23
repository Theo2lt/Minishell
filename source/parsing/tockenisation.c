/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/08/23 15:11:44 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Minishell.h"

void	*ft_delete_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->tabs_exeve)
			ft_free_tab2(exec->tabs_exeve);
		if (exec->args)
			free(exec->args);
		if (exec->infile)
			close(exec->infile);
		if (exec->outfile)
			close(exec->outfile);
		free(exec);
		exec = NULL;
	}
	return (NULL);
}

void	*ft_delete_execs(t_exec *exec)
{
	if (exec)
		if (exec->next)
			ft_delete_execs(exec->next);
	return (ft_delete_exec(exec));
}

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

void	ft_print_error_file(char *str, char *sterr)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(sterr, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_exit_child(t_minishell *mini, int exit_code)
{
	ft_delete_execs(mini->begin);
	if (mini->env_lst)
		ft_lst_env_free(mini->env_lst);
	if (mini->exec)
		ft_delete_exec_lst_free(&mini->exec);
	if (mini->fd[1] > 1)
		close(mini->fd[1]);
	if (mini->fd[0] > 0)
		close(mini->fd[0]);
	if (mini->fd_previous > 0)
		close(mini->fd_previous);
	if (mini)
		free(mini);
	ft_all_close_fd();
	exit(exit_code);
}

char	*ft_create_name(void)
{
	char			*str;
	long long int	n;

	n = 0;
	while (1)
	{
		str = ft_joint_free_s2("/tmp/tmp_bosh_", ft_itoa2(n));
		if (access(str, F_OK))
			return (str);
		free(str);
		n++;
	}
}

void	*ft_free2(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (str);
}

void	exit_heredoc(t_token *tkn, int exit_code)
{
	ft_free2(tkn->limiter);
	ft_free2(tkn->file_name);
	ft_delete_exec(tkn->exec);
	ft_converte_tab_list(NULL, &tkn->env, ft_delete_env);
	exit(exit_code);
}

void	open_heredoc(t_token *tkn)
{
	tkn->exec->infile = open(tkn->file_name, O_CREAT
			| O_RDWR, S_IRUSR | S_IWUSR);
	if (tkn->exec->infile < 0)
		ft_putstr_fd("ERROR HERDOC", 2);
}

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
	if (!str)
		return (1);
	while (*str && *str != '"' && *str != '\'' && *str != ' ')
		str++;
	if (*str == '"' || *str == '\'')
		tkn->type_redir = 5;
	else
		tkn->type_redir = 4;
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
