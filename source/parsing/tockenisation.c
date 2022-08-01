/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/08/01 22:52:13 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	set_infile(char *str, t_exec *exec)
{
	if (exec->infile > 0)
	{
		exec->infile = open(str, O_RDONLY, 0666);
		if (exec->infile < 0)
			ft_putstr_fd("ERROR INFILE", 2);
	}
	if (exec->infile < 0)
		return (0);
	return (1);
}

int	set_outfile(char *str, t_exec *exec, int mode)
{
	if (mode && exec->outfile >= 0)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	else if (!mode && exec->outfile >= 0)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	if (exec->outfile < 0)
		return (0);
	return (1);
}

/*int	set_cmd(char *str, t_exec *exec)
{

}
*/

char	*set_tocken(char *start, t_exec *exec)
{
	char	*tmp;
	char	*res;

	(void)exec;
	if (*start == '\'' || *start == '"')
		start++;
	tmp = start;
	while (*tmp && !ft_strchr("\"'<>| ", *tmp))
		printf("%c", *(tmp++));
	if (*tmp && (*tmp == '\'' || *tmp == '"'))
		if (tmp[1] && !ft_strchr("<>| ", tmp[1]))
			return (set_tocken(tmp + 1, exec));
	return (tmp);
}

t_exec	*tocken(char *str)
{
	t_exec	exec;
	int		redir;
	int		cmd;

	cmd = 0;
	redir = 0;
	(void)exec;
	ft_converte_str(str, -1);
	while (*str)
	{
		if (cmd == 0 && redir == 0 && !ft_strchr(" <>|", *str))
		{
			cmd = 1;
			printf("COMANDE == ");
			while (*str && !ft_strchr(" <>|", *str))
				printf("%c", *(str++));
			printf("\n");
		}
		if (cmd == 1 && redir == 0 && !ft_strchr(" <>|", *str))
		{
			printf("ARGUMENTS == ");
			str = set_arg(str, &exec);
			printf("\n");
		}
		if (redir == 0 && (*str == '<' || *str == '>'))
		{
			redir = 1; printf("REDIRECTION == ");
			str++;
			printf("\n");
		}
		if (redir == 1 && !ft_strchr(" <>|", *str))
		{
			redir = 0;
			printf("FILE == ");
			while (*str && *str != ' ')
				printf("%c", *(str++));
			printf("\n");
		}
		if (*str)
			str++;
	}
	return (NULL);
}
