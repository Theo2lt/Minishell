/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sredjini <sredjini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 07:55:40 by sredjini          #+#    #+#             */
/*   Updated: 2022/07/21 03:42:27 by sredjini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

char	*ft_nb_expand(char *str, int i, t_pars *pars)
{
	
	int j;
	char *tmp;

	if (str[i] == '$' /*&& str[i + 1] && (ft_isalpha(str[i + 1])
			|| str[i + 1] == '_')*/)
	{
		j = ++i;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
		//pars->expand++;
		//pars->len -= j - i + 1;
		tmp = str;
		tmp = ft_save_pos_expand(str, 1, i, j, pars);
		printf("1 replace str %s\n", str);
		free(tmp);
		return (str);
	}
	return (str);
}

int	ft_check_expand(char *str, char c, int i, t_pars *pars)
{
	int	j;
	(void)pars;
	if (c == '"')
	{
		if (str[i] == '$' && str[i + 1] /*&& (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_')*/)
		{
			j = ++i;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			if (str[j] == '$' && printf("PAR_LA %c\n", c))
				j = ft_check_expand(str, c, j, pars);
			return (j);
		}
	}
	return (i);
}

int	ft_negative_quote(char *str, t_pars *pars)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
			{
				i = ft_check_expand(str, c, i, pars);
				if ((!str[i] || str[i] == '"'))
					break ;			
				str[i] = -1 * str[i];
			}
		}
		if (str[i] == '<')
			i = negative_expand(str, i + 1);	
	}
	return (1);
}

int	negative_expand(char *str, int i)
{
	if (!str[i] || str[i] != '<')
		return (i);
	i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\"'))
		i++;
	if (str[i] == '$')
		str[i] = -1 * str[i];
	return (i);	
}

int	ft_positive_char(char *str, t_pars *pars)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	(void)pars;
	return (1);
}


/* char	*ft_init_pars2(char *str, t_pars *pars)
{
	int	i;
	char c;

	i = - 1;
	
	while (str[++i])
	{	
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
			{
				str = ft_save_expand(str, c, i, pars);
				if ((str[i] == '"'))
					break ;
			}
		}
		else
			str = ft_nb_expand(str, i, pars);
	}
	return (str);
} */

/*char	*ft_save_expand(char *str, char c, int i, t_pars *pars)
{
	int	j;
	(void)pars;
	if (c == '"')
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_'))
		{
			j = ++i;
			pars->expand++;
			pars->len -= j - i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			//printf(" %d == i , %d == j", i , j);
			str = ft_save_pos_expand(str, 1, i, j, pars);
			return (str);
		}
	}
	return (str);
} */