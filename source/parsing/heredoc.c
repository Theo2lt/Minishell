/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:46:47 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 13:47:58 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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
