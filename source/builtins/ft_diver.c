/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 06:55:49 by tliot             #+#    #+#             */
/*   Updated: 2022/08/22 14:03:16 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_check_signe(const char *str, int *i, int *sign)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
		if (str[*i] == '+' || str[*i] == '-')
			return (0);
	}
	return (1);
}

bool	ft_atoi_bool(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (!ft_check_signe(str, &i, &sign))
		return (0);
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if ((sign == 1 && num >= (unsigned long long)9223372036854775808ULL))
		return (0);
	if ((sign == -1 && num >= (unsigned long long)9223372036854775809ULL))
		return (0);
	return (1);
}

char	*ft_joint_free_s1_s2(char *str1, char *str2)
{
	char	*str_join;

	str_join = NULL;
	str_join = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (str_join);
}

void	ft_put_err_cd(char *cmd, char *arg, char *strerrno)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerrno, 2);
	ft_putstr_fd("\n", 2);
	(*g_global)->exit_code = 1;
}
